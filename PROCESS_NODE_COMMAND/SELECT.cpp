#include "../PROCESS_NODE_SELECTOR.h"
#include "SELECT.h"
namespace PROCESS_NODE_COMMAND {
	SELECT::SELECT(
		const std::vector<PROCESS_NODE*>& selectList,
		const std::vector<PROCESS_NODE*>& oldSelectList,
		PROCESS_NODE_SELECTOR* processNodeSelector) :
		SelectList(selectList),
		OldSelectList(oldSelectList),
		ProcessNodeSelector(processNodeSelector)
	{
	}

	SELECT::~SELECT() {
	}
	void SELECT::execute(){
		ProcessNodeSelector->select(SelectList);
	}
	void SELECT::undo(){
		ProcessNodeSelector->select(OldSelectList);
	}
}