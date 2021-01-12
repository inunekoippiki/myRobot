#include "../Library/common.h"
#include "../Library/CONTAINER.h"
#include "../Library/INDEV.h"
#include "INPUT_COMMON.h"
#include "DRAWER_IMAGE2D.h"
#include "PROCESS_NODE.h"
#include "NODE_LINE.h"
#include "UI.h"
#include "UI_FUNC_ATTACHER.h"
#include "PROCESS_NODE_LINER.h"
#include "UI_FACTORY.h"
#include "PROCESS_NODE_CONNECTOR.h"
PROCESS_NODE_CONNECTOR_IN::PROCESS_NODE_CONNECTOR_IN(CONTAINER* c, PROCESS_NODE* processNode, PROCESS_NODE_LINER* processNodeLiner) :
	ProcessNode(processNode), 
	ProcessNodeLiner(processNodeLiner) {
	DRAWER::IMAGE2D* drawer = DRAWER::IMAGE2D::instance(c->texture("nodeConnectorIcon"), VECTOR2(8.0f, 80.0f), VECTOR2::one());
	create(drawer);
}

PROCESS_NODE_CONNECTOR_IN::PROCESS_NODE_CONNECTOR_IN(PROCESS_NODE_CONNECTOR_TYPE type, CONTAINER* c, PROCESS_NODE* processNode, PROCESS_NODE_LINER* processNodeLiner) :
	ProcessNode(processNode), 
	ProcessNodeLiner(processNodeLiner) {
	DRAWER::IMAGE2D* drawer = nullptr;
	switch (type){
	case PROCESS_NODE_CONNECTOR_TYPE::THEN:
		drawer = DRAWER::IMAGE2D::instance(c->texture("nodeConnectorIcon"), VECTOR2(8.0f, 80.0f), VECTOR2::one());
		break;
	case PROCESS_NODE_CONNECTOR_TYPE::ELSE:
		drawer = DRAWER::IMAGE2D::instance(c->texture("nodeConnectorElseIcon"), VECTOR2(8.0f, 80.0f), VECTOR2::one());
		break;
	default:
		WARNING(true, "PROCESS_NODE_CONNECTOR_TYPE範囲外", "");
		break;
	}
	create(drawer);
}

PROCESS_NODE_CONNECTOR_IN::~PROCESS_NODE_CONNECTOR_IN() {
}

void PROCESS_NODE_CONNECTOR_IN::setConnectorFront(PROCESS_NODE_CONNECTOR_OUT* connectorFront){
	ConnectorFront = connectorFront;
}

