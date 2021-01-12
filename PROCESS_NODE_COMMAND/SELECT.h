#pragma once
#include "../../Library/VECTOR2.h"
#include "INTERFACE.h"
class PROCESS_NODE_SELECTOR;
namespace PROCESS_NODE_COMMAND {
	//ノードを選択するコマンド
	class SELECT :public BASE {
	public:
		SELECT(
			const std::vector<PROCESS_NODE*>& selectList,
			const std::vector<PROCESS_NODE*>& oldSelectList,
			PROCESS_NODE_SELECTOR* processNodeSelector);
		~SELECT();
		void execute()override;
		void undo()override;
	private:
		std::vector<PROCESS_NODE*> SelectList;
		std::vector<PROCESS_NODE*> OldSelectList;
		PROCESS_NODE_SELECTOR* ProcessNodeSelector = nullptr;
	};
}