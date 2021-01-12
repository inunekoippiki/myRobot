#pragma once
#include "../Library/VECTOR3.h"
#include "COLLISION3D.h"
//点のコリジョン
class COLLISION3D_POINT:public COLLISION3D{
public:
	COLLISION3D_POINT(ENTITY::ENTITY* entity);
	~COLLISION3D_POINT();
	bool isHit(const COLLISION3D_SPHERE* sphere)const override;
	bool isHit(const COLLISION3D_POINT* point)const override;
	bool isHit(const COLLISION3D_CYLINDER* sylinder)const override;
	bool isHit(const COLLISION3D_SPHERES* spheres)const override;

	bool isHit(const COLLISION3D* collision)const override;
	virtual VECTOR3 dispatchTerrain(const COLLISION3D_TERRAIN* collision)const;
	void setPos(const VECTOR3& pos) { Pos = pos; }
	//ゲッター
	VECTOR3 pos()const { return Pos; }
	float px()const { return Pos.x; }
	float py()const { return Pos.y; }
	float pz()const { return Pos.z; }
private:
	VECTOR3 Pos;
};

