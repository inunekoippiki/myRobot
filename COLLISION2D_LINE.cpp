#include "../Library/collisionUtil.h"
#include "COLLISION2D_CIRCLE.h"
#include "COLLISION2D_LINE.h"
#include "COLLISION2D_POINT.h"
#include "COLLISION2D_RECT.h"
COLLISION2D_LINE::COLLISION2D_LINE(){
}

COLLISION2D_LINE::~COLLISION2D_LINE(){
}

bool COLLISION2D_LINE::isHit(const COLLISION2D_CIRCLE* circle) const{
	return Calc2DCircleAndLineIsHit(Pos, Vec, circle->pos(), circle->r());
}

bool COLLISION2D_LINE::isHit(const COLLISION2D_LINE* line) const{
	return Calc2DLineAndLineIsHit(Pos, Vec, line->pos(), line->vec());
}

bool COLLISION2D_LINE::isHit(const COLLISION2D_POINT* point) const{
	return false;
}

bool COLLISION2D_LINE::isHit(const COLLISION2D_RECT* rect) const{
	return false;
}

bool COLLISION2D_LINE::dispatch(const COLLISION2D* collision) const{
	if (IsCollisionDisable) return false;
	return collision->isHit(this);
}
