#include "../Library/VECTOR3.h"
#include "COLLISION3D_AABB.h"
#include "COLLISION3D_CYLINDER.h"
#include "COLLISION3D_CYLINDER_YAA.h"
#include "COLLISION3D_MULTI.h"
#include "COLLISION3D_POINT.h"
#include "COLLISION3D_SPHERE.h"
#include "COLLISION3D_SPHERES.h"
#include "COLLISION3D_TERRAIN.h"
#include "COLLISION3D.h"
COLLISION3D::COLLISION3D(ENTITY::ENTITY* entity):Entity(entity){

}
COLLISION3D::~COLLISION3D() {

}

bool COLLISION3D::isHit(const COLLISION3D_AABB* collision) const{
	return false;
}

bool COLLISION3D::isHit(const COLLISION3D_CYLINDER* collision) const{
	return false;
}

bool COLLISION3D::isHit(const COLLISION3D_CYLINDER_YAA* collision) const{
	return false;
}

bool COLLISION3D::isHit(const COLLISION3D_MULTI* collision) const{
	return false;
}

bool COLLISION3D::isHit(const COLLISION3D_SPHERE* collision) const {
	return false;
}

bool COLLISION3D::isHit(const COLLISION3D_POINT* collision)const {
	return false;
}

bool COLLISION3D::isHit(const COLLISION3D_SPHERES* collision) const{
	return false;
}

bool COLLISION3D::isHit(const COLLISION3D_TERRAIN* collision) const{
	return false;
}

bool COLLISION3D::isHit(const COLLISION3D* collision) const{
	return false;
}


VECTOR3 COLLISION3D::isHitExtrude(const COLLISION3D_AABB* collision) const{
	return VECTOR3();
}

VECTOR3 COLLISION3D::isHitExtrude(const COLLISION3D_CYLINDER* collision) const {
	return VECTOR3();
}

VECTOR3 COLLISION3D::isHitExtrude(const COLLISION3D_CYLINDER_YAA* collision) const {
	return VECTOR3();
}

VECTOR3 COLLISION3D::isHitExtrude(const COLLISION3D_MULTI* collision) const {
	return VECTOR3();
}

VECTOR3 COLLISION3D::isHitExtrude(const COLLISION3D_POINT* collision) const {
	return VECTOR3();
}

VECTOR3 COLLISION3D::isHitExtrude(const COLLISION3D_SPHERE* collision) const {
	return VECTOR3();
}

VECTOR3 COLLISION3D::isHitExtrude(const COLLISION3D_SPHERES* collision) const {
	return VECTOR3();
}

VECTOR3 COLLISION3D::isHitExtrude(const COLLISION3D_TERRAIN* collision) const {
	return VECTOR3();
}

VECTOR3 COLLISION3D::isHitExtrude(const COLLISION3D* collision) const{
	return VECTOR3();
}

void COLLISION3D::Delete(){
	IsDelete = true;
}
