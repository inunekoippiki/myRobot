#include "../Library/CONTAINER.h"
#include "../Library/INDEV.h"
#include "INPUT_COMMON.h"
#include "NODE_LINE.h"
#include "UI_FACTORY.h"
#include "PROCESS_NODE_MANAGER.h"
#include "PROCESS_NODE_COMMAND/FACTORY.h"
#include "LINE_POINT.h"
LINE_POINT::LINE_POINT(){
}

void LINE_POINT::create(CONTAINER* c, int pointIdx,const VECTOR2& pos, NODE_LINE* nodeLine, PROCESS_NODE_MANAGER* processNodeManager){
	ProcessNodeManager = processNodeManager;
	NodeLine = nodeLine;
	RootUi = UI_FACTORY::instance(c->texture("linePointIcon"), pos, VECTOR2::one());
	//§Œä“_‚Ì‘€ì‚ÍAndoRedo‚ª‘S‚Ä‘Î‰ž‚Å‚«‚é‚Ü‚Å–³Œø‚É‚µ‚Ä‚¨‚­
	RootUi->setIsCollisionDisable(true);
	RootUi->setDownFunc([this]() {onDown();});
	RootUi->setDragUpdate([this]() {onDragUpdate();});
	RootUi->setDragEndFunc([this]() {onDragEnd();});
	RootUi->setIsReleaseDisable(true);
	PointIdx = pointIdx;
}

LINE_POINT::~LINE_POINT(){
	SAFE_DELETE(RootUi);
}

VECTOR2 LINE_POINT::uiPos() const{
	return ProcessNodeManager->processNodeListUi()->worldPosToLocalPos(RootUi->pos() + RootUi->drawer()->wh() * 0.5f);
}

void LINE_POINT::onDown(){
	OldPos = uiPos();
}

void LINE_POINT::onDragUpdate(){
	INDEV* indev = INDEV::instance();
	VECTOR2 v = INPUT_COMMON::MouseRelativeValue(indev) / RootUi->absoluteScale();
	move(v);
}

void LINE_POINT::onDragEnd(){
	auto command = PROCESS_NODE_COMMAND::instanceLineMove(uiPos(),OldPos, this);
	ProcessNodeManager->commandStream()->push(command);
	OldPos = VECTOR2();
}

void LINE_POINT::setUiPos(const VECTOR2& pos){
	RootUi->setPos(pos - RootUi->drawer()->wh() * 0.5f);
}

void LINE_POINT::setPos(const VECTOR2& pos){
	NodeLine->pointsUpdate(PointIdx, ProcessNodeManager->processNodeListUi()->localPosToWorldPos(pos));
	NodeLine->linePointUpdate();
}

void LINE_POINT::move(const VECTOR2& v){
	NodeLine->pointsUpdate(PointIdx, NodeLine->points()[PointIdx] + v);
	NodeLine->linePointUpdate();
}

void LINE_POINT::setIsDisable(bool isDisable){
	RootUi->setIsDisable(isDisable);
}
