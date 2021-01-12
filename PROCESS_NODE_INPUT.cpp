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
#include "PROCESS_NODE_INPUT.h"
PROCESS_NODE_INPUT::PROCESS_NODE_INPUT(CONTAINER* c, STATIC_FONT* font, DRAWER::DRAWERS_SHADER* lineDrawers, PROCESS_NODE_LINER* processNodeLiner, PROCESS_NODE_MANAGER* processNodeManager):
	ProcessNodeManager(processNodeManager),
	StringBoxVariable(c,font,UI_INPUT_BOX::INPUT_TYPE::KEY_PULLDOWN,processNodeManager),
	StringBoxInputModule(c,font, UI_INPUT_BOX::INPUT_TYPE::PULLDOWN),
	NodeConnectorFront(c,this, processNodeLiner),
	NodeConnectorBack(c,this,lineDrawers, processNodeLiner, processNodeManager),
	NodeConnectorFront_(&NodeConnectorFront),
	NodeConnectorBack_(&NodeConnectorBack){

	Frame.create(this, c->texture("processNodeInputBack"), ProcessNodeManager);
	UI* rootUi = Frame.rootUi();
	NodeTypeNameUi = UI_FACTORY::instance(DRAWER::STATIC_FONT::instance("入力モジュール", font, VECTOR2(), VECTOR2(24.0f, 24.0f), DRAWER::STATIC_FONT::drawMethodDefault()));
	NodeTypeNameUi->setIsCollisionDisable(true);
	rootUi->addChilds(NodeTypeNameUi);
	NodeConnectorFront.rootUi()->setPos(VECTOR2(8.0f, 80.0f));
	rootUi->addChilds(NodeConnectorFront.rootUi());
	NodeConnectorBack.rootUi()->setPos(VECTOR2(232.0f, 80.0f));
	rootUi->addChilds(NodeConnectorBack.rootUi());
	//入力モジュール
	startScrollInput(StringBoxInputModule.pulldownInputUi(), ProcessNodeManager->inputModuleScroll(), ProcessNodeManager, &StringBoxInputModule);
	StringBoxInputModule.rootUi()->setPos(VECTOR2(32.0f, 104.0f));
	rootUi->addChilds(StringBoxInputModule.rootUi());
	//左辺
	startKeyboardInput(StringBoxVariable.keyInputUi(), ProcessNodeManager,&StringBoxVariable);
	startScrollInput(StringBoxVariable.pulldownInputUi(), ProcessNodeManager->variableScroll(), ProcessNodeManager,&StringBoxVariable);
	StringBoxVariable.rootUi()->setPos(VECTOR2(32.0f, 48.0f));
	rootUi->addChilds(StringBoxVariable.rootUi());
}
PROCESS_NODE_INPUT::~PROCESS_NODE_INPUT() {
	disconnect(this);
}

std::pair<PROCESS_NODE_CONNECTOR_IN**, int> PROCESS_NODE_INPUT::allNodeConnectorIn() {
	return { &NodeConnectorFront_ ,1 };
}

std::pair<PROCESS_NODE_CONNECTOR_OUT**, int> PROCESS_NODE_INPUT::allNodeConnectorOut() {
	return { &NodeConnectorBack_,1 };
}

std::string PROCESS_NODE_INPUT::saveDataString() {
	return PROCESS_NODE_SAVE::commonSaveDataString(PROCESS_NODE_SAVE::getTypeStringName(PROCESS_NODE_TYPE::INPUT), rootUi()->pos()) +
		"inputModule{" + StringBoxInputModule.inputBoxUiDrawer()->string() + "}" +
		"variable{" + StringBoxVariable.string() + "}";
}

void PROCESS_NODE_INPUT::loadFromSaveString(const STRING_TREE& data) {
	rootUi()->setPos(PROCESS_NODE_LOAD::loadSaveDataStringPos(data));
	int idx = data.findData("inputModule");
	if (idx != -1) {
		StringBoxInputModule.inputBoxUiDrawer()->setString(data.childs()[idx]->data());
	}
	idx = data.findData("variable");
	if (idx != -1) {
		StringBoxVariable.setString(data.childs()[idx]->data());
	}
}

void PROCESS_NODE_INPUT::compile(ROBOT_COMPILER* robotCompiler){
	robotCompiler->addVariable(StringBoxVariable);
	robotCompiler->checkInputModule(StringBoxInputModule.inputBoxUiDrawer()->string());
}

void PROCESS_NODE_INPUT::nextStep(ROBOT_PROCESSOR* robotProcessor){
	const std::string& inputModuleName = StringBoxInputModule.inputBoxUiDrawer()->string();
	if (robotProcessor->inputModuleList().list()->contains(inputModuleName)) {	//対応するする入力モジュールがあれば
		robotProcessor->inputModule(inputModuleName, robotProcessor->variable(StringBoxVariable.string()));
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

void PROCESS_NODE_INPUT::setEnable(){
	StringBoxVariable.setEnable();
}

void PROCESS_NODE_INPUT::setDisable(){
	StringBoxVariable.setDisable();
}
