#include "../PROCESS_NODE.h"
#include "../PROCESS_NODE_MANAGER.h"
#include "MOVE.h"
namespace PROCESS_NODE_COMMAND {
	MOVE::MOVE(
		PROCESS_NODE* processNode,
		const VECTOR2& pos,
		const VECTOR2& oldPos,
		PROCESS_NODE_MANAGER* processNodeManager) :
		ProcessNode(processNode),
		Pos(pos),
		OldPos(oldPos),
		ProcessNodeManager(processNodeManager)
	{
	}

	MOVE::~MOVE() {
	}
	void MOVE::execute(){
		ProcessNode->rootUi()->setPos(Pos);
		PROCESS_NODE::lineUpdate(ProcessNode);
		ProcessNodeManager->processNodeSelectorUpdate();
	}
	void MOVE::undo(){
		ProcessNode->rootUi()->setPos(OldPos);
		PROCESS_NODE::lineUpdate(ProcessNode);
		ProcessNodeManager->processNodeSelectorUpdate();
	}
}