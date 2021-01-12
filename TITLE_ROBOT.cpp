#include <cmath>
#include "../Library/INDEV.h"
#include "../Library/collisionUtil.h"
#include "INPUT_COMMON.h"
#include "CAMERA.h"
#include "DRAWER.h"
#include "TITLE_ROBOT.h"
TITLE_ROBOT::TITLE_ROBOT() {
}

TITLE_ROBOT::~TITLE_ROBOT() {
}

void TITLE_ROBOT::create(CONTAINER* c,DRAWER::DRAWERS_SHADER* drawers3d,CAMERA* camera){
	Camera = camera;
	Robot.create(c, drawers3d);
	Pos = VECTOR3(0.0f, Robot.scale().y * 0.5f, 0.0f);
	Ry = 0.0f;
	MoveSpeed = 0.1f;
	RotateSpeed = 0.1f;
}

void TITLE_ROBOT::update(){
	INDEV* in = INDEV::instance();
	VECTOR2 frontVec{ std::sin(Ry) ,std::cos(Ry) };
	VECTOR3 targetPos = CalcFloorAndLineHitPoint(0.0f,
		Camera->pos(),
		Camera->screenToWorldPoint(INPUT_COMMON::MousePosition(in), 1.0f) - Camera->pos());
	VECTOR2 targetVec = normalize(targetPos.xz() - Pos.xz());
	float r = rotate(frontVec, targetVec);
	Pos += VECTOR3(frontVec.x, 0.0f, frontVec.y) * MoveSpeed;
	Robot.setPos(Pos);
	if (std::abs(r) > RotateSpeed) {
		Ry += RotateSpeed * (r / std::abs(r));
	}
	float lwr = 0.0f;
	float rwr = 0.0f;
	(r < 0 ? lwr : rwr) = std::abs(r);
	Robot.lWheelRotate(MoveSpeed + RotateSpeed * lwr);
	Robot.rWheelRotate(MoveSpeed + RotateSpeed * rwr);
	Robot.update(Pos, Ry, VECTOR3());
}
