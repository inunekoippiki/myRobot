#include "../../Library/STRING_TREE.h"
#include "../PROCESS_NODE_LOAD.h"
#include "../PROCESS_NODE_MANAGER.h"
#include "../PROCESS_NODE.h"
#include "OPERATOR_PASTE.h"
namespace PROCESS_NODE_COMMAND {
	OPERATOR_PASTE::OPERATOR_PASTE(
		const std::string& connectorData,
		const std::vector<PROCESS_NODE*>& addList,
		PROCESS_NODE_SELECTOR* processNodeSelector,
		PROCESS_NODE_MANAGER* processNodeManager) :
		ConnectorData(connectorData),
		AddList(addList),
		ProcessNodeSelector(processNodeSelector),
		ProcessNodeManager(processNodeManager) {

	}

	OPERATOR_PASTE::~OPERATOR_PASTE() {
		if (IsUndo) {
			for (auto& i : AddList) {
				SAFE_DELETE(i);
			}
		}
	}

	void OPERATOR_PASTE::execute() {
		for (auto& i : AddList) {
			ProcessNodeManager->addProcessNode(i);
		}
		//Šeƒm[ƒh‚ÌŒq‚ª‚è‚ð“Ç‚Ýž‚Þ
		STRING_TREE connectorTree(ConnectorData);
		PROCESS_NODE_LOAD::lineLoad(&connectorTree, AddList, ProcessNodeManager);
		OldSelectList.clear();
		ProcessNodeSelector->select(AddList, OldSelectList);
		IsUndo = false;
	}
	void OPERATOR_PASTE::undo() {
		for (auto& i : AddList) {
			ProcessNodeManager->removeProcessNode(i);
		}
		ProcessNodeSelector->select(OldSelectList);
		IsUndo = true;
	}
}