#pragma once
#include <vector>
#include <string>
#include "INTERFACE.h"
class CONTAINER;
class STATIC_FONT;
class PROCESS_NODE_MANAGER;
class PROCESS_NODE_SELECTOR;
class PROCESS_NODE;
namespace PROCESS_NODE_COMMAND {
	//コピーしていたノードを読み込み追加するコマンド
	class OPERATOR_PASTE :public BASE {
	public:
		OPERATOR_PASTE(
			const std::string& connectorData,
			const std::vector<PROCESS_NODE*>& addList,
			PROCESS_NODE_SELECTOR* processNodeSelector,
			PROCESS_NODE_MANAGER* processNodeManager
		);
		~OPERATOR_PASTE();
		void execute()override;
		void undo()override;

	private:

		std::string ConnectorData;
		std::vector<PROCESS_NODE*> AddList;
		PROCESS_NODE_SELECTOR* ProcessNodeSelector = nullptr;
		PROCESS_NODE_MANAGER* ProcessNodeManager = nullptr;
		std::vector<PROCESS_NODE*> OldSelectList;
		bool IsUndo = false;
	};
}