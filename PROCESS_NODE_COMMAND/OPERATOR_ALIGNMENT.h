#pragma once
#include <vector>
#include "../../Library/VECTOR2.h"
#include "INTERFACE.h"
class PROCESS_NODE;
class PROCESS_NODE_SELECTOR;
namespace PROCESS_NODE_COMMAND {
	//選択されたノードの位置揃えをするコマンド
	enum class ALIGNMENT_TYPE {
		X, Y
	};
	class OPERATOR_ALIGNMENT:public BASE {
	public:
		OPERATOR_ALIGNMENT(
			ALIGNMENT_TYPE type,
			PROCESS_NODE_SELECTOR* processNodeSelector);
		~OPERATOR_ALIGNMENT();
		void execute()override;
		void undo()override;

	private:
		ALIGNMENT_TYPE Type;
		std::vector<VECTOR2> SelectListPos;
		PROCESS_NODE_SELECTOR* ProcessNodeSelector = nullptr;
	};
}