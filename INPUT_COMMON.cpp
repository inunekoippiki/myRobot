#include "../Library/INDEV.h"
#include "../Library/GRAPHIC.h"
#include "../Library/VECTOR2.h"
#include "../Library/VECTOR3.h"
#include "INPUT_COMMON.h"
float INPUT_COMMON::MouseRelativeValueX(INDEV* in){
	GRAPHIC* g = GRAPHIC::instance();
	return (float)in->relativeValue(MOUSE_X) * (g->baseWidth() / g->width());
}

float INPUT_COMMON::MouseRelativeValueY(INDEV* in){
	GRAPHIC* g = GRAPHIC::instance();
	return (float)in->relativeValue(MOUSE_Y) * (g->baseHeight() / g->height());
}

VECTOR2 INPUT_COMMON::MouseRelativeValue(INDEV* in){
	return VECTOR2(MouseRelativeValueX(in), MouseRelativeValueY(in));
}

float INPUT_COMMON::MousePositionX(INDEV* in){
	GRAPHIC* g = GRAPHIC::instance();
	return (float)in->value(MOUSE_X) * (g->baseWidth() / g->width());
}

float INPUT_COMMON::MousePositionY(INDEV* in){
	GRAPHIC* g = GRAPHIC::instance();
	return (float)in->value(MOUSE_Y) * (g->baseHeight() / g->height());
}

VECTOR2 INPUT_COMMON::MousePosition(INDEV* in){
	return VECTOR2(MousePositionX(in), MousePositionY(in));
}

VECTOR3 INPUT_COMMON::Debug3dObjectMove(INDEV* in){
	if (!in->isPress(KEY_SHIFT))return VECTOR3();
	VECTOR3 v;
	if (in->isPress(KEY_A)) {
		v.x += 1.0f;
	}
	if (in->isPress(KEY_D)) {
		v.x += -1.0f;
	}
	if (in->isPress(KEY_W)) {
		v.z += 1.0f;
	}
	if (in->isPress(KEY_S)) {
		v.z += -1.0f;
	}
	if (in->isPress(KEY_Q)) {
		v.y += 1.0f;
	}
	if (in->isPress(KEY_E)) {
		v.y += -1.0f;
	}
	return v;
}
