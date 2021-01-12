#pragma once
#include "../Library/VECTOR2.h"
#include "COLLISION2D.h"
class COLLISION2D_CIRCLE:public COLLISION2D{
public:
	COLLISION2D_CIRCLE();
	~COLLISION2D_CIRCLE();
	bool isHit(const COLLISION2D_CIRCLE* circle) const override;
	bool isHit(const COLLISION2D_LINE* line)const override;
	bool isHit(const COLLISION2D_POINT* point)const override;
	bool isHit(const COLLISION2D_RECT* rect)const override;
	//ディスパッチ
	bool dispatch(const COLLISION2D* collision)const override;

	//セッター
	void setPos(const VECTOR2& pos) { Pos= pos; }
	void setR(float r) { R = r; }
	//ゲッター
	VECTOR2 pos()const { return Pos; }
	float r()const { return R; }


private:
	VECTOR2 Pos;
	float R = 0.0f;
};

