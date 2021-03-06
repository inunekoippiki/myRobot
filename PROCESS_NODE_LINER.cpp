#include "../Library/COLOR.h"
#include "../Library/CONTAINER.h"
#include "DRAWER_ARROW.h"
#include "PROCESS_NODE.h"
#include "PROCESS_NODE_CONNECTOR.h"
#include "PROCESS_NODE_MANAGER.h"
#include "PROCESS_NODE_COMMAND/FACTORY.h"
#include "SOUND_MANAGER.h"
#include "PROCESS_NODE_LINER.h"
PROCESS_NODE_LINER::PROCESS_NODE_LINER() {
}


PROCESS_NODE_LINER::~PROCESS_NODE_LINER() {
}

void PROCESS_NODE_LINER::create(PROCESS_NODE_MANAGER* processNodeManager, CONTAINER* c, DRAWER::DRAWERS_SHADER* drawers) {
	ProcessNodeManager = processNodeManager;
	NodeLine.create(drawers, c, processNodeManager);
	NodeLine.noneLine();
	NodeLine.setBendLength(16.0f);
	NodeLine.setLineWidth(4.0f);
	NodeLine.drawer()->setColor(COLOR(1.0f, 1.0f, 1.0f, 0.6f));

	SoundLineConnect = c->sound("lineConnect");
}

void PROCESS_NODE_LINER::overlapConnectorIn(PROCESS_NODE_CONNECTOR_IN* connectorIn){
	if (SelectedConnectOut != nullptr) {
		NodeLine.drawer()->setColor(COLOR(1.0f, 0.0f, 0.0f, 0.8f));
	}
}

void PROCESS_NODE_LINER::overlapEndConnectorIn(PROCESS_NODE_CONNECTOR_IN* connectorIn){
	NodeLine.drawer()->setColor(COLOR(1.0f, 1.0f, 1.0f, 0.6f));
}

void PROCESS_NODE_LINER::mouseDragUpdate(const VECTOR2& pos){
	MousePos = pos;
	if (SelectedConnectOut!=nullptr) {
		NodeLine.pointsUpdate(SelectedConnectOut->rootUi()->centerPos(), MousePos);
	}
}
 
void PROCESS_NODE_LINER::selectProcessNode(PROCESS_NODE_CONNECTOR_OUT* connectorOut) {
	SelectedConnectIn = nullptr;
	SelectedConnectOut = connectorOut;
}

void PROCESS_NODE_LINER::selectReleaseProcessNode(){
	if (SelectedConnectIn != nullptr) {//開始選択していたら
		if (SelectedConnectIn == SelectedConnectOut->cnnectorNext()) {//繋げようとしたノードが既に同じノードに繋がっている
			//線を切るコマンド
			auto command = PROCESS_NODE_COMMAND::instanceDisconnect(SelectedConnectOut, this);
			ProcessNodeManager->commandStream()->push(command);
			command->execute();
		}
		else{
			//線を繋ぐコマンド
			auto command = PROCESS_NODE_COMMAND::instanceConnect(SelectedConnectOut, SelectedConnectIn, this);
			ProcessNodeManager->commandStream()->push(command);
			command->execute();
			SOUND_MANAGER::instance()->playSound(SoundLineConnect);
		}
	}
	else{
		//線を切るコマンド
		auto command = PROCESS_NODE_COMMAND::instanceDisconnect(SelectedConnectOut, this);
		ProcessNodeManager->commandStream()->push(command);
		command->execute();
	}
	SelectedConnectOut = nullptr;
	NodeLine.noneLine();
}

void PROCESS_NODE_LINER::decisionProcessNode(PROCESS_NODE_CONNECTOR_IN* connectorIn) {
	auto allIn = SelectedConnectOut->processNode()->allNodeConnectorIn();
	for (int i = 0;i < allIn.second;i++) {
		if (allIn.first[i] == connectorIn) {
			SelectedConnectIn = nullptr;
			return;
		}
	}
	SelectedConnectIn = connectorIn;
}

void PROCESS_NODE_LINER::connect(PROCESS_NODE_CONNECTOR_OUT* connectorOut,PROCESS_NODE_CONNECTOR_IN* connectorIn){
	if (connectorOut->cnnectorNext() != nullptr) {//既に次のノードに繋がっていたら
		connectorOut->cnnectorNext()->setConnectorFront(nullptr);//次のノードの繋がりを切る
	}
	connectorOut->setConnectorNext(connectorIn);//次のノードとつなげる
	if (connectorIn->connectorFront() != nullptr) {//既に繋げ先ノードが前のノードと繋がっていたら
		connectorIn->connectorFront()->setConnectorNext(nullptr);//繋げ先ノードの前のノードつながりを切る
	}
	connectorIn->setConnectorFront(connectorOut);//繋げ先ノードを開始選択ノードにつなげる

}

void PROCESS_NODE_LINER::disconnect(PROCESS_NODE* processNode){
	auto allIn = processNode->allNodeConnectorIn();
	for (int i = 0;i < allIn.second;i++) {
		disconnect(allIn.first[i]);
	}
	auto allOut = processNode->allNodeConnectorOut();
	for (int i = 0;i < allOut.second;i++) {
		disconnect(allOut.first[i]);
	}
}

void PROCESS_NODE_LINER::disconnect(PROCESS_NODE_CONNECTOR_IN* connectorIn){
	if (connectorIn->connectorFront() != nullptr) {
		connectorIn->connectorFront()->setConnectorNext(nullptr);
		connectorIn->setConnectorFront(nullptr);
	}
}

void PROCESS_NODE_LINER::disconnect(PROCESS_NODE_CONNECTOR_OUT* connectorOut){
	if (connectorOut->cnnectorNext() != nullptr) {
		connectorOut->cnnectorNext()->setConnectorFront(nullptr);
		connectorOut->setConnectorNext(nullptr);
	}
}

