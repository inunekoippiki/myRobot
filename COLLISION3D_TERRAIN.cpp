#include <cmath>
#include "../Library/VECTOR3.h"
#include "../Library/CONTAINER.h"
#include "COLLISION3D_AABB.h"
#include "COLLISION3D_CYLINDER.h"
#include "COLLISION3D_CYLINDER_YAA.h"
#include "COLLISION3D_MULTI.h"
#include "COLLISION3D_POINT.h"
#include "COLLISION3D_SPHERE.h"
#include "COLLISION3D_SPHERES.h"
#include "COLLISION3D_TERRAIN.h"

COLLISION3D_TERRAIN::COLLISION3D_TERRAIN(CONTAINER* c, ENTITY::ENTITY* entity) :COLLISION3D(entity) {
	Floor = c->data("COLLISION3D_TERRAIN::Floor");
	Sx = c->data("COLLISION3D_TERRAIN::Sx");
	Sz = c->data("COLLISION3D_TERRAIN::Sz");
	Ex = c->data("COLLISION3D_TERRAIN::Ex");
	Ez = c->data("COLLISION3D_TERRAIN::Ez");
}

COLLISION3D_TERRAIN::~COLLISION3D_TERRAIN() {

}

VECTOR3 COLLISION3D_TERRAIN::collision(const COLLISION3D_SPHERE* collision)const{
	float overY = Floor - (collision->py() - collision->r());
	VECTOR3 v;
	if (overY > 0) {
		v.y = overY;
	}
	return v;
}

VECTOR3 COLLISION3D_TERRAIN::collision(const COLLISION3D_SPHERES* collision) const{
	VECTOR3 v;
	for (auto& i : collision->spheres()) {
		float overY = Floor - (i.OffsetPos.y+ collision->py() - i.R);
		VECTOR3 _v;
		if (overY > 0) {
			if (overY > _v.y) {
				v.y = overY;
			}
		}
	}
	return v;
}

VECTOR3 COLLISION3D_TERRAIN::collision(const COLLISION3D_POINT* collision)const{
	float overY = Floor - collision->py();
	VECTOR3 v;
	if (overY > 0) {
		v.y = overY;
	}
	return v;
}

VECTOR3 COLLISION3D_TERRAIN::isHitExtrude(const COLLISION3D_AABB* collision) const{
	const VECTOR3& pos = collision->pos();
	const VECTOR3& d = collision->d();
	float overSx = Sx - (pos.x);
	float overSz = Sz - (pos.z);
	float overEx = (pos.x + d.x) - Ex;
	float overEz = (pos.z + d.z) - Ez;
	float overY = Floor - pos.y;
	VECTOR3 v;
	if (overSx > 0) {
		v.x = overSx;
	}
	if (overSz > 0) {
		v.z = overSz;
	}
	if (overEx > 0) {
		v.x = -overEx;
	}
	if (overEz > 0) {
		v.z = -overEz;
	}
	if (overY > 0) {
		v.y = overY;
	}
	return v;

	if (Floor > collision->pos().y) {
		return VECTOR3(0.0f, Floor- collision->pos().y,0.0f);
	}
	return VECTOR3();
}

VECTOR3 COLLISION3D_TERRAIN::isHitExtrude(const COLLISION3D_CYLINDER_YAA* collision) const{
	const VECTOR3& collisionPos = collision->pos();
	float overSx = Sx - (collisionPos.x - collision->r());
	float overSz = Sz - (collisionPos.z - collision->r());
	float overEx = collisionPos.x + collision->r() - Ex;
	float overEz = collisionPos.z + collision->r() - Ez;
	float overY = Floor - collisionPos.y;
	VECTOR3 v;
	if (overSx > 0) {
		v.x = overSx;
	}
	if (overSz > 0) {
		v.z = overSz;
	}
	if (overEx > 0) {
		v.x = -overEx;
	}
	if (overEz > 0) {
		v.z = -overEz;
	}
	if (overY > 0) {
		v.y = overY;
	}
	return v;

	if (Floor > collision->pos().y) {
		return VECTOR3(0.0f, Floor - collision->pos().y, 0.0f);
	}
	return VECTOR3();
}

VECTOR3 COLLISION3D_TERRAIN::isHitExtrude(const COLLISION3D_SPHERE* collision) const{
	float overSx = Sx - (collision->px() - collision->r());
	float overSz = Sz - (collision->pz() - collision->r());
	float overEx = collision->px() + collision->r() - Ex;
	float overEz = collision->pz() + collision->r() - Ez;
	float overY = Floor - (collision->py() - collision->r());
	VECTOR3 v;
	if (overSx > 0) {
		v.x = overSx;
	}
	if (overSz > 0) {
		v.z = overSz;
	}
	if (overEx > 0) {
		v.x = -overEx;
	}
	if (overEz > 0) {
		v.z = -overEz;
	}
	if (overY > 0) {
		v.y = overY;
	}
	return v;
}

VECTOR3 COLLISION3D_TERRAIN::isHitExtrude(const COLLISION3D* collision) const{
	if (IsCollisionDisable) return VECTOR3();
	return collision->isHitExtrude(this);
}

VECTOR3 COLLISION3D_TERRAIN::collision(const VECTOR3& pos, const VECTOR3& cv) const{
	float overY = Floor - pos.y;
	VECTOR3 v;
	if (overY > 0) {
		VECTOR3 _v = cv * (overY / cv.y);
		if (length2(v) < length2(_v)) {
			v = _v;
		}
	}
	return v;
}
