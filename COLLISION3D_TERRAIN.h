#pragma once
#include "COLLISION3D.h"
class VECTOR3;
class COLLISION3D_SPHERE;
class COLLISION3D_SPHERES;
class COLLISION3D_POINT;
class CONTAINER;
class COLLISION3D_TERRAIN:public COLLISION3D{
public:
	COLLISION3D_TERRAIN(CONTAINER* c, ENTITY::ENTITY* entity);
	~COLLISION3D_TERRAIN();
	void setFloor(float floor) { Floor = floor; }

	//�n�`�̌`�󂪕ς��Ƃ���S���ύX------------------
	VECTOR3 collision(const COLLISION3D_SPHERE* collision)const;
	VECTOR3 collision(const COLLISION3D_SPHERES* collision)const;
	VECTOR3 collision(const COLLISION3D_POINT* collision)const;

	VECTOR3 isHitExtrude(const COLLISION3D_AABB* collision)const override;
	VECTOR3 isHitExtrude(const COLLISION3D_CYLINDER_YAA* collision)const override;
	VECTOR3 isHitExtrude(const COLLISION3D_SPHERE* collision)const;
	VECTOR3 isHitExtrude(const COLLISION3D* collision)const override;

	//cv�̓J�����̌����Ă�����̃x�N�g��
	VECTOR3 collision(const VECTOR3& pos,const VECTOR3& cv)const;
private:
	float Floor = 0.0f;
	float Sx = 0.0f;
	float Sz = 0.0f;
	float Ex = 0.0f;
	float Ez = 0.0f;

};

