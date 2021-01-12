#pragma once
#include "../Library/VECTOR2.h"
#include "COLLISION2D.h"
class COLLISION2D_POINT:public COLLISION2D{
public:
	COLLISION2D_POINT();
	~COLLISION2D_POINT();
	bool isHit(const COLLISION2D_CIRCLE* circle) const override;
	bool isHit(const COLLISION2D_LINE* line)const override;
	bool isHit(const COLLISION2D_POINT* point)const override;
	bool isHit(const COLLISION2D_RECT* rect)const override;
	//�f�B�X�p�b�`
	bool dispatch(const COLLISION2D* collision)const override;

	//�Z�b�^�[
	void setPos(const VECTOR2& pos) { Pos = pos; }
	//�Q�b�^�[
	VECTOR2 pos()const { return Pos; }
private:
	VECTOR2 Pos;
};

