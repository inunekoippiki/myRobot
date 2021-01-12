#pragma once
#include <optional>
#include <string>
#include "MESSENGER.h"
class STRING_TREE;
namespace COMPONENT {
	class DAMAGE;
	class HIT_POINT;
	class ITEM;
	class GOAL;
	class POSITION;
	class ENEMY;
	class TARGET;
	class SCALE;
	class RADIUS;
	class HEIGHT;
	class ACTIVE_BEHAVIOR;
	class PHYSICS;
	class UPDATER;
	class COLLISION_CALLBACK;
};
/*
	
*/
namespace ENTITY {
	class ENTITY {
	public:
		ENTITY();
		virtual ~ENTITY();
		//基本のアップデート
		virtual void update() = 0;
		//再生中のアップデート
		virtual void activeUpdate() = 0;

		virtual COMPONENT::HIT_POINT* componentHitPoint() { return nullptr; }
		virtual COMPONENT::ITEM* componentItem() { return nullptr; }
		virtual COMPONENT::GOAL* componentGoal() { return nullptr; }
		virtual COMPONENT::POSITION* componentPosition() { return nullptr; }
		virtual COMPONENT::TARGET* componentTarget() { return nullptr; }
		virtual COMPONENT::SCALE* componentScale() { return nullptr; }
		virtual COMPONENT::RADIUS* componentRadius() { return nullptr; }
		virtual COMPONENT::HEIGHT* componentHeight() { return nullptr; }
		virtual COMPONENT::ACTIVE_BEHAVIOR* componentActiveBehavior() { return nullptr; }
		virtual COMPONENT::PHYSICS* componentPhysics() { return nullptr; }

		virtual std::string saveDataString() { return std::string(); }
		virtual void stringDataLoad(STRING_TREE* StringTree) {};
		void Delete() { IsDelete = true; }
		bool isDelete() { return IsDelete;}
	private:
		bool IsDelete = false;
	};
}

