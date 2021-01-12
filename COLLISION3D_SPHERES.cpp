#include "../Library/collisionUtil.h"
#include "COLLISION3D_SPHERES.h"
#include "COLLISION3D_CYLINDER.h"
#include "COLLISION3D_POINT.h"
#include "COLLISION3D_SPHERE.h"
#include "COLLISION3D_TERRAIN.h"

COLLISION3D_SPHERES::COLLISION3D_SPHERES(ENTITY::ENTITY* entity) :COLLISION3D(entity) {
}

COLLISION3D_SPHERES::~COLLISION3D_SPHERES() {
}

bool COLLISION3D_SPHERES::isHit(const COLLISION3D_SPHERE* sphere) const{
	for (auto& i : Spheres) {
		if (Calc2SphereIsHit(sphere->pos(),sphere->r(),i.OffsetPos+pos(),i.R)) {
			return true;
		}
	}
	return false;
}

bool COLLISION3D_SPHERES::isHit(const COLLISION3D_POINT* point) const{
	for (auto& i : Spheres) {
		if (CalcPointSphereIsHit(point->pos(),i.OffsetPos+pos(),i.R)) {
			return true;
		}
	}
	return false;
}

bool COLLISION3D_SPHERES::isHit(const COLLISION3D_CYLINDER* sylinder) const{
	for (auto& i : Spheres) {
		if (CalcSphereSylinderIsHit(i.OffsetPos+pos(),i.R,sylinder->pos(),sylinder->v(),sylinder->r())) {
			return true;
		}
	}
	return false;
}

bool COLLISION3D_SPHERES::isHit(const COLLISION3D_SPHERES* spheres) const{
	for (auto& i : Spheres) {
		for (auto& i2 : spheres->spheres()) {
			if (Calc2SphereIsHit(i.OffsetPos+pos(),i.R,i2.OffsetPos+spheres->pos(),i2.R)) {
				return true;
			}
		}
	}
	return false;
}

bool COLLISION3D_SPHERES::isHit(const COLLISION3D* collision) const{
	return collision->isHit(this);
}

VECTOR3 COLLISION3D_SPHERES::dispatchTerrain(const COLLISION3D_TERRAIN* collision) const{
	if (IsCollisionDisable) return VECTOR3();
	return collision->collision(this);
}

void COLLISION3D_SPHERES::reserve(int num){
	Spheres.reserve(num);
}

void COLLISION3D_SPHERES::add(const VECTOR3& offset, float r){
	Spheres.push_back(SPHERE(offset, r));
}

