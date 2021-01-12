#include "../Library/collisionUtil.h"
#include "COLLISION2D_CIRCLE.h"
#include "COLLISION2D_LINE.h"
#include "COLLISION2D_POINT.h"
#include "COLLISION2D_RECT.h"
COLLISION2D_CIRCLE::COLLISION2D_CIRCLE() {
}

COLLISION2D_CIRCLE::~COLLISION2D_CIRCLE() {
}

bool COLLISION2D_CIRCLE::isHit(const COLLISION2D_CIRCLE* circle) const{
	return Calc2DCircleAndCircleIsHit(Pos,R,circle->pos(),circle->r());
}

bool COLLISION2D_CIRCLE::isHit(const COLLISION2D_LINE* line) const{
	return Calc2DCircleAndLineIsHit(line->pos(), line->vec(), Pos, R);
}

bool COLLISION2D_CIRCLE::isHit(const COLLISION2D_POINT* point) const{
	return Calc2DCircleAndPointIsHit(Pos,R, point->pos());
}

bool COLLISION2D_CIRCLE::isHit(const COLLISION2D_RECT* rect) const{
	return Calc2DRectAndCircleIsHit(rect->pos(),rect->wh(),Pos,R);
}

bool COLLISION2D_CIRCLE::dispatch(const COLLISION2D* collision) const{
	if (IsCollisionDisable) return false;
	return collision->isHit(this);
}
