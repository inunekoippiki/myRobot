#include "../PROCESS_NODE_SELECTOR.h"
#include "OPERATOR_MOVE.h"
namespace PROCESS_NODE_COMMAND {

	OPERATOR_MOVE::OPERATOR_MOVE(
		const VECTOR2& move,
		PROCESS_NODE_SELECTOR* processNodeSelector) :
		Move(move),
		ProcessNodeSelector(processNodeSelector) {
	}

	OPERATOR_MOVE::~OPERATOR_MOVE() {
	}
	void OPERATOR_MOVE::execute(){
		ProcessNodeSelector->moveSelectProcessNode(Move);
	}
	void OPERATOR_MOVE::undo(){
		ProcessNodeSelector->moveSelectProcessNode(-Move);
	}
}