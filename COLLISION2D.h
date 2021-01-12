#pragma once
class COLLISION2D_CIRCLE;
class COLLISION2D_LINE;
class COLLISION2D_POINT;
class COLLISION2D_RECT;
class VECTOR2;
//�R���W�������B
//�e�h���N���X�Ƃ��f�B�X�p�b�`����
class COLLISION2D{
public:
	COLLISION2D();
	~COLLISION2D();
	virtual bool isHit(const COLLISION2D_CIRCLE* circle)const = 0;
	virtual bool isHit(const COLLISION2D_LINE* line)const = 0;
	virtual bool isHit(const COLLISION2D_POINT* point)const = 0;
	virtual bool isHit(const COLLISION2D_RECT* rect)const = 0;
	//�f�B�X�p�b�`
	virtual bool dispatch(const COLLISION2D* collision)const = 0;

	//�Z�b�^�[
	void Delete() { IsDelete = true; }
	void setIsCollisionDisable(bool isCollisionDisable) { IsCollisionDisable = isCollisionDisable; }
	//�Q�b�^�[
	bool isCollisionDisable()const { return IsCollisionDisable; }
protected:
	bool IsDelete = false;
	bool IsCollisionDisable = false;
};
