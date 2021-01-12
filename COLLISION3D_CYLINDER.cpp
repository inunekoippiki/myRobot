#include "../Library/collisionUtil.h"
#include "COLLISION3D_AABB.h"
#include "COLLISION3D_CYLINDER.h"
#include "COLLISION3D_CYLINDER_YAA.h"
#include "COLLISION3D_MULTI.h"
#include "COLLISION3D_POINT.h"
#include "COLLISION3D_SPHERE.h"
#include "COLLISION3D_SPHERES.h"
#include "COLLISION3D_TERRAIN.h"
COLLISION3D_CYLINDER::COLLISION3D_CYLINDER(ENTITY::ENTITY* entity):COLLISION3D(entity){

}

COLLISION3D_CYLINDER::~COLLISION3D_CYLINDER() {
}

bool COLLISION3D_CYLINDER::isHit(const COLLISION3D_SPHERE* sphere) const{
	return CalcSphereSylinderIsHit(sphere->pos(),sphere->r(), pos(),V,R);
}

bool COLLISION3D_CYLINDER::isHit(const COLLISION3D_POINT* point) const{
	return CalcPointSylinderIsHit(point->pos(), pos(), V, R);
}
//‰~’Œ“¯Žm–¢ŽÀ‘•B“–‚½‚ç‚È‚¢
bool COLLISION3D_CYLINDER::isHit(const COLLISION3D_CYLINDER* sylinder) const{
	return false;
}

bool COLLISION3D_CYLINDER::isHit(const COLLISION3D_SPHERES* spheres) const{
	for (auto& i : spheres->spheres()) {
		if (CalcSphereSylinderIsHit(i.OffsetPos + spheres->pos(), i.R, pos(), V, R)) {
			return true;
		}
	}
	return false;
}

bool COLLISION3D_CYLINDER::isHit(const COLLISION3D* collision) const{
	if (IsCollisionDisable) return false;
	return collision->isHit(this);
}
