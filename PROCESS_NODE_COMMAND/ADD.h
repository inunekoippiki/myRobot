#pragma once
#include "../../Library/VECTOR2.h"
#include "INTERFACE.h"
class PROCESS_NODE;
class PROCESS_NODE_MANAGER;
namespace PROCESS_NODE_COMMAND {
	//新しいノードを追加するコマンド
	class ADD :public BASE {
	public:
		ADD(const VECTOR2& pos,PROCESS_NODE* processNode,PROCESS_NODE_MANAGER* processNodeManager);
		~ADD();
		void execute()override;
		void undo()override;
	private:
		VECTOR2 Pos;
		PROCESS_NODE* ProcessNode = nullptr;
		PROCESS_NODE* HoldProcessNode = nullptr;
		PROCESS_NODE_MANAGER* ProcessNodeManager = nullptr;
	};
}