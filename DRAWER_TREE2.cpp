#include "../Library/TREE.h"
#include "DRAWER_TREE2.h"
namespace DRAWER {
	void TREE2::update() {
		MATRIX world = World;
		world.mulTranslate(Pos);
		world.mulRotateZ(Rad.z);
		world.mulRotateY(Rad.y);
		world.mulRotateX(Rad.x);
		world.mulScale(Scale);
		Tree->update(world);
	}
	void TREE2::setPos(const VECTOR3& pos) {
		Pos = pos;
	}
	void TREE2::setRad(const VECTOR3& rad) {
		Rad = rad;
	}
	void TREE2::setScale(const VECTOR3& scale) {
		Scale = scale;
	}
	void TREE2::draw(SHADER* shader) {
		if (IsDisable) return;
		Tree->draw(shader);
	}
	void TREE2::setWorld(const MATRIX& world){
		World = world;
	}
}
