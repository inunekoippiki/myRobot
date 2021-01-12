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
#include "PROCESS_NODE_WAIT.h"
PROCESS_NODE_WAIT::PROCESS_NODE_WAIT(CONTAINER* c, STATIC_FONT* font, DRAWER::DRAWERS_SHADER* lineDrawers, PROCESS_NODE_LINER* processNodeLiner, PROCESS_NODE_MANAGER* processNodeManager) :
	ProcessNodeManager(processNodeManager),
	StringBoxWait(c, font, UI_INPUT_BOX::INPUT_TYPE::KEY_PULLDOWN,processNodeManager),
	NodeConnectorFront(c,this, processNodeLiner),
	NodeConnectorBack(c,this,lineDrawers, processNodeLiner, processNodeManager),
	NodeConnectorFront_(&NodeConnectorFront),
	NodeConnectorBack_(&NodeConnectorBack){

	Frame.create(this, c->texture("processNodeBack"), ProcessNodeManager);
	UI* rootUi = Frame.rootUi();
	NodeTypeNameUi = UI_FACTORY::instance(DRAWER::STATIC_FONT::instance("時間ノード", font, VECTOR2(), VECTOR2(24.0f, 24.0f), DRAWER::STATIC_FONT::drawMethodDefault()));
	NodeTypeNameUi->setIsCollisionDisable(true);
	rootUi->addChilds(NodeTypeNameUi);
	//コネクターの設定
	NodeConnectorFront.rootUi()->setPos(VECTOR2(8.0f, 80.0f));
	rootUi->addChilds(NodeConnectorFront.rootUi());
	NodeConnectorBack.rootUi()->setPos(VECTOR2(232.0f, 80.0f));
	rootUi->addChilds(NodeConnectorBack.rootUi());
	//入力ボックス
	startKeyboardInput(StringBoxWait.keyInputUi(), ProcessNodeManager, &StringBoxWait);
	startScrollInput(StringBoxWait.pulldownInputUi(), ProcessNodeManager->variableScroll(), ProcessNodeManager, &StringBoxWait);
	StringBoxWait.rootUi()->setPos(VECTOR2(32.0f, 76.0f));
	rootUi->addChilds(StringBoxWait.rootUi());
	StringBoxWait.setString("0");
}
PROCESS_NODE_WAIT::~PROCESS_NODE_WAIT() {
	disconnect(this);
}

std::pair<PROCESS_NODE_CONNECTOR_IN**, int> PROCESS_NODE_WAIT::allNodeConnectorIn() {
	return { &NodeConnectorFront_,1 };
}

std::pair<PROCESS_NODE_CONNECTOR_OUT**, int> PROCESS_NODE_WAIT::allNodeConnectorOut() {
	return { &NodeConnectorBack_ ,1 };
}

std::string PROCESS_NODE_WAIT::saveDataString() {
	return PROCESS_NODE_SAVE::commonSaveDataString(PROCESS_NODE_SAVE::getTypeStringName(PROCESS_NODE_TYPE::WAIT), rootUi()->pos()) +
		"variable{" + StringBoxWait.string() + "}";
}

void PROCESS_NODE_WAIT::loadFromSaveString(const STRING_TREE& data) {
	rootUi()->setPos(PROCESS_NODE_LOAD::loadSaveDataStringPos(data));
	int idx = data.findData("variable");
	if (idx != -1) {
		StringBoxWait.setString(data.childs()[idx]->data());
	}
}

void PROCESS_NODE_WAIT::compile(ROBOT_COMPILER* robotCompiler){
	robotCompiler->addVariable(StringBoxWait.uiInputBoxVariable());
}

void PROCESS_NODE_WAIT::nextStep(ROBOT_PROCESSOR* robotProcessor){
	robotProcessor->addTime();
	if (robotProcessor->variable(StringBoxWait.string()) > robotProcessor->waitFrameTime()) {
		robotProcessor->oneFrameProcessEnd(this);
	}
	else {
		robotProcessor->resetTime();
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
}

void PROCESS_NODE_WAIT::setEnable(){
	StringBoxWait.setEnable();
}

void PROCESS_NODE_WAIT::setDisable(){
	StringBoxWait.setDisable();
}

