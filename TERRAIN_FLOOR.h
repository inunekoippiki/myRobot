#pragma once
#include "DRAWER_BATCH.h"
#include "ENTITY.h"
#include "COLLISION_MANAGER.h"
class VECTOR3;
class CONTAINER;
class COLLISION3D_TERRAIN;
namespace DRAWER {
	class DRAWERS_SHADER;
}
namespace ENTITY {
	class TERRAIN_FLOOR :public ENTITY {
	public:
		TERRAIN_FLOOR(CONTAINER* c, DRAWER::DRAWERS_SHADER* drawers, COMPONENT::COLLISION_LIST* collisionList);
		~TERRAIN_FLOOR();
		void update()override;
		void activeUpdate()override;
		void onCollision(COLLISION3D* collision) {};
		void onCollisionExtrude(const VECTOR3& norm);
		void setPos(const VECTOR3& pos);
		void setScale(const VECTOR3& scale);
		DRAWER::BATCH* drawer() { return Drawer; }
		COLLISION3D* collision()const ;
	private:
		void create(CONTAINER* c, DRAWER::DRAWERS_SHADER* drawers, COMPONENT::COLLISION_LIST* collisionList);
		COLLISION3D_TERRAIN* Collision = nullptr;
		DRAWER::BATCH* Drawer = nullptr;
		COMPONENT::COLLISION_HANDLE CollisionHandle;
	};
}