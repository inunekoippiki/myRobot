#include "../PROCESS_NODE_CONNECTOR.h"
#include "DISCONNECT.h"
namespace PROCESS_NODE_COMMAND {
	DISCONNECT::DISCONNECT(
		PROCESS_NODE_CONNECTOR_OUT* connecterOut,
		PROCESS_NODE_LINER* processNodeLiner) :
		ConnecterOut(connecterOut),
		ProcessNodeLiner(processNodeLiner) {
	}

	DISCONNECT::~DISCONNECT() {
	}
	void DISCONNECT::execute() {
		//�Â��R�l�N�^�[�̌q�����ێ�
		OldConnecterIn = ConnecterOut->cnnectorNext();
		NodeLineData = NODE_LINE_DATA(ConnecterOut->nodeLine());
		//�q�����؂�
		if (ConnecterOut->cnnectorNext() != nullptr) {
			ConnecterOut->cnnectorNext()->setConnectorFront(nullptr);
		}
		ConnecterOut->setConnectorNext(nullptr);
	}
	void DISCONNECT::undo() {
		//�Â��R�l�N�^�[�ƌq������
		ConnecterOut->setConnectorNext(OldConnecterIn);
		NodeLineData.set(ConnecterOut->nodeLine());
		if (OldConnecterIn != nullptr) {
			OldConnecterIn->setConnectorFront(ConnecterOut);
		}
	}
}