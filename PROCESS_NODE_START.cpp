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
#include "PROCESS_NODE_START.h"
PROCESS_NODE_START::PROCESS_NODE_START(CONTAINER* c, STATIC_FONT* font, DRAWER::DRAWERS_SHADER* lineDrawers, PROCESS_NODE_LINER* processNodeLiner, PROCESS_NODE_MANAGER* processNodeManager):
	ProcessNodeManager(processNodeManager),
	NodeConnectorBack(c,this,lineDrawers, processNodeLiner, processNodeManager),
	NodeConnectorBack_(&NodeConnectorBack){
	Frame.create(this, c->texture("processNodeBack"), ProcessNodeManager);
	UI* rootUi = Frame.rootUi();
	NodeTypeNameUi = UI_FACTORY::instance(DRAWER::STATIC_FONT::instance("開始ノード", font, VECTOR2(), VECTOR2(24.0f, 24.0f), DRAWER::STATIC_FONT::drawMethodDefault()));
	NodeTypeNameUi->setIsCollisionDisable(true);
	rootUi->addChilds(NodeTypeNameUi);
	//コネクター
	NodeConnectorBack.rootUi()->setPos(VECTOR2(232.0f, 80.0f));
	rootUi->addChilds(NodeConnectorBack.rootUi());

}
PROCESS_NODE_START::~PROCESS_NODE_START() {
	disconnect(this);
}

std::pair<PROCESS_NODE_CONNECTOR_IN**, int> PROCESS_NODE_START::allNodeConnectorIn(){
	return {nullptr,0};
}

std::pair<PROCESS_NODE_CONNECTOR_OUT**, int> PROCESS_NODE_START::allNodeConnectorOut(){
	return { &NodeConnectorBack_ ,1};
}

std::string PROCESS_NODE_START::saveDataString(){
	return PROCESS_NODE_SAVE::commonSaveDataString(PROCESS_NODE_SAVE::getTypeStringName(PROCESS_NODE_TYPE::START), rootUi()->pos());
}

void PROCESS_NODE_START::loadFromSaveString(const STRING_TREE& data){
	rootUi()->setPos(PROCESS_NODE_LOAD::loadSaveDataStringPos(data));
}

void PROCESS_NODE_START::compile(ROBOT_COMPILER* robotCompiler){
	robotCompiler->setProcessNodeStart(this);
}

void PROCESS_NODE_START::nextStep(ROBOT_PROCESSOR* robotProcessor){
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
			robotProcessor->ProcessEnd();
		}
	}
}

void PROCESS_NODE_START::setEnable(){
}

void PROCESS_NODE_START::setDisable(){
}
