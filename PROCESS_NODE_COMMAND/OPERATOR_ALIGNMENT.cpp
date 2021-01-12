#include "../PROCESS_NODE.h"
#include "../PROCESS_NODE_SELECTOR.h"
#include "OPERATOR_ALIGNMENT.h"
namespace PROCESS_NODE_COMMAND {
	OPERATOR_ALIGNMENT::OPERATOR_ALIGNMENT(
		ALIGNMENT_TYPE type,
		PROCESS_NODE_SELECTOR* processNodeSelector):
		Type(type),
		ProcessNodeSelector(processNodeSelector){
		SelectListPos.reserve(processNodeSelector->selectList()->size());
	}

	OPERATOR_ALIGNMENT::~OPERATOR_ALIGNMENT() {
	}

	void OPERATOR_ALIGNMENT::execute(){
		SelectListPos.clear();
		auto& selectList = *ProcessNodeSelector->selectList();
		for (auto& i : selectList) {
			SelectListPos.push_back(i->rootUi()->pos());
		}
		switch (Type){
		case PROCESS_NODE_COMMAND::ALIGNMENT_TYPE::X:
			ProcessNodeSelector->AlignPosXSelectProcessNode();
			break;
		case PROCESS_NODE_COMMAND::ALIGNMENT_TYPE::Y:
			ProcessNodeSelector->AlignPosYSelectProcessNode();
			break;
		}
	}
	void OPERATOR_ALIGNMENT::undo(){
		auto& selectList = *ProcessNodeSelector->selectList();
		for (int i = 0;i < SelectListPos.size();i++) {
			selectList[i]->rootUi()->setPos(SelectListPos[i]);
		}
		ProcessNodeSelector->updateLine();
		ProcessNodeSelector->drawerUpdate();
	}
}