void PROCESS_NODE_CONNECTOR_IN::create(DRAWER::IMAGE2D* drawer){
	RootUi = UI_FACTORY::instance(drawer);
	RootUi->setUpFunc([this]() {this->ProcessNodeLiner->decisionProcessNode(this);});
	RootUi->setOverlapIn([this, drawer]() {
		this->ProcessNodeLiner->overlapConnectorIn(this);
		drawer->setColor(COLOR(0.0f, 0.0f, 0.0f, 0.7f));}
	);
	RootUi->setOverlapOut([this, drawer]() {
		this->ProcessNodeLiner->overlapEndConnectorIn(this);
		drawer->setColor(COLOR(1.0f, 1.0f, 1.0f, 1.0f));}
	);
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

PROCESS_NODE_CONNECTOR_OUT::PROCESS_NODE_CONNECTOR_OUT(
	CONTAINER* c, 
	PROCESS_NODE* processNode, 
	DRAWER::DRAWERS_SHADER* lineDrawers, 
	PROCESS_NODE_LINER* processNodeLiner,
	PROCESS_NODE_MANAGER* processNodeManager) :
	ProcessNode(processNode),
	ProcessNodeLiner(processNodeLiner){
	DRAWER::IMAGE2D* drawer = DRAWER::IMAGE2D::instance(c->texture("nodeConnectorIcon"), VECTOR2(232.0f, 80.0f), VECTOR2::one());
	create(drawer, c, lineDrawers, processNodeManager);
}

PROCESS_NODE_CONNECTOR_OUT::PROCESS_NODE_CONNECTOR_OUT(
	PROCESS_NODE_CONNECTOR_TYPE type, 
	CONTAINER* c, 
	PROCESS_NODE* processNode,
	DRAWER::DRAWERS_SHADER* lineDrawers,
	PROCESS_NODE_LINER* processNodeLiner,
	PROCESS_NODE_MANAGER* processNodeManager) :
	ProcessNode(processNode),
	ProcessNodeLiner(processNodeLiner) {
	DRAWER::IMAGE2D* drawer = nullptr;
	switch (type) {
	case PROCESS_NODE_CONNECTOR_TYPE::THEN:
		drawer = DRAWER::IMAGE2D::instance(c->texture("nodeConnectorIcon"), VECTOR2(8.0f, 80.0f), VECTOR2::one());
		break;
	case PROCESS_NODE_CONNECTOR_TYPE::ELSE:
		drawer = DRAWER::IMAGE2D::instance(c->texture("nodeConnectorElseIcon"), VECTOR2(8.0f, 80.0f), VECTOR2::one());
		break;
	default:
		WARNING(true, "PROCESS_NODE_CONNECTOR_TYPE範囲外", "");
		break;
	}
	create(drawer, c, lineDrawers, processNodeManager);
}

PROCESS_NODE_CONNECTOR_OUT::~PROCESS_NODE_CONNECTOR_OUT(){
	delete NodeLine;
}

void PROCESS_NODE_CONNECTOR_OUT::setConnectorNext(PROCESS_NODE_CONNECTOR_IN* connectorNext){
	ConnectorNext = connectorNext;
	updateLine();
}

void PROCESS_NODE_CONNECTOR_OUT::updateLine() {
	//ノードに線が被らないように幅とか高さとかを計算して
	//ラインを適切に曲げる
	if (ConnectorNext != nullptr) {
		float h = 0.0f;
		if (rootUi()->absolutePos().y > ConnectorNext->rootUi()->absolutePos().y) {
			//このコネクターが繋がっている次のコネクターより下にあったら

			//このコネクターの中心の位置
			float h1 = RootUi->pos().y * RootUi->absoluteScale().y + RootUi->collision()->wh().y * 0.5f;
			//次のコネクターの中心の位置
			float h2 = ConnectorNext->processNode()->rootUi()->collision()->wh().y - ConnectorNext->rootUi()->pos().y * ConnectorNext->rootUi()->absoluteScale().y - ConnectorNext->rootUi()->collision()->wh().y * 0.5f;
			h = h1 / (h1 + h2);
		}
		else{
			//このコネクターが繋がっている次のコネクターより上にあったら

			//次のコネクターの中心の位置
			float h1 = (ProcessNode->rootUi()->collision()->wh().y - RootUi->pos().y * RootUi->absoluteScale().y - RootUi->collision()->wh().y * 0.5f);
			//このコネクターの中心の位置
			float h2 = ConnectorNext->rootUi()->pos().y * ConnectorNext->rootUi()->absoluteScale().y + ConnectorNext->rootUi()->collision()->wh().y * 0.5f;
			h = h1 / (h1 + h2);
		}
		//横の曲げる割合は固定
		float w = 0.5f;
		NodeLine->pointsUpdate(RootUi->centerPos(), ConnectorNext->rootUi()->centerPos(), w, h);
	}
	else {
		NodeLine->noneLine();
	}
}

void PROCESS_NODE_CONNECTOR_OUT::moveLine() {
	if (ConnectorNext != nullptr) {
		NodeLine->movePoints(RootUi->centerPos(),ConnectorNext->rootUi()->centerPos());
	}
}

void PROCESS_NODE_CONNECTOR_OUT::rescaleLine() {
	if (ConnectorNext != nullptr) {
		NodeLine->rescalePoints(RootUi->centerPos(),ConnectorNext->rootUi()->centerPos());
	}
}

void PROCESS_NODE_CONNECTOR_OUT::onDown(){
	ProcessNodeLiner->selectProcessNode(this);
}

void PROCESS_NODE_CONNECTOR_OUT::onDragUpdate(){
	ProcessNodeLiner->mouseDragUpdate(INPUT_COMMON::MousePosition(INDEV::instance()));
}

void PROCESS_NODE_CONNECTOR_OUT::onDragEnd(){
	ProcessNodeLiner->selectReleaseProcessNode();
}

void PROCESS_NODE_CONNECTOR_OUT::create(DRAWER::IMAGE2D* drawer,CONTAINER* c, DRAWER::DRAWERS_SHADER* lineDrawers,PROCESS_NODE_MANAGER* processNodeManager){
	RootUi = UI_FACTORY::instance(drawer);
	//ノード同士の接続はPROCESS_NODE_LINERにしてもらう。そのためのファンクションの設定
	RootUi->setDownFunc([this]() {onDown();});
	RootUi->setDragUpdate([this]() {onDragUpdate();});
	RootUi->setDragEndFunc([this]() {onDragEnd();});
	//翳すと色変わるようにする
	UI_FUNC_ATTACHER::OverlapAlphaColorChange(RootUi, drawer);
	//線の設定
	NodeLine = new NODE_LINE();
	NodeLine->create(lineDrawers, c, processNodeManager);
	NodeLine->setBendLength(16.0f);
	NodeLine->setLineWidth(4.0f);
	NodeLine->noneLine();
}
