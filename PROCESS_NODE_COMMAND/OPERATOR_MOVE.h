#pragma once
#include "../../Library/VECTOR2.h"
#include "INTERFACE.h"
class PROCESS_NODE_SELECTOR;
namespace PROCESS_NODE_COMMAND {
	//選択されたノードの位置を変える
	class OPERATOR_MOVE:public BASE {
	public:
		OPERATOR_MOVE(
			const VECTOR2& move,
			PROCESS_NODE_SELECTOR* processNodeSelector);
		~OPERATOR_MOVE();
		void execute()override;
		void undo()override;

	private:
		VECTOR2 Move;
		PROCESS_NODE_SELECTOR* ProcessNodeSelector = nullptr;
	};

}