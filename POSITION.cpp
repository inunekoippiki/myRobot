#include "POSITION.h"
namespace COMPONENT {
	POSITION::POSITION() {
	}

	//POSITION::POSITION(const VECTOR3& pos):
	//	Pos(pos){
	//}

	POSITION::~POSITION() {
	}

	void POSITION::setPos(const VECTOR3& pos) {
		Pos = pos;
	}
}