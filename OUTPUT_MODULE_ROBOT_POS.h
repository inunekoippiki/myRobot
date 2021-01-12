#pragma once
#include <array>
#include "../Library/VECTOR3.h"
#include "OUTPUT_MODULE.h"
#include "OUTPUT_MODULE_SIMPLE.h"
class ROBOT_PROCESSOR;
namespace ENTITY {
	class ROBOT;
}
class ROBOT_MODULE;
//ロボットのxyz座標の情報を追加
class OUTPUT_MODULE_ROBOT_POS :public OUTPUT_MODULE {
public:
	OUTPUT_MODULE_ROBOT_POS(
		ROBOT_PROCESSOR& robotProcessor,
		ENTITY::ROBOT* robot,
		ROBOT_MODULE* robotModule);
	~OUTPUT_MODULE_ROBOT_POS();
	void update();
private:
	ENTITY::ROBOT* Robot = nullptr;
	VECTOR3 Pos;
	std::array< OUTPUT_MODULE_SIMPLE<float>, 3> ModuleList;
};

