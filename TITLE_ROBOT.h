#pragma once
#include "MODEL_ROBOT.h"
namespace DRAWER {
	class DRAWERS_SHADER;
}
class CAMERA;
class TITLE_ROBOT{
public:
	TITLE_ROBOT();
	~TITLE_ROBOT();
	void create(CONTAINER* c, DRAWER::DRAWERS_SHADER* drawers3d, CAMERA* camera);
	void update();
private:
	MODEL_ROBOT Robot;
	VECTOR3 Pos;
	float Ry = 0.0f;
	float MoveSpeed = 0.0f;
	float RotateSpeed = 0.0f;

	CAMERA* Camera = nullptr;
};
