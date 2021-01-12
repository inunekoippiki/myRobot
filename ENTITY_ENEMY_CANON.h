#pragma once
#include "../Library/TREE.h"
#include "DRAWER_BATCH.h"
#include "ENTITY.h"
#include "COLLISION_MANAGER.h"
#include "POSITION.h"
#include "PHYSICS.h"
#include "HIT_POINT.h"
#include "TARGET.h"
#include "ACCESSORY_GAUGE.h"
class VECTOR3;
class CONTAINER;
class COLLISION3D_AABB;
class ENTITY_MANAGER;
class ENTITY_FACTORY;
namespace DRAWER {
	class DRAWERS_SHADER;
	class BATCH2;
	class TREE;
	class IMAGE3D;
	class TREE2;
}
class SOUND;
namespace ENTITY {
	class ENEMY_CANON :public ENTITY {
	public:
		ENEMY_CANON(ENTITY_FACTORY* entityFactoty);

		~ENEMY_CANON();
		void update()override;
		void activeUpdate()override;
		void collisionUpdate();
		void onCollision(COLLISION3D* collision);
		void onCollisionExtrude(const VECTOR3& norm);
		void setPos(const VECTOR3& pos);
		void setScale(const VECTOR3& scale);
		COLLISION3D* collision()const;
		COLLISION3D_AABB* collision() { return Collision; }
		COMPONENT::POSITION* componentPosition() override;
		COMPONENT::HIT_POINT* componentHitPoint() override;
		COMPONENT::TARGET* componentTarget();
		COMPONENT::PHYSICS* physics() { return &Physics; }
		std::string saveDataString()override;
		void stringDataLoad(STRING_TREE* stringTree)override;
	private:
		void create(ENTITY_FACTORY* entityFactory);

		ENTITY_MANAGER* EntityManager = nullptr;
		COMPONENT::POSITION Position;
		COMPONENT::PHYSICS Physics;
		COLLISION3D_AABB* Collision = nullptr;
		TREE Tree;
		DRAWER::TREE* Drawer = nullptr;
		TREE CanonTree;
		DRAWER::TREE2* CanonDrawer;
		DRAWER::BATCH2* LWheel = nullptr;
		DRAWER::BATCH2* RWheel = nullptr;
		ACCESSORY_GAUGE HpGauge;
		COMPONENT::COLLISION_HANDLE CollisionHandle;
		COMPONENT::HIT_POINT HitPoint;
		COMPONENT::TARGET Target;
		int Timer = 0;
		int CanonShotIntervalFrame = 0;
		float BaseRotateSpeed = 0.0f;
		float RotateSpeed = 0.0f;

		SOUND* SoundShot = nullptr;
	};
}
