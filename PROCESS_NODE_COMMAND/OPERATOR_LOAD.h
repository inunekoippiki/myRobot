#pragma once
#include <vector>
#include <string>
#include "INTERFACE.h"
class CONTAINER;
class STATIC_FONT;
class PROCESS_NODE_MANAGER;
class PROCESS_NODE;
namespace PROCESS_NODE_COMMAND {
	//保存していたノードを読み込み追加するコマンド
	class OPERATOR_LOAD :public BASE {
	public:
		OPERATOR_LOAD(
			const std::string& processNodeDataStr,
			const std::vector<PROCESS_NODE*>& addList,
			PROCESS_NODE_MANAGER* processNodeManager
		);
		~OPERATOR_LOAD();
		void execute()override;
		void undo()override;

	private:
		std::string ConnectorData;
		std::vector<PROCESS_NODE*> AddList;
		PROCESS_NODE_MANAGER* ProcessNodeManager = nullptr;
		bool IsUndo = false;
	};
}