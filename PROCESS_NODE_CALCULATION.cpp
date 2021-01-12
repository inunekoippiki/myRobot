#include "../Library/CONTAINER.h"
#include "../Library/INDEV.h"
#include "../Library/STRING_TREE.h"
#include "INPUT_COMMON.h"
#include "UI.h"
#include "UI_FUNC_ATTACHER.h"
#include "UI_FACTORY.h"
#include "PROCESS_NODE_MANAGER.h"
#include "PROCESS_NODE_LINER.h"
#include "PROCESS_NODE_JUMP_BACK.h"
#include "PROCESS_NODE_LOAD.h"
#include "PROCESS_NODE_SAVE.h"
#include "NODE_LINE.h"
#include "ROBOT_COMPILER.h"
#include "ROBOT_PROCESSOR.h"
#include "PROCESS_NODE_FUNC_SET.h"
#include "PROCESS_NODE_CALCULATION.h"
PROCESS_NODE_CALCULATION::PROCESS_NODE_CALCULATION(CONTAINER* c, STATIC_FONT* font, DRAWER::DRAWERS_SHADER* lineDrawers, PROCESS_NODE_LINER* processNodeLiner, PROCESS_NODE_MANAGER* processNodeManager):
	ProcessNodeManager(processNodeManager),
	StringBoxVariable1(c,font,UI_INPUT_BOX::INPUT_TYPE::KEY_PULLDOWN,processNodeManager),
	StringBoxOperator(c,font),
	StringBoxVariable2(c, font, UI_INPUT_BOX::INPUT_TYPE::KEY_PULLDOWN, processNodeManager), 
	StringBoxVariable3(c, font, UI_INPUT_BOX::INPUT_TYPE::KEY_PULLDOWN, processNodeManager),
	NodeConnectorFront(c,this, processNodeLiner),
	NodeConnectorBack(c,this,lineDrawers, processNodeLiner, processNodeManager),
	NodeConnectorFront_(&NodeConnectorFront),
	NodeConnectorBack_(&NodeConnectorBack){
	Frame.create(this, c->texture("processNodeCalculationBack"), ProcessNodeManager);
	UI* rootUi = Frame.rootUi();
	NodeTypeNameUi = UI_FACTORY::instance(DRAWER::STATIC_FONT::instance("計算ノード", font, VECTOR2(), VECTOR2(24.0f, 24.0f), DRAWER::STATIC_FONT::drawMethodDefault()));
	NodeTypeNameUi->setIsCollisionDisable(true);
	rootUi->addChilds(NodeTypeNameUi);
	//コネクターの設定
	NodeConnectorFront.rootUi()->setPos(VECTOR2(8.0f, 80.0f));
	rootUi->addChilds(NodeConnectorFront.rootUi());
	NodeConnectorBack.rootUi()->setPos(VECTOR2(232.0f, 80.0f));
	rootUi->addChilds(NodeConnectorBack.rootUi());

	//右辺1
	startKeyboardInput(StringBoxVariable1.keyInputUi(), ProcessNodeManager,&StringBoxVariable1);
	startScrollInput(StringBoxVariable1.pulldownInputUi(), ProcessNodeManager->variableScroll(), ProcessNodeManager,&StringBoxVariable1);
	StringBoxVariable1.rootUi()->setPos(VECTOR2(32.0f, 118.0f - 28.0f * 3.0f));
	rootUi->addChilds(StringBoxVariable1.rootUi());
	//演算子
	startScrollInput(StringBoxOperator.pulldownInputUi(), ProcessNodeManager->operatorScroll(), ProcessNodeManager,&StringBoxOperator);
	StringBoxOperator.rootUi()->setPos(VECTOR2(152.0f, 118.0f - 28.0f * 2.0f));
	rootUi->addChilds(StringBoxOperator.rootUi());
	//右辺2
	startKeyboardInput(StringBoxVariable2.keyInputUi(), ProcessNodeManager, &StringBoxVariable2);
	startScrollInput(StringBoxVariable2.pulldownInputUi(), ProcessNodeManager->variableScroll(), ProcessNodeManager, &StringBoxVariable2);
	StringBoxVariable2.rootUi()->setPos(VECTOR2(32.0f, 118.0f - 28.0f*1.0f));
	rootUi->addChilds(StringBoxVariable2.rootUi());
	//左辺
	startKeyboardInput(StringBoxVariable3.keyInputUi(), ProcessNodeManager, &StringBoxVariable3);
	startScrollInput(StringBoxVariable3.pulldownInputUi(), ProcessNodeManager->variableScroll(), ProcessNodeManager,&StringBoxVariable3);
	StringBoxVariable3.rootUi()->setPos(VECTOR2(32.0f, 118.0f));
	rootUi->addChilds(StringBoxVariable3.rootUi());
}
PROCESS_NODE_CALCULATION::~PROCESS_NODE_CALCULATION() {
	disconnect(this);
}

