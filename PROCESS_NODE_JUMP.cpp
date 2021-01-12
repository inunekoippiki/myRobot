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
#include "PROCESS_NODE_JUMP.h"
PROCESS_NODE_JUMP::PROCESS_NODE_JUMP(CONTAINER* c, STATIC_FONT* font, DRAWER::DRAWERS_SHADER* lineDrawers, PROCESS_NODE_LINER* processNodeLiner, PROCESS_NODE_MANAGER* processNodeManager):
	ProcessNodeManager(processNodeManager),
	StringBoxInputJumpPoint(c,font,UI_INPUT_BOX::INPUT_TYPE::KEY_PULLDOWN),
	NodeConnectorFront(c,this, processNodeLiner),
	NodeConnectorFront_(&NodeConnectorFront){

	Frame.create(this, c->texture("processNodeBack"), ProcessNodeManager);

	UI* rootUi = Frame.rootUi();
	NodeTypeNameUi = UI_FACTORY::instance(DRAWER::STATIC_FONT::instance("ジャンプノード", font, VECTOR2(), VECTOR2(24.0f, 24.0f), DRAWER::STATIC_FONT::drawMethodDefault()));
	NodeTypeNameUi->setIsCollisionDisable(true);
	rootUi->addChilds(NodeTypeNameUi);
	//コネクター
	NodeConnectorFront.rootUi()->setPos(VECTOR2(8.0f, 80.0f));
	rootUi->addChilds(NodeConnectorFront.rootUi());
	//ジャンプポイント
	startKeyboardInput(StringBoxInputJumpPoint.keyInputUi(), ProcessNodeManager, &StringBoxInputJumpPoint);
	startScrollInput(StringBoxInputJumpPoint.pulldownInputUi(), ProcessNodeManager->jumpPointScroll(), ProcessNodeManager, &StringBoxInputJumpPoint);
	StringBoxInputJumpPoint.rootUi()->setPos(VECTOR2(32.0f, 76.0f));
	rootUi->addChilds(StringBoxInputJumpPoint.rootUi());
}
PROCESS_NODE_JUMP::~PROCESS_NODE_JUMP() {
	disconnect(this);
}

std::pair<PROCESS_NODE_CONNECTOR_IN**, int> PROCESS_NODE_JUMP::allNodeConnectorIn(){
	return { &NodeConnectorFront_, 1 };
}

std::pair<PROCESS_NODE_CONNECTOR_OUT**, int> PROCESS_NODE_JUMP::allNodeConnectorOut(){
	return { nullptr,0 };
}

std::string PROCESS_NODE_JUMP::saveDataString(){
	return PROCESS_NODE_SAVE::commonSaveDataString(PROCESS_NODE_SAVE::getTypeStringName(PROCESS_NODE_TYPE::JUMP), rootUi()->pos()) +
		"jump_point{" + StringBoxInputJumpPoint.inputBoxUiDrawer()->string() + "}";
}

void PROCESS_NODE_JUMP::loadFromSaveString(const STRING_TREE& data){
	rootUi()->setPos(PROCESS_NODE_LOAD::loadSaveDataStringPos(data));
	int idx = data.findData("jump_point");
	if (idx != -1) {
		StringBoxInputJumpPoint.inputBoxUiDrawer()->setString(data.childs()[idx]->data());
	}
}

void PROCESS_NODE_JUMP::compile(ROBOT_COMPILER* robotCompiler){
	robotCompiler->checkJumpPoint(StringBoxInputJumpPoint.inputBoxUiDrawer()->string());
}

void PROCESS_NODE_JUMP::nextStep(ROBOT_PROCESSOR* robotProcessor){
	if (robotProcessor->stepCnt()) {
		//1フレームのプロセス数の上限に達した
		robotProcessor->oneFrameProcessEnd(this);
	}
	else {
		//次のノードへ処理を続行
		const std::string& jumpPointName = StringBoxInputJumpPoint.inputBoxUiDrawer()->string();
		if (robotProcessor->jumpPointList().contains(jumpPointName)) {//対応するジャンプポイントがあれば
			robotProcessor->jumpPointList()[jumpPointName]->nextStep(robotProcessor);
		}
		else {
			robotProcessor->JumpBackReturn();
		}
	}
}

void PROCESS_NODE_JUMP::setEnable(){
}

void PROCESS_NODE_JUMP::setDisable(){
}
