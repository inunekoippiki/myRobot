#pragma once
#include "../Library/VECTOR3.h"
#include "COLLISION3D.h"
//球のコリジョン
class COLLISION3D_SPHERE:public COLLISION3D{
public:
	COLLISION3D_SPHERE(ENTITY::ENTITY* entity);
	~COLLISION3D_SPHERE();
	bool isHit(const COLLISION3D_AABB* collision)const;
	bool isHit(const COLLISION3D_CYLINDER* collision)const;
	bool isHit(const COLLISION3D_CYLINDER_YAA* collision)const;
	bool isHit(const COLLISION3D_MULTI* collision)const;
	bool isHit(const COLLISION3D_POINT* collision)const;
	bool isHit(const COLLISION3D_SPHERE* collision)const;
	bool isHit(const COLLISION3D_SPHERES* collision)const;
	bool isHit(const COLLISION3D_TERRAIN* collision)const;

	bool isHit(const COLLISION3D* collision)const override;

	VECTOR3 isHitExtrude(const COLLISION3D_AABB* collision)const;
	VECTOR3 isHitExtrude(const COLLISION3D_CYLINDER* collision)const;
	VECTOR3 isHitExtrude(const COLLISION3D_CYLINDER_YAA* collision)const;
	VECTOR3 isHitExtrude(const COLLISION3D_MULTI* collision)const;
	VECTOR3 isHitExtrude(const COLLISION3D_POINT* collision)const;
	VECTOR3 isHitExtrude(const COLLISION3D_SPHERE* collision)const;
	VECTOR3 isHitExtrude(const COLLISION3D_SPHERES* collision)const;
	VECTOR3 isHitExtrude(const COLLISION3D_TERRAIN* collision)const;
	//地形とのコリジョン
	VECTOR3 isHitExtrude(const COLLISION3D* collision)const;


	virtual VECTOR3 dispatchTerrain(const COLLISION3D_TERRAIN* collision)const;
	void setPos(const VECTOR3& pos) { Pos = pos; }
	void setR(float r) { R = r; }
	//ゲッター
	VECTOR3 pos() const { return Pos+OffestPos; }
	float px()const { return Pos.x+ OffestPos.x; }
	float py()const { return Pos.y + OffestPos.y; }
	float pz()const { return Pos.z + OffestPos.z; }
	float r()const { return R; }
private:
	VECTOR3 Pos;
	VECTOR3 OffestPos;
	float R = 0.0f;
};
