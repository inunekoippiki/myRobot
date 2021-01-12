#pragma once
#include "DRAWER_BATCH.h"
#include "ENTITY.h"
#include "COLLISION_MANAGER.h"
#include "POSITION.h"
#include "PHYSICS.h"
#include "RADIUS.h"
#include "HEIGHT.h"

class VECTOR3;
class CONTAINER;
class COLLISION3D_AABB;
class ENTITY_FACTORY;
namespace DRAWER {
	class DRAWERS_SHADER;
}
namespace ENTITY {
	class TERRAIN_CYLINDER :public ENTITY {
	public:
		TERRAIN_CYLINDER(CONTAINER* c, DRAWER::DRAWERS_SHADER* drawers, COMPONENT::COLLISION_LIST* collisionList);
		TERRAIN_CYLINDER(ENTITY_FACTORY* entityFactory);
		~TERRAIN_CYLINDER();
		void update()override;
		void activeUpdate()override;
		void onCollision(COLLISION3D* collision);;
		void onCollisionExtrude(const VECTOR3& norm);
		COMPONENT::POSITION* componentPosition()override;
		COMPONENT::RADIUS* componentRadius()override;
		COMPONENT::HEIGHT* componentHeight()override;
		void setPos(const VECTOR3& pos);
		void setR(float r);
		void setHeight(float height);
		DRAWER::BATCH* drawer() { return Drawer; }
		COLLISION3D_CYLINDER_YAA* collision()const { return Collision; }
		std::string saveDataString()override;
		void stringDataLoad(STRING_TREE* stringTree)override;
	private:
		void create(CONTAINER* c, DRAWER::DRAWERS_SHADER* drawers, COMPONENT::COLLISION_LIST* collisionList);
		COLLISION3D_CYLINDER_YAA* Collision = nullptr;
		COMPONENT::POSITION Position;
		COMPONENT::RADIUS Radius;
		COMPONENT::HEIGHT Height;
		DRAWER::BATCH* Drawer = nullptr;
		COMPONENT::COLLISION_HANDLE CollisionHandle;
	private:

	};
}