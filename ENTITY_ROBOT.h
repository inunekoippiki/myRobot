#pragma once
#include <array>
#include "../Library/TREE.h"
#include "ENTITY.h"
#include "COLLISION_MANAGER.h"
#include "PHYSICS.h"
#include "HIT_POINT.h"
#include "POSITION.h"
#include "ROBOT_PROCESSOR.h"
#include "MODEL_ROBOT.h"
#include "ROBOT_MODULE.h"
#include "INPUT_MODULE_SIMPLE.h"
#include "OUTPUT_MODULE_SIMPLE.h"
#include "OUTPUT_MODULE_NEAREST_GOAL_POS.h"
#include "OUTPUT_MODULE_NEAREST_TARGET_POS.h"
#include "OUTPUT_MODULE_NEAREST_ITEM_POS.h"
#include "OUTPUT_MODULE_ROBOT_POS.h"
#include "ACCESSORY_GAUGE.h"

namespace DRAWER {
	class TREE;
	class IMAGE3D;
	class BATCH2;
	class TREE2;
	class DRAWERS_SHADER;
}
class VECTOR3;
class CONTAINER;
class COLLISION3D_AABB;
class ROBOT_PROCESSOR;
class ENTITY_MANAGER;
class ENTITY_FACTORY;
class ROUND_MISSION;
namespace ENTITY {
	class ROBOT :public ENTITY {
	public:
		ROBOT(ENTITY_FACTORY* entityFactory,
			ROBOT_PROCESSOR* robotProcessor);
		~ROBOT();
		void reset();
		void update()override;
		void activeUpdate()override;
		void collisionUpdate();
		void onCollision(COLLISION3D* collision);
		void onCollisionExtrude(const VECTOR3& norm);
		void setPos(const VECTOR3& pos);
		VECTOR3 pos() { return Position.pos(); }
		COLLISION3D* collision()const;
		COLLISION3D_AABB* collision() { return Collision; }
		COMPONENT::PHYSICS* physics() { return &Physics; }
		COMPONENT::PHYSICS* componentPhysics()override { return &Physics; }
		COMPONENT::HIT_POINT* componentHitPoint() override;
		COMPONENT::POSITION* componentPosition() override;
	private:
		void create(ENTITY_FACTORY* entityFactory);
		void create(CONTAINER* c, 
			DRAWER::DRAWERS_SHADER* drawers,
			DRAWER::DRAWERS_SHADER* drawers2d,
			COMPONENT::COLLISION_LIST* collisionList);
		void aliveUpdate();

		ENTITY_MANAGER* EntityManager = nullptr;
		ROUND_MISSION* RoundMission;
		VECTOR3 Rad;
		COMPONENT::PHYSICS Physics;
		COLLISION3D_AABB* Collision = nullptr;
		MODEL_ROBOT Model;
		ACCESSORY_GAUGE HpGauge;
		COMPONENT::POSITION Position;
		COMPONENT::COLLISION_HANDLE CollisionHandle;
		COMPONENT::HIT_POINT HitPoint;
		ROBOT_PROCESSOR* RobotProcessor;
		ROBOT_MODULE RobotModule;
		float WheelPower = 0.1f;
		int CanonShotInterval = 60;
		std::array< INPUT_MODULE_SIMPLE<float>, 5> InputModuleList;
		float CanonVerticalRad = 0.0f;
		float CanonHorizontalRad = 0.0f;
		float CanonShot = 0.0f;
		float RightWheelPower = 0.0f;
		float LeftWheelPower = 0.0f;
		OUTPUT_MODULE_NEAREST_ITEM_POS OutputModuleNearestItemPos;
		OUTPUT_MODULE_ROBOT_POS OutputModuleRobotPos;
		OUTPUT_MODULE_NEAREST_GOAL_POS OutputModuleNearestGoalPos;
		OUTPUT_MODULE_NEAREST_TARGET_POS OutputModuleNearestTargetPos;
		float CanonShotTimer = 0;
		std::vector<DRAWER::IMAGE3D*> DebugDrawerPosition ;
	};
}
