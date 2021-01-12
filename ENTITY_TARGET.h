#pragma once
#include "../Library/VECTOR3.h"
#include "PHYSICS.h"
#include "ENTITY.h"
#include "POSITION.h"
#include "SCALE.h"
#include "HIT_POINT.h"
#include "ACCESSORY_GAUGE.h"
#include "TARGET.h"
class COLLISION3D_AABB;
class COLLISION3D;
class ENTITY_FACTORY;
namespace DRAWER {
	class BATCH;
	class IMAGE3D;
}
namespace ENTITY {
	class TARGET :public ENTITY {
	public:
		TARGET(ENTITY_FACTORY* entityFactory, 
			COMPONENT::COLLISION_LIST* collisionList);
		~TARGET();
		void update()override;
		void activeUpdate()override;
		void onCollision(COLLISION3D* collision);;
		void onCollisionExtrude(const VECTOR3& norm);
		void setPos(const VECTOR3& pos);
		void setScale(const VECTOR3& scale);
		COMPONENT::POSITION* componentPosition()override;
		COMPONENT::SCALE* componentScale()override;
		COMPONENT::HIT_POINT* componentHitPoint()override;
		COMPONENT::TARGET* componentTarget()override;

		COLLISION3D* collision()const;
		std::string saveDataString()override;
		void stringDataLoad(STRING_TREE* stringTree)override;

	private:
		void create(ENTITY_FACTORY* entityFactory, COMPONENT::COLLISION_LIST* collisionList);
		COMPONENT::POSITION Position;
		COMPONENT::SCALE Scale;
		COLLISION3D_AABB* Collision = nullptr;
		DRAWER::BATCH* Drawer = nullptr;
		ACCESSORY_GAUGE HpGauge;
		COMPONENT::PHYSICS Physics;
		COMPONENT::COLLISION_HANDLE CollisionHandle;
		COMPONENT::HIT_POINT HitPoint;
		COMPONENT::TARGET Target;
	};
}