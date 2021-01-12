#pragma once
#include <array>
#include "../Library/VECTOR3.h"
#include "OUTPUT_MODULE.h"
#include "OUTPUT_MODULE_SIMPLE.h"
class ROBOT_PROCESSOR;
class ENTITY_MEDIATOR;
namespace ENTITY {
	class ROBOT;
}
class ROBOT_MODULE;
//ロボットの位置から一番近いターゲットのxyz座標の情報を追加
class OUTPUT_MODULE_NEAREST_TARGET_POS :public OUTPUT_MODULE {
public:
	OUTPUT_MODULE_NEAREST_TARGET_POS(
		ROBOT_PROCESSOR& robotProcessor,
		ENTITY::ROBOT* robot,
		ROBOT_MODULE* robotModule,
		ENTITY_MEDIATOR* entityMediator);
	~OUTPUT_MODULE_NEAREST_TARGET_POS();
	void update();
private:
	ENTITY_MEDIATOR* EntityMediator = nullptr;
	ENTITY::ROBOT* Robot = nullptr;
	VECTOR3 Pos;
	std::array< OUTPUT_MODULE_SIMPLE<float>, 3> ModuleList;
};

