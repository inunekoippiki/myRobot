#pragma once
#include "../../Library/VECTOR2.h"
#include "INTERFACE.h"
class PROCESS_NODE;
class PROCESS_NODE_MANAGER;
namespace PROCESS_NODE_COMMAND {
	//ÉmÅ[ÉhÇÃà íuÇïœÇ¶ÇÈ
	class MOVE:public BASE {
	public:
		MOVE(PROCESS_NODE* processNode,
			const VECTOR2& pos,
			const VECTOR2& oldPos,
			PROCESS_NODE_MANAGER* processNodeManager);
		~MOVE();
		void execute()override;
		void undo()override;

	private:
		PROCESS_NODE* ProcessNode = nullptr;
		VECTOR2 Pos;
		VECTOR2 OldPos;
		PROCESS_NODE_MANAGER* ProcessNodeManager = nullptr;
	};
}