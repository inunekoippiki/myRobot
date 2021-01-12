#pragma once
#include "../Library/VECTOR3.h"
#include "COLLISION3D.h"
class COLLISION3D_CYLINDER_YAA :public COLLISION3D {
public:
	COLLISION3D_CYLINDER_YAA(ENTITY::ENTITY* entity);
	~COLLISION3D_CYLINDER_YAA();

	bool isHit(const COLLISION3D_AABB* collision)const;
	bool isHit(const COLLISION3D_CYLINDER* collision)const;
	bool isHit(const COLLISION3D_CYLINDER_YAA* collision)const;
	bool isHit(const COLLISION3D_MULTI* collision)const;
	bool isHit(const COLLISION3D_POINT* collision)const;
	bool isHit(const COLLISION3D_SPHERE* collision)const;
	bool isHit(const COLLISION3D_SPHERES* collision)const;
	bool isHit(const COLLISION3D_TERRAIN* collision)const;
	//ディスパッチ
	bool isHit(const COLLISION3D* collision)const;


	VECTOR3 isHitExtrude(const COLLISION3D_AABB* collision)const;
	VECTOR3 isHitExtrude(const COLLISION3D_CYLINDER* collision)const;
	VECTOR3 isHitExtrude(const COLLISION3D_CYLINDER_YAA* collision)const;
	VECTOR3 isHitExtrude(const COLLISION3D_MULTI* collision)const;
	VECTOR3 isHitExtrude(const COLLISION3D_POINT* collision)const;
	VECTOR3 isHitExtrude(const COLLISION3D_SPHERE* collision)const;
	VECTOR3 isHitExtrude(const COLLISION3D_SPHERES* collision)const;
	VECTOR3 isHitExtrude(const COLLISION3D_TERRAIN* collision)const;
	//地形とのコリジョン
	VECTOR3 isHitExtrude(const COLLISION3D* collision)const override;



	void setPos(const VECTOR3& pos) { Pos = pos; }
	void setHeight(float height) { Height = height; }
	void setR(float r) { R = r; }
	//ゲッター
	VECTOR3 pos()const { return Pos; }
	float height()const { return Height; }
	float r()const { return R; }
private:
	VECTOR3 Pos;
	float Height = 0.0f;
	float R = 0.0f;
};

