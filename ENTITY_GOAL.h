#pragma once
#include "../Library/VECTOR3.h"
#include "EFFEKSEER.h"
#include "ENTITY.h"
#include "POSITION.h"
#include "RADIUS.h"
#include "GOAL.h"
class COLLISION3D_SPHERE;
class COLLISION3D;
class ENTITY_FACTORY;
namespace ENTITY {
	class GOAL:public ENTITY {
	public:
		GOAL(EFFEKSEER::MANAGER* effekseerManager, 
			COMPONENT::COLLISION_LIST* collisionList);
		GOAL(ENTITY_FACTORY* entityFactory);

		~GOAL();
		void update()override;
		void activeUpdate()override;
		void collisionUpdate();
		void onCollision(COLLISION3D* collision);;
		void onCollisionExtrude(const VECTOR3& norm);
		void setPos(const VECTOR3& pos);
		void setR(float r);
		COMPONENT::GOAL* componentGoal()override;
		COMPONENT::POSITION* componentPosition()override;
		COMPONENT::RADIUS* componentRadius()override;
		COLLISION3D* collision()const;
		std::string saveDataString()override;
		void stringDataLoad(STRING_TREE* stringTree)override;
	private:
		void create(EFFEKSEER::MANAGER* effekseerManager,
			COMPONENT::COLLISION_LIST* collisionList);
		bool CollisionOnce = false;
		COMPONENT::POSITION Position;
		COMPONENT::RADIUS Radius;
		COLLISION3D_SPHERE* Collision = nullptr;
		EFFEKSEER::MANAGER* EffekseerManager = nullptr;
		Effekseer::Handle GoalEffect = EFFEKSEER::initialHandle();
		COMPONENT::COLLISION_HANDLE CollisionHandle;
		COMPONENT::GOAL Goal;
	};
}
