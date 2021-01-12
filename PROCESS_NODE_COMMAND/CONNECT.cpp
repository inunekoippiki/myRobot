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
		//古いコネクターを保持
		OldConnecterIn = ConnecterOut->cnnectorNext();
		OldConnecterOut	 = ConnecterIn->connectorFront();

		//古いコネクターと繋がりを切って新しいのと繋ぐ
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
		//保持していた古いコネクターと繋ぎ直す
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