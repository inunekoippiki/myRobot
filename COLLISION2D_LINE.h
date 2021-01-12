#pragma once
#include "../Library/VECTOR2.h"
#include "COLLISION2D.h"
class COLLISION2D_LINE:public COLLISION2D{
public:
	COLLISION2D_LINE();
	~COLLISION2D_LINE();
	bool isHit(const COLLISION2D_CIRCLE* circle) const override;
	bool isHit(const COLLISION2D_LINE* line)const override;
	bool isHit(const COLLISION2D_POINT* point)const override;
	bool isHit(const COLLISION2D_RECT* rect)const override;
	//ディスパッチ
	bool dispatch(const COLLISION2D* collision)const override;

	//セッター
	void setPos(const VECTOR2& pos) { Pos = pos; }
	void setVelo(const VECTOR2& velo) { Vec = velo; }
	//ゲッター
	VECTOR2 pos() const{ return Pos; }
	VECTOR2 vec() const{ return Vec; };

private:
	VECTOR2 Pos;
	VECTOR2 Vec;
};

