#include "../../Library/STRING_TREE.h"
#include "../PROCESS_NODE_LOAD.h"
#include "../PROCESS_NODE_MANAGER.h"
#include "../PROCESS_NODE.h"
#include "OPERATOR_LOAD.h"
namespace PROCESS_NODE_COMMAND {
	OPERATOR_LOAD::OPERATOR_LOAD(
		const std::string& connectorData,
		const std::vector<PROCESS_NODE*>& addList,
		PROCESS_NODE_MANAGER* processNodeManager) :
		ConnectorData(connectorData),
		AddList(addList),
		ProcessNodeManager(processNodeManager) {

	}

	OPERATOR_LOAD::~OPERATOR_LOAD() {
		if (IsUndo) {
			for (auto& i : AddList) {
				SAFE_DELETE(i);
			}
		}
	}

	void OPERATOR_LOAD::execute() {
		for (auto& i : AddList) {
			ProcessNodeManager->addProcessNode(i);
		}
		//Šeƒm[ƒh‚ÌŒq‚ª‚è‚ð“Ç‚Ýž‚Þ
		STRING_TREE connectorTree(ConnectorData);
		PROCESS_NODE_LOAD::lineLoad(&connectorTree, AddList, ProcessNodeManager);
		IsUndo = false;
	}
	void OPERATOR_LOAD::undo(){
		for (auto& i : AddList) {
			ProcessNodeManager->removeProcessNode(i);
		}
		IsUndo = true;
	}
}