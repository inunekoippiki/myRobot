#include "../../Library/common.h"
#include "../PROCESS_NODE_MANAGER.h"
#include "../PROCESS_NODE.h"
#include "ADD.h"
namespace PROCESS_NODE_COMMAND {
	ADD::ADD(const VECTOR2& pos,PROCESS_NODE* processNode, PROCESS_NODE_MANAGER* processNodeManager) :
		Pos(pos),
		ProcessNode(processNode),
		ProcessNodeManager(processNodeManager) {
	}
	ADD::~ADD(){
		//このコマンドがノードを持ちっぱなしだったら消しておく
		if (HoldProcessNode != nullptr) {
			SAFE_DELETE(HoldProcessNode);
		}
	}
	void ADD::execute() {
		ProcessNodeManager->addProcessNode(ProcessNode);
		ProcessNode->rootUi()->setPos(Pos);
		//addすると管理がマネージャーに移る
		HoldProcessNode = nullptr;
	}
	void ADD::undo() {
		ProcessNodeManager->removeProcessNode(ProcessNode);
		//removeすると管理がコマンドに移る
		HoldProcessNode = ProcessNode;
	}
}