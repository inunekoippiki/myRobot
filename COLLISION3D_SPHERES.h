#pragma once
#include <vector>
#include <functional>
#include "../Library/VECTOR3.h"
#include "COLLISION3D.h"
struct SPHERE{
	SPHERE(const VECTOR3& offset, float r) 
		:OffsetPos(offset), R(r) {
	};
	VECTOR3 OffsetPos;
	float R = 0.0f;
};

//�L�����N�^�[�Ƃ��͊�{�I�ɂ���g��
class COLLISION3D_SPHERES:public COLLISION3D{
public:
	COLLISION3D_SPHERES(ENTITY::ENTITY* entity);
	~COLLISION3D_SPHERES();
	bool isHit(const COLLISION3D_SPHERE* sphere)const override;
	bool isHit(const COLLISION3D_POINT* point)const override;
	bool isHit(const COLLISION3D_CYLINDER* sylinder)const override;
	bool isHit(const COLLISION3D_SPHERES* spheres)const override;

	bool isHit(const COLLISION3D* collision)const override;
	virtual VECTOR3 dispatchTerrain(const COLLISION3D_TERRAIN* collision)const;

	//�ŏ��Ɏg�����m�ۂ����ق����ǂ�
	void reserve(int num);
	//�����蔻��ɋ���ǉ�
	void add(const VECTOR3& offset,float r);
	void setPos(const VECTOR3& pos) { Pos = pos; }
	//�Q�b�^�[
	VECTOR3 pos() const { return Pos; }
	float px()const { return Pos.x; }
	float py()const { return Pos.y; }
	float pz()const { return Pos.z; }
	const std::vector<SPHERE>& spheres()const { return Spheres; }
private:
	VECTOR3 Pos;
	std::vector<SPHERE> Spheres;

};

