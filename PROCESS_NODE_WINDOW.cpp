#include <utility>
#include "../Library/GRAPHIC.h"
#include "../Library/CONTAINER.h"
#include "../Library/INDEV.h"
#include "../Library/STRING_TREE.h"
#include "INPUT_COMMON.h"
#include "DRAWER_IMAGE2D_TILING.h"
#include "UI_FACTORY.h"
#include "PROCESS_NODE_MANAGER.h"
#include "PROCESS_NODE_SELECTOR.h"
#include "PROCESS_NODE_WINDOW_OPERATOR.h"
#include "PROCESS_NODE.h"
#include "PROCESS_NODE_CONNECTOR.h"
#include "PROCESS_NODE_WINDOW.h"
PROCESS_NODE_WINDOW::PROCESS_NODE_WINDOW() {
}

PROCESS_NODE_WINDOW::~PROCESS_NODE_WINDOW() {
}

void PROCESS_NODE_WINDOW::create(
	CONTAINER* c,
	STRING_TREE* rootST,
	PROCESS_NODE_SELECTOR* processNodeSelector,
	PROCESS_NODE_MANAGER* processNodeManager){

	ProcessNodeSelector = processNodeSelector;
	ProcessNodeManager = processNodeManager;

	GRAPHIC* g = GRAPHIC::instance();

	ProcessNodeWindowOperator.create(rootST->atw("processNodeWindowOperator"));
	//プロセスノードが入るウインドウを作る
	ProcessNodeListUi = new UI;
	//画像がタイリング表示されるDRAWERを作る
	DRAWER::IMAGE2D_TILING* drawer = new DRAWER::IMAGE2D_TILING;
	drawer->setPos(VECTOR2(0.0f, 0.0f));
	drawer->setTexture(c->texture("processNodeEditBack"));
	drawer->setRangePosSt(VECTOR2(0.0f, 0.0f));
	drawer->setRangePosEd(VECTOR2(g->baseWidth(), g->baseHeight()));
	ProcessNodeListUi->create(drawer);
	ProcessNodeListUi->setScale(VECTOR2(ProcessNodeWindowOperator.zoomInitValueZoom(), ProcessNodeWindowOperator.zoomInitValueZoom()));
	ProcessNodeListUi->setIsUnconditionalCollisionHit(true);
	ProcessNodeListUi->setDownFunc([this]() {onDownWindow();});
	ProcessNodeListUi->setDragUpdate([this]() {onDragWindow();});
	ProcessNodeListUi->setDragEndFunc([this]() {onUpWindow();});
	//制御点が入るレイヤーを作る
	ProcessNodeLinePointListUi = UI_FACTORY::instanceEmpty();

	//ウインドウ操作
	{
		CameraOperationUi = UI_FACTORY::instanceEmpty();
		CameraScrollCenterUi = UI_FACTORY::instance(c->texture("windowScrolCenter"), VECTOR2(111.0f, 911.0f), VECTOR2::one());
		CameraScrollCenterUi->setDownFunc([this]() {onDownCameraButton();});
		CameraScrollCenterUi->setDragUpdate([this]() {onDragCameraButton();});
		CameraOperationUi->addChilds(CameraScrollCenterUi);
		CameraScrollUpUi = UI_FACTORY::instance(c->texture("windowScrolUp"), VECTOR2(111.0f, 838.0f), VECTOR2::one());
		CameraScrollUpUi->setDragUpdate([this]() {this->designWindowMove(VECTOR2(0.0f, -1.0f));});
		CameraOperationUi->addChilds(CameraScrollUpUi);
		CameraScrollDownUi = UI_FACTORY::instance(c->texture("windowScrolDown"), VECTOR2(111.0f, 985.0f), VECTOR2::one());
		CameraScrollDownUi->setDragUpdate([this]() {this->designWindowMove(VECTOR2(0.0f, 1.0f));});
		CameraOperationUi->addChilds(CameraScrollDownUi);
		CameraScrollLeftUi = UI_FACTORY::instance(c->texture("windowScrolLeft"), VECTOR2(37.0f, 911.0f), VECTOR2::one());
		CameraScrollLeftUi->setDragUpdate([this]() {this->designWindowMove(VECTOR2(-1.0f, 0.0f));});
		CameraOperationUi->addChilds(CameraScrollLeftUi);
		CameraScrollRightUi = UI_FACTORY::instance(c->texture("windowScrolRight"), VECTOR2(184.0f, 911.0f), VECTOR2::one());
		CameraScrollRightUi->setDragUpdate([this]() {this->designWindowMove(VECTOR2(1.0f, 0.0f));});
		CameraOperationUi->addChilds(CameraScrollRightUi);
		CameraZoomInUi = UI_FACTORY::instance(c->texture("windowZoomInIcon"), VECTOR2(317.0f, 851.0f), VECTOR2::one());
		CameraZoomInUi->setPushFunc([this]() {this->designWindowZoomIn();});
		CameraOperationUi->addChilds(CameraZoomInUi);
		CameraZoomOutUi = UI_FACTORY::instance(c->texture("windowZoomOutIcon"), VECTOR2(317.0f, 974.0f), VECTOR2::one());
		CameraZoomOutUi->setPushFunc([this]() {this->designWindowZoomOut();});
		CameraOperationUi->addChilds(CameraZoomOutUi);
	}

}

