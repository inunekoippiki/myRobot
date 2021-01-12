#include "../Library/GRAPHIC.h"
#include "../Library/STRING_TREE.h"
#include "../Library/STRING_TREE_SL.h"
#include "CAMERA_FIXED.h"
CAMERA_FIXED::CAMERA_FIXED() {
}

CAMERA_FIXED::~CAMERA_FIXED() {
}

void CAMERA_FIXED::create(const STRING_TREE& dataTree){
	Pos = STRING_TREE_LOADER::vector3(dataTree.atw("pos"));
	GRAPHIC* g = GRAPHIC::instance();
	Proj.setPers(dataTree.atw("Angle")->toFloat(),
		g->aspect(),
		dataTree.atw("N")->toFloat(),
		dataTree.atw("F")->toFloat());
}

void CAMERA_FIXED::update(){

}

void CAMERA_FIXED::setPos(const VECTOR3& pos){
	Pos = pos;
	View.set(Pos, LookAt, VECTOR3(0, 1, 0));
}

void CAMERA_FIXED::setLookAt(const VECTOR3& lookAt){
	LookAt = lookAt;
	View.set(Pos, lookAt, VECTOR3(0, 1, 0));
}
