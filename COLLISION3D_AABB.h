#pragma once
#include "../Library/VECTOR3.h"
#include "COLLISION3D.h"
class COLLISION3D_AABB :public COLLISION3D {
public:
	COLLISION3D_AABB (ENTITY::ENTITY* entity);
	~COLLISION3D_AABB ();

	bool isHit(const COLLISION3D_AABB* collision)const;
	bool isHit(const COLLISION3D_CYLINDER* collision)const;
	bool isHit(const COLLISION3D_CYLINDER_YAA* collision)const;
	bool isHit(const COLLISION3D_MULTI* collision)const;
	bool isHit(const COLLISION3D_POINT* collision)const;
	bool isHit(const COLLISION3D_SPHERE* collision)const;
	bool isHit(const COLLISION3D_SPHERES* collision)const;
	bool isHit(const COLLISION3D_TERRAIN* collision)const;
	//�f�B�X�p�b�`
	bool isHit(const COLLISION3D* collision)const;


	VECTOR3 isHitExtrude(const COLLISION3D_AABB* collision)const;
	VECTOR3 isHitExtrude(const COLLISION3D_CYLINDER* collision)const;
	VECTOR3 isHitExtrude(const COLLISION3D_CYLINDER_YAA* collision)const;
	VECTOR3 isHitExtrude(const COLLISION3D_MULTI* collision)const;
	VECTOR3 isHitExtrude(const COLLISION3D_POINT* collision)const;
	VECTOR3 isHitExtrude(const COLLISION3D_SPHERE* collision)const;
	VECTOR3 isHitExtrude(const COLLISION3D_SPHERES* collision)const;
	VECTOR3 isHitExtrude(const COLLISION3D_TERRAIN* collision)const;
	//�n�`�Ƃ̃R���W����
	VECTOR3 isHitExtrude(const COLLISION3D* collision)const override;


	void setPos(const VECTOR3& pos) { Pos = pos; }
	void setD(const VECTOR3& d) { D = d; }
	//�ʒu(�ŏ�)
	VECTOR3 pos()const { return Pos; }
	//�T�C�Y
	VECTOR3 d()const{ return D; }
private:
	//�ʒu(�ŏ�)
	VECTOR3 Pos;
	//�T�C�Y
	VECTOR3 D;
};