void PROCESS_NODE_WINDOW::onDownWindow(){
	ProcessNodeSelector->mouseDown(ProcessNodeListUi->worldPosToLocalPos(INPUT_COMMON::MousePosition(INDEV::instance())));
}

void PROCESS_NODE_WINDOW::onDragWindow(){
	VECTOR2 mousePos = INPUT_COMMON::MousePosition(INDEV::instance());
	ProcessNodeSelector->mouseDragUpdate(ProcessNodeListUi->worldPosToLocalPos(mousePos));
	autoDesignWindowMove();
}

void PROCESS_NODE_WINDOW::onUpWindow(){
	ProcessNodeSelector->mouseUp();
}

void PROCESS_NODE_WINDOW::onDownCameraButton(){
	MouseDownPos = INPUT_COMMON::MousePosition(INDEV::instance());
}

void PROCESS_NODE_WINDOW::onDragCameraButton(){
	VECTOR2 move = (INPUT_COMMON::MousePosition(INDEV::instance()) - MouseDownPos) / ProcessNodeListUi->absoluteScale();
	if (!move.isZero()) {
		designWindowMove(normalize(move));
	}
}

void PROCESS_NODE_WINDOW::addProcessNodeLineUpdate() {
	for (auto i : ProcessNodeManager->processNodeList()) {
		auto allNodeConnectorOut = i->allNodeConnectorOut();
		for (int i2 = 0;i2 < allNodeConnectorOut.second;i2++) {
			allNodeConnectorOut.first[i2]->moveLine();
		}
	}
}

void PROCESS_NODE_WINDOW::designWindowZoom(float scaleAmount, const VECTOR2& localCenter) {
	ProcessNodeListUi->setScale(ProcessNodeListUi->scale() + VECTOR2(scaleAmount, scaleAmount));
	for (auto& i : ProcessNodeManager->processNodeList()) {
		auto allNodeConnectorOut = i->allNodeConnectorOut();
		for (int i2 = 0;i2 < allNodeConnectorOut.second;i2++) {
			allNodeConnectorOut.first[i2]->rescaleLine();
		}
	}
	ProcessNodeListUi->setPos(ProcessNodeListUi->pos() - (localCenter * VECTOR2(scaleAmount, scaleAmount)));
	for (auto& i : ProcessNodeManager->processNodeList()) {
		auto allNodeConnectorOut = i->allNodeConnectorOut();
		for (int i2 = 0;i2 < allNodeConnectorOut.second;i2++) {
			allNodeConnectorOut.first[i2]->moveLine();
		}
	}
	ProcessNodeSelector->drawerUpdate();
}

void PROCESS_NODE_WINDOW::designWindowZoomIn() {
	GRAPHIC* g = GRAPHIC::instance();
	designWindowZoom(ProcessNodeWindowOperator.zoomIn(), ProcessNodeListUi->worldPosToLocalPos(VECTOR2(g->baseWidth() * 0.5f, g->baseHeight() * 0.5f)));
}

void PROCESS_NODE_WINDOW::designWindowZoomOut() {
	GRAPHIC* g = GRAPHIC::instance();
	designWindowZoom(ProcessNodeWindowOperator.zoomOut(), ProcessNodeListUi->worldPosToLocalPos(VECTOR2(g->baseWidth() * 0.5f, g->baseHeight() * 0.5f)));
}

void PROCESS_NODE_WINDOW::designWindowMove(const VECTOR2& moveAmount) {
	ProcessNodeListUi->setPos(ProcessNodeListUi->pos() - ProcessNodeWindowOperator.moveAmount(moveAmount));
	addProcessNodeLineUpdate();
	ProcessNodeSelector->drawerUpdate();
}

void PROCESS_NODE_WINDOW::autoDesignWindowMove() {
	GRAPHIC* g = GRAPHIC::instance();
	VECTOR2 mousePos = INPUT_COMMON::MousePosition(INDEV::instance());
	if (mousePos.x <= 1.0f) {
		designWindowMove(VECTOR2(-1.0f, 0.0f));
	}
	if (mousePos.x >= g->baseWidth() - 1.0f) {
		designWindowMove(VECTOR2(1.0f, 0.0f));
	}
	if (mousePos.y <= 1.0f) {
		designWindowMove(VECTOR2(0.0f, -1.0f));
	}
	if (mousePos.y >= g->baseHeight() - 1.0f) {
		designWindowMove(VECTOR2(0.0f, 1.0f));
	}
}