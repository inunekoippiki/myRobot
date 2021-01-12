#pragma once
#include "OPERATOR_ALIGNMENT.h"
#include "INPUT.h"
class LINE_POINT;
namespace PROCESS_NODE_COMMAND {
	class BASE;
	class FACTORY {
	public:
		FACTORY();
		~FACTORY();

	private:

	};
	BASE* instanceAdd(
		const VECTOR2& pos,
		PROCESS_NODE* processNode,
		PROCESS_NODE_MANAGER* processNodeManager
	);
	BASE* instanceConnect(
		PROCESS_NODE_CONNECTOR_OUT* connecterOut,
		PROCESS_NODE_CONNECTOR_IN* connecterIn,
		PROCESS_NODE_LINER* processNodeLiner
	);
	BASE* instanceDisconnect(
		PROCESS_NODE_CONNECTOR_OUT* connecterOut,
		PROCESS_NODE_LINER* processNodeLiner
	);

	template<class INPUT_OBJ>
	BASE* instanceInput(INPUT_OBJ* inputObj,
		const std::string& newString) {
		return new INPUT(inputObj,newString);
	};
	BASE* instanceLineMove(
		const VECTOR2& pos,
		const VECTOR2& oldPos,
		LINE_POINT* linePoint
	);
	BASE* instanceMove(
		PROCESS_NODE* processNode,
		const VECTOR2& pos,
		const VECTOR2& oldPos,
		PROCESS_NODE_MANAGER* processNodeManager
	);
	BASE* instanceOperatorLoad(
		const std::string& connectorData,
		const std::vector<PROCESS_NODE*>& addList,
		PROCESS_NODE_MANAGER* processNodeManager
	);
	BASE* instanceOperatorAlignment(
		ALIGNMENT_TYPE type,
		PROCESS_NODE_SELECTOR* processNodeSelector
	);
	BASE* instanceOperatorDelete(
		PROCESS_NODE_SELECTOR* processNodeSelector,
		PROCESS_NODE_MANAGER* processNodeManager
	);
	BASE* instanceOperatorMove(
		const VECTOR2& move,
		PROCESS_NODE_SELECTOR* processNodeSelector

	);
	BASE* instanceOperatorPaste(
		const std::string& connectorData,
		const std::vector<PROCESS_NODE*>& addList,
		PROCESS_NODE_SELECTOR* processNodeSelector,
		PROCESS_NODE_MANAGER* processNodeManager
	);
	BASE* instanceSelect(
		const std::vector<PROCESS_NODE*>& selectList,
		const std::vector<PROCESS_NODE*>& oldSelectList,
		PROCESS_NODE_SELECTOR* processNodeSelector
	);

}