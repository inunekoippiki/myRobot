#pragma once

#include "ENTITY.h"
#include "POSITION.h"
#include "SCALE.h"
#include "DRAWER_BATCH.h"
#include "COLLISION_MANAGER.h"
class VECTOR3;
class CONTAINER;
class COLLISION3D_AABB;
class ENTITY_FACTORY;
namespace DRAWER {
	class DRAWERS_SHADER;
}
namespace ENTITY {
	class TERRAIN_AABB:public ENTITY{
	public:
		TERRAIN_AABB(CONTAINER* c, DRAWER::DRAWERS_SHADER* drawers, COMPONENT::COLLISION_LIST* collisionList);
		TERRAIN_AABB(ENTITY_FACTORY* entityFactory);
		~TERRAIN_AABB();
		void update()override;
		void activeUpdate()override;
		void collisionUpdate();
		void onCollisionExtrude(const VECTOR3& norm);
		COMPONENT::POSITION* componentPosition()override;
		COMPONENT::SCALE* componentScale()override;
		void setPos(const VECTOR3& pos);
		void setScale(const VECTOR3& scale);
		DRAWER::BATCH* drawer() { return Drawer; }
		COLLISION3D* collision()const ;
		COLLISION3D_AABB* collision() { return Collision; }
		std::string saveDataString()override;
		void stringDataLoad(STRING_TREE* stringTree)override;
	private:
		void create(CONTAINER* c, DRAWER::DRAWERS_SHADER* drawers, COMPONENT::COLLISION_LIST* collisionList);
		COMPONENT::POSITION Position;
		COMPONENT::SCALE Scale;
		COLLISION3D_AABB* Collision = nullptr;
		DRAWER::BATCH* Drawer = nullptr;
		COMPONENT::COLLISION_HANDLE CollisionHandle;
	private:

	};
}
