#include "ADD.h"
#include "CONNECT.h"
#include "DISCONNECT.h"
#include "INPUT.h"
#include "LINE_MOVE.h"
#include "MOVE.h"
#include "OPERATOR_ALIGNMENT.h"
#include "OPERATOR_DELETE.h"
#include "OPERATOR_LOAD.h"
#include "OPERATOR_MOVE.h"
#include "OPERATOR_PASTE.h"
#include "SELECT.h"
#include "FACTORY.h"
namespace PROCESS_NODE_COMMAND {

	FACTORY::FACTORY() {
	}

	FACTORY::~FACTORY() {
	}
	BASE* instanceAdd(const VECTOR2& pos,PROCESS_NODE* processNode, PROCESS_NODE_MANAGER* processNodeManager) {
		sizeof(ADD);
		return new ADD(pos,processNode, processNodeManager);
	}
	BASE* instanceConnect(PROCESS_NODE_CONNECTOR_OUT* connecterOut, PROCESS_NODE_CONNECTOR_IN* connecterIn, PROCESS_NODE_LINER* processNodeLiner) {
		sizeof(CONNECT);
		return new CONNECT(connecterOut, connecterIn, processNodeLiner);
	}
	BASE* instanceDisconnect(PROCESS_NODE_CONNECTOR_OUT* connecterOut, PROCESS_NODE_LINER* processNodeLiner){
		sizeof(DISCONNECT);
		return new DISCONNECT(connecterOut, processNodeLiner);
	}
	BASE* instanceLineMove(
		const VECTOR2& pos,
		const VECTOR2& oldPos,
		LINE_POINT* linePoint){
		sizeof(LINE_MOVE);
		return new LINE_MOVE(pos, oldPos, linePoint);
	}
	BASE* instanceMove(PROCESS_NODE* processNode, const VECTOR2& pos, const VECTOR2& oldPos,PROCESS_NODE_MANAGER* processNodeManager) {
		sizeof(MOVE);
		return new MOVE(processNode, pos, oldPos, processNodeManager);
	}
	BASE* instanceOperatorLoad(const std::string& connectorData,
		const std::vector<PROCESS_NODE*>& addList,
		PROCESS_NODE_MANAGER* processNodeManager) {
		sizeof(OPERATOR_LOAD);
		return new OPERATOR_LOAD(connectorData, addList,  processNodeManager);
	}
	BASE* instanceOperatorAlignment(ALIGNMENT_TYPE type, PROCESS_NODE_SELECTOR* processNodeSelector) {
		sizeof(OPERATOR_ALIGNMENT);
		return new OPERATOR_ALIGNMENT(type,processNodeSelector);
	}
	BASE* instanceOperatorDelete(
		PROCESS_NODE_SELECTOR* processNodeSelector,
		PROCESS_NODE_MANAGER* processNodeManager) {
		sizeof(OPERATOR_DELETE);
		return new OPERATOR_DELETE(processNodeSelector, processNodeManager);
	}
	BASE* instanceOperatorMove(
		const VECTOR2& move,
		PROCESS_NODE_SELECTOR* processNodeSelector){
		sizeof(OPERATOR_MOVE);
		return new OPERATOR_MOVE(move, processNodeSelector);
	}
	BASE* instanceOperatorPaste(
		const std::string& connectorData,
		const std::vector<PROCESS_NODE*>& addList,
		PROCESS_NODE_SELECTOR* processNodeSelector, 
		PROCESS_NODE_MANAGER* processNodeManager){
		sizeof(OPERATOR_PASTE);
		return new OPERATOR_PASTE(connectorData, addList, processNodeSelector, processNodeManager);
	}
	BASE* instanceSelect(
		const std::vector<PROCESS_NODE*>& selectList,
		const std::vector<PROCESS_NODE*>& oldSelectList,
		PROCESS_NODE_SELECTOR* processNodeSelector) {
		sizeof(SELECT);
		return new SELECT(selectList, oldSelectList, processNodeSelector);
	}
}