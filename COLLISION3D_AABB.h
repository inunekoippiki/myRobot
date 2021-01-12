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
	void setD(const VECTOR3& d) { D = d; }
	//位置(最小)
	VECTOR3 pos()const { return Pos; }
	//サイズ
	VECTOR3 d()const{ return D; }
private:
	//位置(最小)
	VECTOR3 Pos;
	//サイズ
	VECTOR3 D;
};

