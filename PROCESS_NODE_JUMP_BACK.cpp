#include "../Library/CONTAINER.h"
#include "../Library/STRING_TREE.h"
#include "../Library/INDEV.h"
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
#include "PROCESS_NODE_JUMP_BACK.h"
PROCESS_NODE_JUMP_BACK::PROCESS_NODE_JUMP_BACK(CONTAINER* c, STATIC_FONT* font, DRAWER::DRAWERS_SHADER* lineDrawers, PROCESS_NODE_LINER* processNodeLiner, PROCESS_NODE_MANAGER* processNodeManager) :
	ProcessNodeManager(processNodeManager),
	StringBoxInputJumpPoint(c, font, UI_INPUT_BOX::INPUT_TYPE::KEY_PULLDOWN),
	NodeConnectorFront(c, this, processNodeLiner),
	NodeConnectorBack(c, this, lineDrawers, processNodeLiner, processNodeManager),
	NodeConnectorFront_(&NodeConnectorFront),
	NodeConnectorBack_(&NodeConnectorBack){
	Frame.create(this, c->texture("processNodeBack"), ProcessNodeManager);
	UI* rootUi = Frame.rootUi();
	NodeTypeNameUi = UI_FACTORY::instance(DRAWER::STATIC_FONT::instance("ジャンプバック", font, VECTOR2(), VECTOR2(24.0f, 24.0f), DRAWER::STATIC_FONT::drawMethodDefault()));
	NodeTypeNameUi->setIsCollisionDisable(true);
	rootUi->addChilds(NodeTypeNameUi);
	//コネクター
	NodeConnectorFront.rootUi()->setPos(VECTOR2(8.0f, 80.0f));
	rootUi->addChilds(NodeConnectorFront.rootUi());
	NodeConnectorBack.rootUi()->setPos(VECTOR2(232.0f, 80.0f));
	rootUi->addChilds(NodeConnectorBack.rootUi());
	//ジャンプポイント
	startKeyboardInput(StringBoxInputJumpPoint.keyInputUi(), ProcessNodeManager, &StringBoxInputJumpPoint);
	startScrollInput(StringBoxInputJumpPoint.pulldownInputUi(), ProcessNodeManager->jumpPointScroll(), ProcessNodeManager, &StringBoxInputJumpPoint);
	StringBoxInputJumpPoint.rootUi()->setPos(VECTOR2(32.0f, 76.0f));
	rootUi->addChilds(StringBoxInputJumpPoint.rootUi());
}
PROCESS_NODE_JUMP_BACK::~PROCESS_NODE_JUMP_BACK() {
	disconnect(this);
}

std::pair<PROCESS_NODE_CONNECTOR_IN**, int> PROCESS_NODE_JUMP_BACK::allNodeConnectorIn() {
	return { &NodeConnectorFront_, 1 };
}

std::pair<PROCESS_NODE_CONNECTOR_OUT**, int> PROCESS_NODE_JUMP_BACK::allNodeConnectorOut() {
	return { &NodeConnectorBack_,1 };
}

std::string PROCESS_NODE_JUMP_BACK::saveDataString() {
	return PROCESS_NODE_SAVE::commonSaveDataString(PROCESS_NODE_SAVE::getTypeStringName(PROCESS_NODE_TYPE::JUMP_BACK), rootUi()->pos()) +
		"jump_point{" + StringBoxInputJumpPoint.inputBoxUiDrawer()->string() + "}";
}

void PROCESS_NODE_JUMP_BACK::loadFromSaveString(const STRING_TREE& data) {
	rootUi()->setPos(PROCESS_NODE_LOAD::loadSaveDataStringPos(data));
	int idx = data.findData("jump_point");
	if (idx != -1) {
		StringBoxInputJumpPoint.inputBoxUiDrawer()->setString(data.childs()[idx]->data());
	}
}

void PROCESS_NODE_JUMP_BACK::compile(ROBOT_COMPILER* robotCompiler){
	robotCompiler->checkJumpPoint(StringBoxInputJumpPoint.inputBoxUiDrawer()->string());
}

void PROCESS_NODE_JUMP_BACK::nextStep(ROBOT_PROCESSOR* robotProcessor){
	robotProcessor->JumpBackIn(this);
	if (robotProcessor->stepCnt()) {
		//1フレームのプロセス数の上限に達した
		robotProcessor->oneFrameProcessEnd(this);
	}
	else {
		//次のノードへ処理を続行
		const std::string& jumpPointName= StringBoxInputJumpPoint.inputBoxUiDrawer()->string();
		if (robotProcessor->jumpPointList().contains(jumpPointName)) {//対応するジャンプポイントがあれば
			robotProcessor->jumpPointList()[jumpPointName]->nextStep(robotProcessor);
		}
	}
}

void PROCESS_NODE_JUMP_BACK::ReturnedStep(ROBOT_PROCESSOR* robotProcessor){
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

void PROCESS_NODE_JUMP_BACK::setEnable(){
}

void PROCESS_NODE_JUMP_BACK::setDisable(){
}
