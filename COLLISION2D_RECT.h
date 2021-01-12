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
	//ディスパッチ
	bool dispatch(const COLLISION2D* collision)const override;

	//セッター
	void setPos(const VECTOR2& pos) { Pos = pos; }
	void setWh(const VECTOR2& wh) { Wh = wh; }
	//2点から設定
	void minusWhFix(const VECTOR2& pos1, const VECTOR2& pos2);
	//ゲッター
	VECTOR2 pos() const{return Pos;}
	VECTOR2 wh() const{ return Wh; }
	VECTOR2 st() const { return Pos; }
	VECTOR2 ed() const { return Pos+Wh; }

private:
	VECTOR2 Pos;
	VECTOR2 Wh;
};

