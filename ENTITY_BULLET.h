#pragma once
#include "../Library/VECTOR3.h"
#include "PHYSICS.h"
#include "EFFEKSEER.h"
#include "ENTITY.h"
class COLLISION3D_SPHERE;
class COLLISION3D;
class CONTAINER;
class ENTITY_FACTORY;
class SOUND;
namespace DRAWER {
	class BATCH;
	class DRAWERS_SHADER;
}
namespace ENTITY {
	class BULLET :public ENTITY {
	public:
		BULLET(
			ENTITY_FACTORY* entityFactory,
			COMPONENT::COLLISION_LIST* collisionList);
		~BULLET();
		void update()override;
		void activeUpdate()override;
		void onCollision(COLLISION3D* collision);;
		void onCollisionExtrude(const VECTOR3& norm);
		void setPos(const VECTOR3& pos);
		void setVelo(const VECTOR3& velo);
		void setR(float r);
		COMPONENT::PHYSICS* componentPhysics()override;
		COLLISION3D* collision()const;
	private:
		void create(DRAWER::DRAWERS_SHADER* drawer3d, CONTAINER* c, COMPONENT::COLLISION_LIST* collisionList);

		bool CollisionOnce = false;
		int Damage = 0;
		int Timer = 0;
		int LifeTime = 0;
		COMPONENT::PHYSICS Physics;
		VECTOR3 Pos;
		float R = 0.0f;
		COLLISION3D_SPHERE* Collision = nullptr;
		DRAWER::BATCH* Drawer = nullptr;
		COMPONENT::COLLISION_HANDLE CollisionHandle;
		EFFEKSEER::MANAGER* EffekseerManager = nullptr;
		SOUND* SoundBomb = nullptr;
	};
}
