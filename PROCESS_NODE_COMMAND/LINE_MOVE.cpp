#include "LINE_MOVE.h"
namespace PROCESS_NODE_COMMAND {
	LINE_MOVE::LINE_MOVE(
		const VECTOR2& pos,
		const VECTOR2& oldPos,
		LINE_POINT* linePoint) :
		Pos(pos),
		OldPos(oldPos),
		LinePoint(linePoint) {
	}

	LINE_MOVE::~LINE_MOVE() {
	}

	void LINE_MOVE::execute() {
		LinePoint->setPos(Pos);
	}

	void LINE_MOVE::undo() {
		LinePoint->setPos(OldPos);
	}
}