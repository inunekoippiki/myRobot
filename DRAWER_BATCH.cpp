#include "../Library/BATCH.h"
#include "DRAWER_BATCH.h"
namespace DRAWER {
	void BATCH::setPos(const VECTOR3& pos){
		Pos = pos;
	}
	void BATCH::setRad(const VECTOR3& rad){
		Rad = rad;
	}
	void BATCH::setScale(const VECTOR3& scale){
		Scale = scale;
	}
	void BATCH::draw(SHADER* shader) {
		if (IsDisable) return;
		World.identity();
		World.mulTranslate(Pos);
		World.mulRotateZ(Rad.z);
		World.mulRotateY(Rad.y);
		World.mulRotateX(Rad.x);
		World.mulScale(Scale);
		Batch->draw(shader,World);
	}
}
