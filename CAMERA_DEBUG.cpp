#include <math.h>
#include "../Library/GRAPHIC.h"
#include "../Library/INDEV.h"
#include "../Library/CONTAINER.h"
#include "../Library/DATA.h"
#include "../Library/STRING_TREE.h"
#include "../Library/STRING_TREE_SL.h"
#include "INPUT_COMMON.h"
#include "CAMERA_DEBUG.h"
CAMERA_DEBUG::CAMERA_DEBUG(CONTAINER* container) {
	VerticalRad = container->data("CAMERA_DEBUG::VerticalRad");
	HorizontalRad = container->data("CAMERA_DEBUG::HorizontalRad");
	BaseRotateSpeed = container->data("CAMERA_DEBUG::RotateSpeed");
	ZoomSpeed = container->data("CAMERA_DEBUG::ZoomSpeed");
	RotateSpeed = 1.0f;
	GRAPHIC* g = GRAPHIC::instance();
	Proj.setPers(3.141592f / 3.0f, g->aspect(), -0.1f, -120.1f);
	viewUpdate();
}
CAMERA_DEBUG::CAMERA_DEBUG(const STRING_TREE& dataTree){
	create(dataTree);
}

CAMERA_DEBUG::CAMERA_DEBUG() {
	VerticalRad = 0.0f;
	HorizontalRad = 0.0f;
	BaseRotateSpeed = 0.008f;
	RotateSpeed = 1.0f;
	ZoomSpeed = 0.1f;
	GRAPHIC* g = GRAPHIC::instance();
	Proj.setPers(3.141592f / 3.0f, g->aspect(), -0.1f, -120.1f);
}

CAMERA_DEBUG::~CAMERA_DEBUG() {
}

void CAMERA_DEBUG::create(const STRING_TREE& dataTree){
	InitCameraPos = STRING_TREE_LOADER::vector3(dataTree.atw("pos"));
	InitVerticalRad = dataTree.atw("VerticalRad")->toFloat();
	InitHorizontalRad = dataTree.atw("HorizontalRad")->toFloat();

	Pos = InitCameraPos;
	VerticalRad = InitVerticalRad;
	HorizontalRad = InitHorizontalRad;
	BaseRotateSpeed = dataTree.atw("RotateSpeed")->toFloat();
	ZoomSpeed = dataTree.atw("ZoomSpeed")->toFloat();
	RotateSpeed = 1.0f;
	GRAPHIC* g = GRAPHIC::instance();
	Proj.setPers(dataTree.atw("Angle")->toFloat(),
		g->aspect(),
		dataTree.atw("N")->toFloat(),
		dataTree.atw("F")->toFloat());
	viewUpdate();
}

void CAMERA_DEBUG::reset(){
	Pos = InitCameraPos;
	VerticalRad = InitVerticalRad;
	HorizontalRad = InitHorizontalRad;
	viewUpdate();
}

void CAMERA_DEBUG::update() {
	INDEV* in = INDEV::instance();
	if (in->isPress(KEY_SPACE)) {
		mouseScroll();
		keyScroll();
	}
	viewUpdate();
}

void CAMERA_DEBUG::viewUpdate(){
	LookVec.x = sinf(HorizontalRad) * cosf(VerticalRad);
	LookVec.y = sinf(VerticalRad);
	LookVec.z = cosf(HorizontalRad) * cosf(VerticalRad);
	View.set(Pos, Pos + LookVec, VECTOR3(0, 1, 0));
}

void CAMERA_DEBUG::mouseScroll(){
	INDEV* in = INDEV::instance();
	if (in->isPress(MOUSE_LBUTTON)) {
		VECTOR3 horizonralVec = normalize(cross(-LookVec, VECTOR3(0, 1, 0)));
		Pos += horizonralVec * INPUT_COMMON::MouseRelativeValueX(in) * 0.01f;
		Pos += normalize(cross(-LookVec, -horizonralVec)) * INPUT_COMMON::MouseRelativeValueY(in) * 0.01f;
	}
	if (in->isPress(MOUSE_RBUTTON)) {
		HorizontalRad -= INPUT_COMMON::MouseRelativeValueX(in) * BaseRotateSpeed * RotateSpeed;
		VerticalRad -= INPUT_COMMON::MouseRelativeValueY(in) * BaseRotateSpeed * RotateSpeed;
	}
	Pos += (float)in->value(MOUSE_WHEEL) * LookVec;
}

void CAMERA_DEBUG::keyScroll() {
	INDEV* in = INDEV::instance();
	VECTOR3 horizonralVec = normalize(cross(-LookVec, VECTOR3(0, 1, 0)));
	VECTOR3 verticalVec = normalize(cross(-LookVec, -horizonralVec));

	if (in->isPress(KEY_D)) {
		Pos += -horizonralVec ;
	}
	if (in->isPress(KEY_A)) {
		Pos += horizonralVec;
	}
	if (in->isPress(KEY_W)) {
		Pos += LookVec;
	}
	if (in->isPress(KEY_S)) {
		Pos += -LookVec;
	}
	if (in->isPress(KEY_Q)) {
		Pos += verticalVec;
	}
	if (in->isPress(KEY_E)) {
		Pos += -verticalVec;
	}
}

VECTOR3 CAMERA_DEBUG::lookatVec()const {
	return normalize(LookVec - Pos);
}

VECTOR3 CAMERA_DEBUG::cameraPos() const{
	return Pos;
}

float CAMERA_DEBUG::verticalRad()const {
	return VerticalRad;
}

float CAMERA_DEBUG::horizontalRad()const {
	return HorizontalRad;
}

VECTOR3 CAMERA_DEBUG::VecFlont() const {
	return LookVec - Pos;
}

VECTOR3 CAMERA_DEBUG::VecBack() const {
	return Pos - LookVec;
}

VECTOR3 CAMERA_DEBUG::VecRight() const {
	VECTOR3 v = LookVec - Pos;
	return VECTOR3(-v.z, v.y, v.x);
}

VECTOR3 CAMERA_DEBUG::VecLeft() const {
	VECTOR3 v = LookVec - Pos;
	return VECTOR3(v.z, v.y, -v.x);
}

MATRIX CAMERA_DEBUG::rotateMatrix()const {
	MATRIX m;
	m.set(VECTOR3(),  -LookVec, VECTOR3(0, 1, 0));
	return m;
}

MATRIX CAMERA_DEBUG::projView()const {
	return Proj * View;
}

