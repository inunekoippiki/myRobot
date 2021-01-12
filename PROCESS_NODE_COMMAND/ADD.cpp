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
		//���̃R�}���h���m�[�h���������ςȂ�������������Ă���
		if (HoldProcessNode != nullptr) {
			SAFE_DELETE(HoldProcessNode);
		}
	}
	void ADD::execute() {
		ProcessNodeManager->addProcessNode(ProcessNode);
		ProcessNode->rootUi()->setPos(Pos);
		//add����ƊǗ����}�l�[�W���[�Ɉڂ�
		HoldProcessNode = nullptr;
	}
	void ADD::undo() {
		ProcessNodeManager->removeProcessNode(ProcessNode);
		//remove����ƊǗ����R�}���h�Ɉڂ�
		HoldProcessNode = ProcessNode;
	}
}