std::pair<PROCESS_NODE_CONNECTOR_IN**, int> PROCESS_NODE_CALCULATION::allNodeConnectorIn() {
	return { &NodeConnectorFront_ ,1 };
}

std::pair<PROCESS_NODE_CONNECTOR_OUT**, int> PROCESS_NODE_CALCULATION::allNodeConnectorOut() {
	return { &NodeConnectorBack_,1 };
}

std::string PROCESS_NODE_CALCULATION::saveDataString() {
	return PROCESS_NODE_SAVE::commonSaveDataString(PROCESS_NODE_SAVE::getTypeStringName(PROCESS_NODE_TYPE::CALCULATION), rootUi()->pos()) +
		"variable1{" + StringBoxVariable1.string() + "}" +
		"operator{" + StringBoxOperator.string() + "}" +
		"variable2{" + StringBoxVariable2.string() + "}"+
		"variable3{" + StringBoxVariable3.string() + "}";

}

void PROCESS_NODE_CALCULATION::loadFromSaveString(const STRING_TREE& data) {
	rootUi()->setPos(PROCESS_NODE_LOAD::loadSaveDataStringPos(data));
	int idx = data.findData("variable1");
	if (idx != -1) {
		StringBoxVariable1.setString(data.childs()[idx]->data());
	}
	idx = data.findData("operator");
	if (idx != -1) {
		StringBoxOperator.setString(data.childs()[idx]->data());
	}
	idx = data.findData("variable2");
	if (idx != -1) {
		StringBoxVariable2.setString(data.childs()[idx]->data());
	}
	idx = data.findData("variable3");
	if (idx != -1) {
		StringBoxVariable3.setString(data.childs()[idx]->data());
	}
}

void PROCESS_NODE_CALCULATION::compile(ROBOT_COMPILER* robotCompiler){
	robotCompiler->addVariable(StringBoxVariable1);
	robotCompiler->addVariable(StringBoxVariable2);
	robotCompiler->addVariable(StringBoxVariable3);

}

void PROCESS_NODE_CALCULATION::nextStep(ROBOT_PROCESSOR* robotProcessor){
	if (!StringBoxVariable3.isNumber()) {
		double value = StringBoxOperator.variableOperation(
			robotProcessor->variable(StringBoxVariable1.string()),
			robotProcessor->variable(StringBoxVariable2.string()));
		robotProcessor->setVariable(
			StringBoxVariable3.string(), value);
	}

	if (robotProcessor->stepCnt()) {
		//1フレームのプロセス数の上限に達した
		robotProcessor->oneFrameProcessEnd(this);
	}
	else {
		//次のノードへ処理を続行
		if (NodeConnectorBack.cnnectorNext() != nullptr) {
			NodeConnectorBack.cnnectorNext()->processNode()->nextStep(robotProcessor);
		}
		else {//次のノードが繋がっていない
			robotProcessor->JumpBackReturn();
		}
	}
}

void PROCESS_NODE_CALCULATION::setEnable(){
	StringBoxVariable1.setEnable();
	StringBoxVariable2.setEnable();
	StringBoxVariable3.setEnable();
}

void PROCESS_NODE_CALCULATION::setDisable(){
	StringBoxVariable1.setDisable();
	StringBoxVariable2.setDisable();
	StringBoxVariable3.setDisable();
}
