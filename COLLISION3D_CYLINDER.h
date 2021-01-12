#pragma once
#include "../Library/VECTOR3.h"
#include "COLLISION3D.h"
//無限円柱
class COLLISION3D_CYLINDER:public COLLISION3D{
public:
	COLLISION3D_CYLINDER(ENTITY::ENTITY* entity);
	~COLLISION3D_CYLINDER();
	bool isHit(const COLLISION3D_SPHERE* sphere)const override;
	bool isHit(const COLLISION3D_POINT* point)const override;
	bool isHit(const COLLISION3D_CYLINDER* sylinder)const override;
	bool isHit(const COLLISION3D_SPHERES* spheres)const override;

	bool isHit(const COLLISION3D* collision)const override;
	void setPos(const VECTOR3& pos) { Pos = pos; }
	void setRadius(float r) { R = r; }
	void setVelo(const VECTOR3& velo) { V = velo; }
	//ゲッター
	VECTOR3 pos()const { return Pos; }
	float px()const { return Pos.x; }
	float py()const { return Pos.y; }
	float pz()const { return Pos.z; }
	VECTOR3 v()const { return V; }
	float r()const { return R; }
private:
	VECTOR3 Pos;
	VECTOR3 V;//レーザーの向き
	float R = 0.0f;
};

