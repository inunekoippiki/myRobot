#include "../Library/collisionUtil.h"
#include "COLLISION2D_CIRCLE.h"
#include "COLLISION2D_LINE.h"
#include "COLLISION2D_POINT.h"
#include "COLLISION2D_RECT.h"
COLLISION2D_RECT::COLLISION2D_RECT(){
}

COLLISION2D_RECT::~COLLISION2D_RECT(){
}

bool COLLISION2D_RECT::isHit(const COLLISION2D_CIRCLE* circle) const{
	return Calc2DRectAndCircleIsHit(Pos, Wh, circle->pos(), circle->r());
}

bool COLLISION2D_RECT::isHit(const COLLISION2D_LINE* line) const{
	return false;
}

bool COLLISION2D_RECT::isHit(const COLLISION2D_POINT* point) const{
	return Calc2DRectAndPointIsHit(Pos,Wh,point->pos());
}

bool COLLISION2D_RECT::isHit(const COLLISION2D_RECT* rect) const{
	return Calc2DRectAndRectIsHit(Pos,Wh,rect->pos(),rect->wh());
}

bool COLLISION2D_RECT::dispatch(const COLLISION2D* collision) const{
	if (IsCollisionDisable) return false;
	return collision->isHit(this);
}

void COLLISION2D_RECT::minusWhFix(const VECTOR2& pos1, const VECTOR2& pos2) {
	if (pos1.x > pos2.x) {
		Pos.x = pos2.x;
		Wh.x = pos1.x - pos2.x;
	}
	else{
		Pos.x = pos1.x;
		Wh.x = pos2.x - pos1.x;
	}
	if (pos1.y > pos2.y) {
		Pos.y = pos2.y;
		Wh.y = pos1.y - pos2.y;
	}
	else {
		Pos.y = pos1.y;
		Wh.y = pos2.y - pos1.y;
	}
}


