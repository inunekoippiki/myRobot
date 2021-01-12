#include "../Library/collisionUtil.h"
#include "COLLISION2D_CIRCLE.h"
#include "COLLISION2D_LINE.h"
#include "COLLISION2D_POINT.h"
#include "COLLISION2D_RECT.h"
COLLISION2D_POINT::COLLISION2D_POINT() {
}

COLLISION2D_POINT::~COLLISION2D_POINT() {
}

bool COLLISION2D_POINT::isHit(const COLLISION2D_CIRCLE* circle) const{
	return Calc2DCircleAndPointIsHit(circle->pos(),circle->r(),Pos);
}

bool COLLISION2D_POINT::isHit(const COLLISION2D_LINE* line) const{
	return false;
}

bool COLLISION2D_POINT::isHit(const COLLISION2D_POINT* point) const{
	return false;
}

bool COLLISION2D_POINT::isHit(const COLLISION2D_RECT* rect) const{
	return Calc2DRectAndPointIsHit(rect->pos(), rect->wh(), Pos);
}

bool COLLISION2D_POINT::dispatch(const COLLISION2D* collision) const{
	if (IsCollisionDisable) return false;
	return collision->isHit(this);
}
