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
#include "PROCESS_NODE_IF.h"
PROCESS_NODE_IF::PROCESS_NODE_IF(CONTAINER* c, STATIC_FONT* font, DRAWER::DRAWERS_SHADER* lineDrawers, PROCESS_NODE_LINER* processNodeLiner, PROCESS_NODE_MANAGER* processNodeManager) :
	ProcessNodeManager(processNodeManager),
	StringBoxInputVariable(c, font, UI_INPUT_BOX::INPUT_TYPE::KEY_PULLDOWN, processNodeManager),
	StringBoxComparisonOperator(c, font),
	StringBoxInputVariable2(c, font, UI_INPUT_BOX::INPUT_TYPE::KEY_PULLDOWN, processNodeManager),
	NodeConnectorFront(c, this, processNodeLiner),
	NodeConnectorBack(c, this, lineDrawers, processNodeLiner, processNodeManager),
	NodeConnectorBackElse(PROCESS_NODE_CONNECTOR_TYPE::ELSE, c, this, lineDrawers, processNodeLiner, processNodeManager),
	NodeConnectorFront_(&NodeConnectorFront),
	NodeConnectorBack_({ &NodeConnectorBack,&NodeConnectorBackElse }) {

	Frame.create(this, c->texture("processNodeBack"), ProcessNodeManager);
	UI* rootUi = Frame.rootUi();
	NodeTypeNameUi = UI_FACTORY::instance(DRAWER::STATIC_FONT::instance("分岐ノード", font, VECTOR2(), VECTOR2(24.0f, 24.0f), DRAWER::STATIC_FONT::drawMethodDefault()));
	NodeTypeNameUi->setIsCollisionDisable(true);
	rootUi->addChilds(NodeTypeNameUi);
	NodeConnectorFront.rootUi()->setPos(VECTOR2(8.0f, 80.0f));
	rootUi->addChilds(NodeConnectorFront.rootUi());
	NodeConnectorBack.rootUi()->setPos(VECTOR2(232.0f, 60.0f));
	rootUi->addChilds(NodeConnectorBack.rootUi());
	NodeConnectorBackElse.rootUi()->setPos(VECTOR2(232.0f, 100.0f));
	rootUi->addChilds(NodeConnectorBackElse.rootUi());
	//上段の変数入力
	startKeyboardInput(StringBoxInputVariable.keyInputUi(), ProcessNodeManager,&StringBoxInputVariable);
	startScrollInput(StringBoxInputVariable.pulldownInputUi(), ProcessNodeManager->variableScroll(), ProcessNodeManager, &StringBoxInputVariable);
	StringBoxInputVariable.rootUi()->setPos(VECTOR2(32.0f, 104.0f));
	rootUi->addChilds(StringBoxInputVariable.rootUi());
	//比較演算子
	startScrollInput(StringBoxComparisonOperator.pulldownInputUi(), ProcessNodeManager->comparisonOperatorScroll(), ProcessNodeManager, &StringBoxComparisonOperator);
	StringBoxComparisonOperator.rootUi()->setPos(VECTOR2(152.0f, 76.0f));
	rootUi->addChilds(StringBoxComparisonOperator.rootUi());
	//下段の変数入力
	startKeyboardInput(StringBoxInputVariable2.keyInputUi(), ProcessNodeManager, &StringBoxInputVariable2);
	startScrollInput(StringBoxInputVariable2.pulldownInputUi(), ProcessNodeManager->variableScroll(), ProcessNodeManager, &StringBoxInputVariable2);
	StringBoxInputVariable2.rootUi()->setPos(VECTOR2(32.0f, 48.0f));
	rootUi->addChilds(StringBoxInputVariable2.rootUi());
}
PROCESS_NODE_IF::~PROCESS_NODE_IF() {
	disconnect(this);
}

std::pair<PROCESS_NODE_CONNECTOR_IN**, int> PROCESS_NODE_IF::allNodeConnectorIn(){
	return { &NodeConnectorFront_, 1 };
}

std::pair<PROCESS_NODE_CONNECTOR_OUT**, int> PROCESS_NODE_IF::allNodeConnectorOut(){
	return { NodeConnectorBack_.data(),(int)NodeConnectorBack_.size() };
}

std::string PROCESS_NODE_IF::saveDataString(){
	return PROCESS_NODE_SAVE::commonSaveDataString(PROCESS_NODE_SAVE::getTypeStringName(PROCESS_NODE_TYPE::IF), rootUi()->pos()) +
		"variable1{" + StringBoxInputVariable.string() + "}" +
		"comparison{" + StringBoxComparisonOperator.string() + "}" +
		"variable2{" + StringBoxInputVariable2.string() + "}";
}

void PROCESS_NODE_IF::loadFromSaveString(const STRING_TREE& data){
	rootUi()->setPos(PROCESS_NODE_LOAD::loadSaveDataStringPos(data));
	int idx = data.findData("variable1");
	if (idx != -1) {
		StringBoxInputVariable.setString(data.childs()[idx]->data());
	}
	idx = data.findData("comparison");
	if (idx != -1) {
		StringBoxComparisonOperator.setString(data.childs()[idx]->data());
	}
	idx = data.findData("variable2");
	if (idx != -1) {
		StringBoxInputVariable2.setString(data.childs()[idx]->data());
	}
}

void PROCESS_NODE_IF::compile(ROBOT_COMPILER* robotCompiler){
	robotCompiler->addVariable(StringBoxInputVariable);
	robotCompiler->addVariable(StringBoxInputVariable2);

}

void PROCESS_NODE_IF::nextStep(ROBOT_PROCESSOR* robotProcessor) {
	if (robotProcessor->stepCnt()) {
		//1フレームのプロセス数の上限に達した
		robotProcessor->oneFrameProcessEnd(this);
	}
	else {
		//次のノードへ処理を続行
		if (StringBoxComparisonOperator.variableOperation(//変数を比較
			robotProcessor->variable(StringBoxInputVariable.string()),
			robotProcessor->variable(StringBoxInputVariable2.string()))) {
			if (NodeConnectorBack.cnnectorNext() != nullptr) {//BackコネクターにつながっているNextコネクターがある場合
				NodeConnectorBack.cnnectorNext()->processNode()->nextStep(robotProcessor);
			}
			else {
				robotProcessor->JumpBackReturn();
			}
		}
		else {
			if (NodeConnectorBackElse.cnnectorNext() != nullptr) {//BackコネクターにつながっているNextコネクター(下段)がある場合
				NodeConnectorBackElse.cnnectorNext()->processNode()->nextStep(robotProcessor);
			}
			else {
				robotProcessor->JumpBackReturn();
			}
		}
	}
}

void PROCESS_NODE_IF::setEnable(){
	StringBoxInputVariable.setEnable();
	StringBoxInputVariable2.setEnable();
}

void PROCESS_NODE_IF::setDisable(){
	StringBoxInputVariable.setDisable();
	StringBoxInputVariable2.setDisable();
}
