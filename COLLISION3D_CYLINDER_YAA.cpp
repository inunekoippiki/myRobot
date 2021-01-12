#include "../Library/collisionUtil.h"
#include "COLLISION3D_AABB.h"
#include "COLLISION3D_CYLINDER.h"
#include "COLLISION3D_CYLINDER_YAA.h"
#include "COLLISION3D_MULTI.h"
#include "COLLISION3D_POINT.h"
#include "COLLISION3D_SPHERE.h"
#include "COLLISION3D_SPHERES.h"
#include "COLLISION3D_TERRAIN.h"

COLLISION3D_CYLINDER_YAA::COLLISION3D_CYLINDER_YAA(ENTITY::ENTITY* entity) :COLLISION3D(entity){
}

COLLISION3D_CYLINDER_YAA::~COLLISION3D_CYLINDER_YAA() {
}

bool COLLISION3D_CYLINDER_YAA::isHit(const COLLISION3D_AABB* collision) const{
	return CalcAABBAndAxisYCylinderIsHit(collision->pos(), collision->d(), Pos, Height, R);
}

bool COLLISION3D_CYLINDER_YAA::isHit(const COLLISION3D_CYLINDER* collision) const{
	return false;
}

bool COLLISION3D_CYLINDER_YAA::isHit(const COLLISION3D_CYLINDER_YAA* collision) const{
	return CalcAxisYCylinderAndAxisYCylinderIsHit(Pos, Height, R, collision->pos(), collision->height(), collision->r());
}

bool COLLISION3D_CYLINDER_YAA::isHit(const COLLISION3D_MULTI* collision) const{
	return false;
}

bool COLLISION3D_CYLINDER_YAA::isHit(const COLLISION3D_POINT* collision) const{
	return false;
}

bool COLLISION3D_CYLINDER_YAA::isHit(const COLLISION3D_SPHERE* collision) const{
	if (collision->py() + collision->r() > Pos.y - Height && collision->py() - collision->r() < Pos.y) {
		return Calc2DCircleAndCircleIsHit(Pos.xz(),R,collision->pos().xz(),collision->r());
	}
	return false;
}

bool COLLISION3D_CYLINDER_YAA::isHit(const COLLISION3D_SPHERES* collision) const{
	return false;
}

bool COLLISION3D_CYLINDER_YAA::isHit(const COLLISION3D_TERRAIN* collision) const{
	return false;
}

bool COLLISION3D_CYLINDER_YAA::isHit(const COLLISION3D* collision) const{
	if (IsCollisionDisable) return false;
	return collision->isHit(this);
}

VECTOR3 COLLISION3D_CYLINDER_YAA::isHitExtrude(const COLLISION3D_AABB* collision) const{
	VECTOR3 norm;
	if (CalcStaticAxisYCylinderAndAABBExtrudeXZ(Pos, Height, R, collision->pos(), collision->d(), norm)) {
		return norm;
	}
	return VECTOR3();
}

VECTOR3 COLLISION3D_CYLINDER_YAA::isHitExtrude(const COLLISION3D_CYLINDER* collision) const{
	return VECTOR3();
}

VECTOR3 COLLISION3D_CYLINDER_YAA::isHitExtrude(const COLLISION3D_CYLINDER_YAA* collision) const{
	VECTOR3 norm;
	if (CalcStaticAxisYCylinderAndAxisYCylinderExtrudeXZ(Pos, Height, R, collision->pos(), collision->height(), collision->r(), norm)) { 
		return norm; 
	}
	return VECTOR3();
}

VECTOR3 COLLISION3D_CYLINDER_YAA::isHitExtrude(const COLLISION3D_MULTI* collision) const{
	return VECTOR3();
}

VECTOR3 COLLISION3D_CYLINDER_YAA::isHitExtrude(const COLLISION3D_POINT* collision) const{
	return VECTOR3();
}

VECTOR3 COLLISION3D_CYLINDER_YAA::isHitExtrude(const COLLISION3D_SPHERE* collision) const{
	VECTOR3 norm;
	if (CalcStaticAxisYCylinderAndAxisYCylinderExtrudeXZ(Pos, Height, R, collision->pos()- VECTOR3(0.0f,collision->r(),0.0f), collision->r()*2.0f, collision->r(), norm)) {
		return norm;
	}
	return VECTOR3();
}

VECTOR3 COLLISION3D_CYLINDER_YAA::isHitExtrude(const COLLISION3D_SPHERES* collision) const{
	return VECTOR3();
}

VECTOR3 COLLISION3D_CYLINDER_YAA::isHitExtrude(const COLLISION3D_TERRAIN* collision) const{
	return VECTOR3();
}

VECTOR3 COLLISION3D_CYLINDER_YAA::isHitExtrude(const COLLISION3D* collision) const{
	if (IsCollisionDisable) return VECTOR3();
	return collision->isHitExtrude(this);
}
