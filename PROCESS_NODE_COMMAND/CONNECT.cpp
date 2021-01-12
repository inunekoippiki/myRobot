#include "../PROCESS_NODE_CONNECTOR.h"
#include "CONNECT.h"
namespace PROCESS_NODE_COMMAND {
	CONNECT::CONNECT(
		PROCESS_NODE_CONNECTOR_OUT* connecterOut,
		PROCESS_NODE_CONNECTOR_IN* connecterIn,
		PROCESS_NODE_LINER* processNodeLiner) :
		ConnecterOut(connecterOut),
		ConnecterIn(connecterIn),
		ProcessNodeLiner(processNodeLiner) {
	}

	CONNECT::~CONNECT() {
	}
	void CONNECT::execute() {
		//�Â��R�l�N�^�[��ێ�
		OldConnecterIn = ConnecterOut->cnnectorNext();
		OldConnecterOut	 = ConnecterIn->connectorFront();

		//�Â��R�l�N�^�[�ƌq�����؂��ĐV�����̂ƌq��
		if (OldConnecterIn != nullptr) {
			OldConnecterIn->setConnectorFront(nullptr);
		}
		NodeLineData = NODE_LINE_DATA(ConnecterOut->nodeLine());
		ConnecterOut->setConnectorNext(ConnecterIn);
		if (OldConnecterOut != nullptr) {
			OldNodeLineData = NODE_LINE_DATA(OldConnecterOut->nodeLine());
			OldConnecterOut->setConnectorNext(nullptr);
		}
		ConnecterIn->setConnectorFront(ConnecterOut);
	}
	void CONNECT::undo(){
		//�ێ����Ă����Â��R�l�N�^�[�ƌq������
		ConnecterOut->setConnectorNext(OldConnecterIn);
		NodeLineData.set(ConnecterOut->nodeLine());
		if (OldConnecterIn != nullptr) {
			OldConnecterIn->setConnectorFront(ConnecterOut);
		}
		ConnecterIn->setConnectorFront(OldConnecterOut);
		if (OldConnecterOut != nullptr) {
			OldConnecterOut->setConnectorNext(ConnecterIn);
			OldNodeLineData.set(OldConnecterOut->nodeLine());
		}
	}
}