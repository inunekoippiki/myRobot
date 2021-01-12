#include "../Library/BATCH.h"
#include "DRAWER_BATCH2.h"
namespace DRAWER {
	void BATCH2::setPos(const VECTOR3& pos) {
		Pos = pos;
	}
	void BATCH2::setRad(const VECTOR3& rad) {
		Rad = rad;
	}
	void BATCH2::setScale(const VECTOR3& scale) {
		Scale = scale;
	}
	void BATCH2::setWorld(const MATRIX& world){
		World = world;
	}
	void BATCH2::draw(SHADER* shader) {
		if (IsDisable) return;
		MATRIX world = World;
		world.mulTranslate(Pos);
		world.mulRotateZ(Rad.z);
		world.mulRotateY(Rad.y);
		world.mulRotateX(Rad.x);
		world.mulScale(Scale);

		Batch->draw(shader, world);
	}
}
