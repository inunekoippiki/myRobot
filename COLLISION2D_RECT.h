#pragma once
#include "../Library/VECTOR2.h"
#include "COLLISION2D.h"
class COLLISION2D_RECT:public COLLISION2D {
public:
	COLLISION2D_RECT();
	~COLLISION2D_RECT();
	bool isHit(const COLLISION2D_CIRCLE* circle) const override;
	bool isHit(const COLLISION2D_LINE* line)const override;
	bool isHit(const COLLISION2D_POINT* point)const override;
	bool isHit(const COLLISION2D_RECT* rect)const override;
	//�f�B�X�p�b�`
	bool dispatch(const COLLISION2D* collision)const override;

	//�Z�b�^�[
	void setPos(const VECTOR2& pos) { Pos = pos; }
	void setWh(const VECTOR2& wh) { Wh = wh; }
	//2�_����ݒ�
	void minusWhFix(const VECTOR2& pos1, const VECTOR2& pos2);
	//�Q�b�^�[
	VECTOR2 pos() const{return Pos;}
	VECTOR2 wh() const{ return Wh; }
	VECTOR2 st() const { return Pos; }
	VECTOR2 ed() const { return Pos+Wh; }

private:
	VECTOR2 Pos;
	VECTOR2 Wh;
};

