#pragma once
#include <array>
#include "../Library/VECTOR3.h"
#include "OUTPUT_MODULE.h"
#include "OUTPUT_MODULE_SIMPLE.h"
class ENTITY_MEDIATOR;
class ROBOT_PROCESSOR;
namespace ENTITY {
	class ROBOT;
}
class ROBOT_MODULE;
//ロボットの位置から一番近いゴールのxyz座標の情報を追加
class OUTPUT_MODULE_NEAREST_GOAL_POS :public OUTPUT_MODULE {
public:
	OUTPUT_MODULE_NEAREST_GOAL_POS(
		ROBOT_PROCESSOR& robotProcessor,
		ENTITY::ROBOT* robot,
		ROBOT_MODULE* robotModule,
		ENTITY_MEDIATOR* entityMediator);
	~OUTPUT_MODULE_NEAREST_GOAL_POS();
	void update();
private:
	ENTITY_MEDIATOR* EntityMediator = nullptr;
	ENTITY::ROBOT* Robot = nullptr;
	VECTOR3 Pos;
	std::array< OUTPUT_MODULE_SIMPLE<float>, 3> ModuleList;
};

