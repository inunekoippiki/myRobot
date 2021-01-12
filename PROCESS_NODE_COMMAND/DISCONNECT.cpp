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
		//古いコネクターの繋がりを保持
		OldConnecterIn = ConnecterOut->cnnectorNext();
		NodeLineData = NODE_LINE_DATA(ConnecterOut->nodeLine());
		//繋がりを切る
		if (ConnecterOut->cnnectorNext() != nullptr) {
			ConnecterOut->cnnectorNext()->setConnectorFront(nullptr);
		}
		ConnecterOut->setConnectorNext(nullptr);
	}
	void DISCONNECT::undo() {
		//古いコネクターと繋ぎ直す
		ConnecterOut->setConnectorNext(OldConnecterIn);
		NodeLineData.set(ConnecterOut->nodeLine());
		if (OldConnecterIn != nullptr) {
			OldConnecterIn->setConnectorFront(ConnecterOut);
		}
	}
}