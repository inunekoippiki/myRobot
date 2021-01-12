#include <math.h>
#include "../Library/GRAPHIC.h"
#include "../Library/SHADER.h"
#include "EFFEKSEER.h"
#include "CAMERA.h"
CAMERA::CAMERA() {
}

void CAMERA::shaderUpdate(SHADER* shader) {
	shader->setProjView(Proj * View);
	shader->setCameraPos(Pos);
}

VECTOR3 CAMERA::pos() const{
	return Pos;
}


VECTOR2 CAMERA::worldToScreenPoint(VECTOR3 point, float& out_z) {
	GRAPHIC* g = GRAPHIC::instance();
	point = Proj * View * point;
	point.x = (((point.x / point.z) + 1.0f) * (g->baseWidth() / 2.0f));
	point.y = (((-point.y / point.z) + 1.0f) * (g->baseHeight() / 2.0f));
	out_z = 1.0f / point.z;
	return point.xy();
}

VECTOR2 CAMERA::worldToScreenPoint(const VECTOR3& point) {
	float z = 0.0f;
	return worldToScreenPoint(point, z);
}

VECTOR3 CAMERA::screenToWorldPoint(const VECTOR2& point, float z) {
	GRAPHIC* g = GRAPHIC::instance();
	MATRIX vp;
	vp.identity();
	vp._11 = g->baseWidth() * 0.5f;
	vp._22 = -g->baseHeight() * 0.5f;
	vp._41 = g->baseWidth() * 0.5f;
	vp._42 = g->baseHeight() * 0.5f;
	VECTOR3 pos = VECTOR3((point.x / (g->baseWidth()) - 0.5f) * 2.0f, -(point.y / (g->baseHeight()) - 0.5f) * 2.0f, z);
	pos = EFFEKSEER::inverseMatrix(Proj) * pos;
	pos = inverseMatrix(View) * pos;
	return pos;
}

CAMERA::~CAMERA() {
}