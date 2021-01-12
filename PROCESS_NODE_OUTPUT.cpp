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
#include "PROCESS_NODE_OUTPUT.h"
PROCESS_NODE_OUTPUT::PROCESS_NODE_OUTPUT(CONTAINER* c, STATIC_FONT* font, DRAWER::DRAWERS_SHADER* lineDrawers, PROCESS_NODE_LINER* processNodeLiner, PROCESS_NODE_MANAGER* processNodeManager) :
	ProcessNodeManager(processNodeManager),
	StringBoxInputVariable(c, font, UI_INPUT_BOX::INPUT_TYPE::KEY_PULLDOWN, processNodeManager),
	StringBoxOutputModule(c, font,UI_INPUT_BOX::INPUT_TYPE::PULLDOWN),
	NodeConnectorFront(c, this, processNodeLiner),
	NodeConnectorBack(c, this, lineDrawers, processNodeLiner, processNodeManager),
	NodeConnectorFront_(&NodeConnectorFront),
	NodeConnectorBack_(&NodeConnectorBack){

	Frame.create(this, c->texture("processNodeOutputBack"), ProcessNodeManager);
	UI* rootUi = Frame.rootUi();
	NodeTypeNameUi = UI_FACTORY::instance(DRAWER::STATIC_FONT::instance("出力モジュール", font, VECTOR2(), VECTOR2(24.0f, 24.0f), DRAWER::STATIC_FONT::drawMethodDefault()));
	NodeTypeNameUi->setIsCollisionDisable(true);
	rootUi->addChilds(NodeTypeNameUi);
	//コネクター
	NodeConnectorFront.rootUi()->setPos(VECTOR2(8.0f, 80.0f));
	rootUi->addChilds(NodeConnectorFront.rootUi());
	NodeConnectorBack.rootUi()->setPos(VECTOR2(232.0f, 80.0f));
	rootUi->addChilds(NodeConnectorBack.rootUi());
	//出力モジュール
	startScrollInput(StringBoxOutputModule.pulldownInputUi(), ProcessNodeManager->outputModuleScroll(), ProcessNodeManager, &StringBoxOutputModule);
	StringBoxOutputModule.rootUi()->setPos(VECTOR2(32.0f, 48.0f));
	rootUi->addChilds(StringBoxOutputModule.rootUi());
	//左辺
	startKeyboardInput(StringBoxInputVariable.keyInputUi(), ProcessNodeManager, &StringBoxInputVariable);
	startScrollInput(StringBoxInputVariable.pulldownInputUi(), ProcessNodeManager->variableScroll(), ProcessNodeManager, &StringBoxInputVariable);
	StringBoxInputVariable.rootUi()->setPos(VECTOR2(32.0f, 104.0f));
	rootUi->addChilds(StringBoxInputVariable.rootUi());
}
PROCESS_NODE_OUTPUT::~PROCESS_NODE_OUTPUT() {
	disconnect(this);
}

std::pair<PROCESS_NODE_CONNECTOR_IN**, int> PROCESS_NODE_OUTPUT::allNodeConnectorIn(){
	return { &NodeConnectorFront_ ,1 };
}

std::pair<PROCESS_NODE_CONNECTOR_OUT**, int> PROCESS_NODE_OUTPUT::allNodeConnectorOut(){
	return { &NodeConnectorBack_,1 };
}

std::string PROCESS_NODE_OUTPUT::saveDataString(){
	return PROCESS_NODE_SAVE::commonSaveDataString(PROCESS_NODE_SAVE::getTypeStringName(PROCESS_NODE_TYPE::OUTPUT), rootUi()->pos()) +
		"outputModule{" + StringBoxOutputModule.inputBoxUiDrawer()->string() + "}"+
		"variable{" + StringBoxInputVariable.string() + "}";
}

void PROCESS_NODE_OUTPUT::loadFromSaveString(const STRING_TREE& data){
	rootUi()->setPos(PROCESS_NODE_LOAD::loadSaveDataStringPos(data));
	int idx = data.findData("outputModule");
	if (idx != -1) {
		StringBoxOutputModule.inputBoxUiDrawer()->setString(data.childs()[idx]->data());
	}
	idx = data.findData("variable");
	if (idx != -1) {
		StringBoxInputVariable.setString(data.childs()[idx]->data());
	}
}

void PROCESS_NODE_OUTPUT::compile(ROBOT_COMPILER* robotCompiler){
	robotCompiler->checkOutputModule(StringBoxOutputModule.inputBoxUiDrawer()->string());
	robotCompiler->addVariable(StringBoxInputVariable);
}

void PROCESS_NODE_OUTPUT::nextStep(ROBOT_PROCESSOR* robotProcessor){
	if (!StringBoxInputVariable.isNumber()) {
		const std::string& outputModuleName = StringBoxOutputModule.inputBoxUiDrawer()->string();
		if (robotProcessor->outputModuleList().list()->contains(outputModuleName)) {//対応するする入力モジュールがあれば
			robotProcessor->setVariable(StringBoxInputVariable.string(), robotProcessor->outputModule(outputModuleName));
		}
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

void PROCESS_NODE_OUTPUT::setEnable(){
	StringBoxInputVariable.setEnable();
}

void PROCESS_NODE_OUTPUT::setDisable(){
	StringBoxInputVariable.setDisable();
}
