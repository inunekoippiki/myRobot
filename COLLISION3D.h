#pragma once
class VECTOR3;
class COLLISION3D_AABB;
class COLLISION3D_CYLINDER;
class COLLISION3D_CYLINDER_YAA;
class COLLISION3D_MULTI;
class COLLISION3D_POINT;
class COLLISION3D_SPHERE;
class COLLISION3D_SPHERES;
class COLLISION3D_TERRAIN;
namespace ENTITY{
	class ENTITY;
};
//�R���W�������B
//�r�W�^�[�̖������ʂ����A�e�h���N���X�Ƃ��f�B�X�p�b�`����
class COLLISION3D {
public:
	COLLISION3D(ENTITY::ENTITY* entity);
	virtual ~COLLISION3D();

	virtual bool isHit(const COLLISION3D_AABB* collision)const;
	virtual bool isHit(const COLLISION3D_CYLINDER* collision)const;
	virtual bool isHit(const COLLISION3D_CYLINDER_YAA* collision)const;
	virtual bool isHit(const COLLISION3D_MULTI* collision)const;
	virtual bool isHit(const COLLISION3D_POINT* collision)const;
	virtual bool isHit(const COLLISION3D_SPHERE* collision)const;
	virtual bool isHit(const COLLISION3D_SPHERES* collision)const;
	virtual bool isHit(const COLLISION3D_TERRAIN* collision)const;
	//�f�B�X�p�b�`
	virtual bool isHit(const COLLISION3D* collision)const;

	virtual VECTOR3 isHitExtrude(const COLLISION3D_AABB* collision)const;
	virtual VECTOR3 isHitExtrude(const COLLISION3D_CYLINDER* collision)const;
	virtual VECTOR3 isHitExtrude(const COLLISION3D_CYLINDER_YAA* collision)const;
	virtual VECTOR3 isHitExtrude(const COLLISION3D_MULTI* collision)const;
	virtual VECTOR3 isHitExtrude(const COLLISION3D_POINT* collision)const;
	virtual VECTOR3 isHitExtrude(const COLLISION3D_SPHERE* collision)const;
	virtual VECTOR3 isHitExtrude(const COLLISION3D_SPHERES* collision)const;
	virtual VECTOR3 isHitExtrude(const COLLISION3D_TERRAIN* collision)const;
	//�n�`�Ƃ̃R���W����
	virtual VECTOR3 isHitExtrude(const COLLISION3D* collision)const;

	//���������G���e�B�e�B��������Ƃ��Ă�ǂ�
	void Delete();
	//�Q�b�^�[
	bool isCollision() { return IsCollisionDisable; }
	ENTITY::ENTITY* entity() { return Entity; }
	//�Z�b�^�[
	//void setEntity(ENTITY* entity) { Entity = entity; }
	void setIsCollisionDisable(bool isCollisionDisable) { IsCollisionDisable = isCollisionDisable; }
protected:
	ENTITY::ENTITY* Entity = nullptr;
	bool IsDelete = false;
	bool IsCollisionDisable = false;
};