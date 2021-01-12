#include "../Library/collisionUtil.h"
#include "COLLISION3D_SPHERE.h"
#include "COLLISION3D_POINT.h"
#include "COLLISION3D_CYLINDER.h"
#include "COLLISION3D_SPHERES.h"
#include "COLLISION3D_TERRAIN.h"
COLLISION3D_POINT::COLLISION3D_POINT(ENTITY::ENTITY* entity) :COLLISION3D(entity){
}

COLLISION3D_POINT::~COLLISION3D_POINT() {
}

bool COLLISION3D_POINT::isHit(const COLLISION3D_SPHERE* sphere) const{
	return CalcPointSphereIsHit(pos(),sphere->pos(),sphere->r());
}

bool COLLISION3D_POINT::isHit(const COLLISION3D_POINT* point) const{
	return Calc2PointIsHit(pos(),point->pos());
}

bool COLLISION3D_POINT::isHit(const COLLISION3D_CYLINDER* sylinder) const{
	return CalcPointSylinderIsHit(pos(),sylinder->pos(),sylinder->v(),sylinder->r());
}

bool COLLISION3D_POINT::isHit(const COLLISION3D_SPHERES* spheres) const{
	for (auto& i : spheres->spheres()) {
		if (CalcPointSphereIsHit(pos(), i.OffsetPos+spheres->pos(),i.R)) {
			return true;
		}
	}
	return false;

}

bool COLLISION3D_POINT::isHit(const COLLISION3D* collision) const {
	return collision->isHit(this);
}

VECTOR3 COLLISION3D_POINT::dispatchTerrain(const COLLISION3D_TERRAIN* collision) const{
	return collision->collision(this);
}
