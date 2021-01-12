#include "../Library/collisionUtil.h"
#include "../Library/CONTAINER.h"
#include "../Library/TEXTURE.h"
#include "COLLISION3D_AABB.h"
#include "COLLISION3D_CYLINDER.h"
#include "COLLISION3D_CYLINDER_YAA.h"
#include "COLLISION3D_MULTI.h"
#include "COLLISION3D_POINT.h"
#include "COLLISION3D_SPHERE.h"
#include "COLLISION3D_SPHERES.h"
#include "COLLISION3D_TERRAIN.h"
COLLISION3D_SPHERE::COLLISION3D_SPHERE(ENTITY::ENTITY* entity):COLLISION3D(entity){
}


COLLISION3D_SPHERE::~COLLISION3D_SPHERE() {
}

bool COLLISION3D_SPHERE::isHit(const COLLISION3D_AABB* collision) const{
	VECTOR3 d = VECTOR3(R, R, R);
	return CalcAABBAndAABBIsHit(collision->pos(), collision->d(), Pos - d, d * 2.0f);
}

bool COLLISION3D_SPHERE::isHit(const COLLISION3D_SPHERE* sphere)const{
	return Calc2SphereIsHit(pos(),R,sphere->pos(),sphere->r());
}

bool COLLISION3D_SPHERE::isHit(const COLLISION3D_POINT* point) const{
	return CalcPointSphereIsHit(point->pos(),pos(),R);
}

bool COLLISION3D_SPHERE::isHit(const COLLISION3D_CYLINDER* sylinder) const{
	return CalcSphereSylinderIsHit(pos(),R,sylinder->pos(),sylinder->v(),sylinder->r());
}

bool COLLISION3D_SPHERE::isHit(const COLLISION3D_CYLINDER_YAA* collision) const{
	if (Pos.y + collision->r() > Pos.y - collision->height() && Pos.y - collision->r() < collision->pos().y) {
		return Calc2DCircleAndCircleIsHit(collision->pos().xz(), collision->r(), Pos.xz(), R);
	}
	return false;
}

bool COLLISION3D_SPHERE::isHit(const COLLISION3D_MULTI* collision) const{
	return false;
}

bool COLLISION3D_SPHERE::isHit(const COLLISION3D_SPHERES* spheres) const{
	for(auto &i:spheres->spheres()){
		if (Calc2SphereIsHit(i.OffsetPos + spheres->pos(), i.R, pos(), R)) {
			return true;
		}
	}
	return false;
}

bool COLLISION3D_SPHERE::isHit(const COLLISION3D_TERRAIN* collision) const{
	return false;
}

bool COLLISION3D_SPHERE::isHit(const COLLISION3D* collision) const{
	return collision->isHit(this);
}

VECTOR3 COLLISION3D_SPHERE::isHitExtrude(const COLLISION3D_AABB* collision) const{
	return VECTOR3();
}

VECTOR3 COLLISION3D_SPHERE::isHitExtrude(const COLLISION3D_CYLINDER* collision) const{
	return VECTOR3();
}

VECTOR3 COLLISION3D_SPHERE::isHitExtrude(const COLLISION3D_CYLINDER_YAA* collision) const{
	return VECTOR3();
}

VECTOR3 COLLISION3D_SPHERE::isHitExtrude(const COLLISION3D_MULTI* collision) const{
	return VECTOR3();
}

VECTOR3 COLLISION3D_SPHERE::isHitExtrude(const COLLISION3D_POINT* collision) const{
	return VECTOR3();
}

VECTOR3 COLLISION3D_SPHERE::isHitExtrude(const COLLISION3D_SPHERE* collision) const{
	return VECTOR3();
}

VECTOR3 COLLISION3D_SPHERE::isHitExtrude(const COLLISION3D_SPHERES* collision) const{
	return VECTOR3();
}

VECTOR3 COLLISION3D_SPHERE::isHitExtrude(const COLLISION3D_TERRAIN* collision) const{
	return VECTOR3();
}

VECTOR3 COLLISION3D_SPHERE::isHitExtrude(const COLLISION3D* collision) const{
	if (IsCollisionDisable) return VECTOR3();
	return collision->isHitExtrude(this);
}

VECTOR3 COLLISION3D_SPHERE::dispatchTerrain(const COLLISION3D_TERRAIN* collision) const{
	return collision->collision(this);
}
