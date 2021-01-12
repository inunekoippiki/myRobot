#pragma once
#include "../Library/VECTOR3.h"
#include "EFFEKSEER.h"
#include "ENTITY.h"
#include "ITEM.h"
#include "POSITION.h"
#include "RADIUS.h"
class COLLISION3D_SPHERE;
class COLLISION3D;
class ENTITY_FACTORY;
namespace ENTITY {
	class ITEM :public ENTITY {
	public:
		ITEM(EFFEKSEER::MANAGER* effekseerManager,
			COMPONENT::COLLISION_LIST* collisionList);
		ITEM(ENTITY_FACTORY* entityFactory);
		~ITEM();
		void update()override;
		void activeUpdate()override;
		void onCollision(COLLISION3D* collision);;
		void onCollisionExtrude(const VECTOR3& norm);
		void setPos(const VECTOR3& pos);
		void setR(float r);
		COMPONENT::ITEM* componentItem()override;
		COMPONENT::POSITION* componentPosition()override;
		COMPONENT::RADIUS* componentRadius()override;
		COLLISION3D* collision()const;
		std::string saveDataString()override;
		void stringDataLoad(STRING_TREE* stringTree)override;

	private:
		void create(EFFEKSEER::MANAGER* effekseerManager,
			COMPONENT::COLLISION_LIST* collisionList);
		COMPONENT::POSITION Position;
		COMPONENT::RADIUS Radius;
		COLLISION3D_SPHERE* Collision = nullptr;
		EFFEKSEER::MANAGER* EffekseerManager = nullptr;
		Effekseer::Handle ItemEffect = EFFEKSEER::initialHandle();
		COMPONENT::COLLISION_HANDLE CollisionHandle;
		COMPONENT::ITEM Item;
	};
}