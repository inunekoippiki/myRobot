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
#include "PROCESS_NODE_ASSIGNMENT.h"
PROCESS_NODE_ASSIGNMENT::PROCESS_NODE_ASSIGNMENT(
	CONTAINER* c,
	STATIC_FONT* font,
	DRAWER::DRAWERS_SHADER* lineDrawers,
	PROCESS_NODE_LINER* processNodeLiner,
	PROCESS_NODE_MANAGER* processNodeManager) :
	ProcessNodeManager(processNodeManager),
	StringBoxVariable1(c, font, UI_INPUT_BOX::INPUT_TYPE::KEY_PULLDOWN, processNodeManager),
	StringBoxAssignmentOperator(c, font),
	StringBoxVariable2(c, font, UI_INPUT_BOX::INPUT_TYPE::KEY_PULLDOWN, processNodeManager),
	NodeConnectorFront(c, this, processNodeLiner),
	NodeConnectorBack(c, this, lineDrawers, processNodeLiner, processNodeManager),
	NodeConnectorFront_(&NodeConnectorFront),
	NodeConnectorBack_(&NodeConnectorBack)
{
	Frame.create(this,c->texture("processNodeAssignmentBack"), ProcessNodeManager);
	UI* rootUi = Frame.rootUi();
	NodeTypeNameUi = instanceNodeTypeNameUi("代入ノード", font);
	rootUi->addChilds(NodeTypeNameUi);
	NodeConnectorFront.rootUi()->setPos(VECTOR2(8.0f, 80.0f));
	rootUi->addChilds(NodeConnectorFront.rootUi());
	NodeConnectorBack.rootUi()->setPos(VECTOR2(232.0f, 80.0f));
	rootUi->addChilds(NodeConnectorBack.rootUi());

	//右辺
	startKeyboardInput(StringBoxVariable1.keyInputUi(), ProcessNodeManager, &StringBoxVariable1);
	startScrollInput(StringBoxVariable1.pulldownInputUi(), ProcessNodeManager->variableScroll(), ProcessNodeManager, &StringBoxVariable1);
	StringBoxVariable1.rootUi()->setPos(VECTOR2(32.0f, 48.0f));
	rootUi->addChilds(StringBoxVariable1.rootUi());
	//演算子
	startScrollInput(StringBoxAssignmentOperator.pulldownInputUi(), ProcessNodeManager->assignmentOperatorScroll(), ProcessNodeManager,&StringBoxAssignmentOperator);
	StringBoxAssignmentOperator.rootUi()->setPos(VECTOR2(152.0f, 76.0f));
	rootUi->addChilds(StringBoxAssignmentOperator.rootUi());
	//左辺
	startKeyboardInput(StringBoxVariable2.keyInputUi(), ProcessNodeManager, &StringBoxVariable2);
	startScrollInput(StringBoxVariable2.pulldownInputUi(), ProcessNodeManager->variableScroll(), ProcessNodeManager, &StringBoxVariable2);
	StringBoxVariable2.rootUi()->setPos(VECTOR2(32.0f, 104.0f));
	rootUi->addChilds(StringBoxVariable2.rootUi());
}
PROCESS_NODE_ASSIGNMENT::~PROCESS_NODE_ASSIGNMENT() {
	disconnect(this);
}

std::pair<PROCESS_NODE_CONNECTOR_IN**, int> PROCESS_NODE_ASSIGNMENT::allNodeConnectorIn() {
	return { &NodeConnectorFront_ ,1 };
}

std::pair<PROCESS_NODE_CONNECTOR_OUT**, int> PROCESS_NODE_ASSIGNMENT::allNodeConnectorOut() {
	return { &NodeConnectorBack_,1 };
}

std::string PROCESS_NODE_ASSIGNMENT::saveDataString() {
	return PROCESS_NODE_SAVE::commonSaveDataString(PROCESS_NODE_SAVE::getTypeStringName(PROCESS_NODE_TYPE::ASSIGNMENT), rootUi()->pos()) +
		"variable1{" + StringBoxVariable1.string() + "}" +
		"assignment{" + StringBoxAssignmentOperator.string() + "}"+
		"variable2{" + StringBoxVariable2.string() + "}";
}

void PROCESS_NODE_ASSIGNMENT::loadFromSaveString(const STRING_TREE& data) {
	rootUi()->setPos(PROCESS_NODE_LOAD::loadSaveDataStringPos(data));
	int idx = data.findData("variable1");
	if (idx != -1) {
		StringBoxVariable1.setString(data.childs()[idx]->data());
	}
	idx = data.findData("assignment");
	if (idx != -1) {
		StringBoxAssignmentOperator.setString(data.childs()[idx]->data());
	}
	idx = data.findData("variable2");
	if (idx != -1) {
		StringBoxVariable2.setString(data.childs()[idx]->data());
	}
}

void PROCESS_NODE_ASSIGNMENT::compile(ROBOT_COMPILER* robotCompiler){
	robotCompiler->addVariable(StringBoxVariable1);
	robotCompiler->addVariable(StringBoxVariable2);
}

void PROCESS_NODE_ASSIGNMENT::nextStep(ROBOT_PROCESSOR* robotProcessor){
	if (!StringBoxVariable1.isNumber()) {
		double value = robotProcessor->variable(StringBoxVariable1.string());
		StringBoxAssignmentOperator.variableOperation(value,robotProcessor->variable(StringBoxVariable2.string()));
		robotProcessor->setVariable(StringBoxVariable1.string(), value);
	}
	if (robotProcessor->stepCnt()) {
		//1フレームのプロセス数の上限に達した
		robotProcessor->oneFrameProcessEnd(this);
	}
	else{
		//次のノードへ処理を続行
		if (NodeConnectorBack.cnnectorNext() != nullptr) {
			NodeConnectorBack.cnnectorNext()->processNode()->nextStep(robotProcessor);
		}
		else {//次のノードが繋がっていない
			robotProcessor->JumpBackReturn();
		}
	}
}

void PROCESS_NODE_ASSIGNMENT::setEnable(){
	StringBoxVariable1.setEnable();
	StringBoxVariable2.setEnable();
}

void PROCESS_NODE_ASSIGNMENT::setDisable(){
	StringBoxVariable1.setDisable();
	StringBoxVariable2.setDisable();
}
