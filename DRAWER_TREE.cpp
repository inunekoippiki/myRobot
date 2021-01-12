#include "../Library/TREE.h"
#include "DRAWER_TREE.h"
namespace DRAWER {
	void TREE::update(){
		World.identity();
		World.mulTranslate(Pos);
		World.mulRotateZ(Rad.z);
		World.mulRotateY(Rad.y);
		World.mulRotateX(Rad.x);
		World.mulScale(Scale);
		Tree->update(World);
	}
	void TREE::draw(SHADER* shader) {
		if (IsDisable) return;
		Tree->draw(shader);
	}
	void TREE::setPos(const VECTOR3& pos) {
		Pos = pos;
	}
	void TREE::setRad(const VECTOR3& rad) {
		Rad = rad;
	}
	void TREE::setRx(float rx){
		Rad.x = rx;
	}
	void TREE::setRy(float ry){
		Rad.y = ry;
	}
	void TREE::setRz(float rz){
		Rad.z = rz;
	}
	void TREE::setScale(const VECTOR3& scale) {
		Scale = scale;
	}
	float TREE::rx()const{
		return Rad.x;
	}
	float TREE::ry()const {
		return Rad.y;
	}
	float TREE::rz()const {
		return Rad.z;
	}
}
