#pragma once
#include "../../Library/VECTOR2.h"
#include "../LINE_POINT.h"
#include "INTERFACE.h"
namespace PROCESS_NODE_COMMAND {
	class LINE_MOVE:public BASE {
	public:
		LINE_MOVE(
			const VECTOR2& pos,
			const VECTOR2& oldPos,
			LINE_POINT* linePoint);
		~LINE_MOVE ();
		void execute()override;
		void undo()override;

	private:
		VECTOR2 Pos;
		VECTOR2 OldPos;
		LINE_POINT* LinePoint = nullptr;
	};
}
