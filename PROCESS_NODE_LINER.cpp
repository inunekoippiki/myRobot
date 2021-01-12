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
	if (SelectedConnectIn != nullptr) {//�J�n�I�����Ă�����
		if (SelectedConnectIn == SelectedConnectOut->cnnectorNext()) {//�q���悤�Ƃ����m�[�h�����ɓ����m�[�h�Ɍq�����Ă���
			//����؂�R�}���h
			auto command = PROCESS_NODE_COMMAND::instanceDisconnect(SelectedConnectOut, this);
			ProcessNodeManager->commandStream()->push(command);
			command->execute();
		}
		else{
			//�����q���R�}���h
			auto command = PROCESS_NODE_COMMAND::instanceConnect(SelectedConnectOut, SelectedConnectIn, this);
			ProcessNodeManager->commandStream()->push(command);
			command->execute();
			SOUND_MANAGER::instance()->playSound(SoundLineConnect);
		}
	}
	else{
		//����؂�R�}���h
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
	if (connectorOut->cnnectorNext() != nullptr) {//���Ɏ��̃m�[�h�Ɍq�����Ă�����
		connectorOut->cnnectorNext()->setConnectorFront(nullptr);//���̃m�[�h�̌q�����؂�
	}
	connectorOut->setConnectorNext(connectorIn);//���̃m�[�h�ƂȂ���
	if (connectorIn->connectorFront() != nullptr) {//���Ɍq����m�[�h���O�̃m�[�h�ƌq�����Ă�����
		connectorIn->connectorFront()->setConnectorNext(nullptr);//�q����m�[�h�̑O�̃m�[�h�Ȃ����؂�
	}
	connectorIn->setConnectorFront(connectorOut);//�q����m�[�h���J�n�I���m�[�h�ɂȂ���

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

