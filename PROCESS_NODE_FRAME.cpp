#include "../Library/INDEV.h"
#include "INPUT_COMMON.h"
#include "UI_FACTORY.h"
#include "PROCESS_NODE.h"
#include "PROCESS_NODE_CONNECTOR.h"
#include "PROCESS_NODE_MANAGER.h"
#include "PROCESS_NODE_COMMAND/FACTORY.h"
#include "PROCESS_NODE_FRAME.h"
PROCESS_NODE_FRAME::PROCESS_NODE_FRAME() {
}

PROCESS_NODE_FRAME::~PROCESS_NODE_FRAME() {
	SAFE_DELETE(RootUi);
}

void PROCESS_NODE_FRAME::create(PROCESS_NODE* owner,TEXTURE* texture,PROCESS_NODE_MANAGER* processNodeManager){
	Owner = owner;
	ProcessNodeManager = processNodeManager;

	RootUi = UI_FACTORY::instance(texture, VECTOR2(), VECTOR2::one());
	RootUi->setDownFunc([this]() {onDown();});
	RootUi->setDragUpdate([this]() {onDrag();});
	RootUi->setDragEndFunc([this]() {onDragEnd();});
	RootUi->setIsReleaseDisable(true);
	RootUi->setIsChildCollisionRestrict(true);
}

void PROCESS_NODE_FRAME::onDown(){
	OldPos = RootUi->pos();
}

void PROCESS_NODE_FRAME::onDragEnd(){
	auto command = PROCESS_NODE_COMMAND::instanceMove(Owner, RootUi->pos(), OldPos, ProcessNodeManager);
	ProcessNodeManager->commandStream()->push(command);
}

void PROCESS_NODE_FRAME::onDrag(){
	INDEV* indev = INDEV::instance();
	UI* rootUi = Owner->rootUi();
	rootUi->setPos(rootUi->pos() + INPUT_COMMON::MouseRelativeValue(indev) / rootUi->parentScale());
	PROCESS_NODE::lineUpdate(Owner);
	ProcessNodeManager->processNodeSelectorUpdate();
}
