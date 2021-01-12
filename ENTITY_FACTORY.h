#pragma once
#include <vector>
class VECTOR3;
class CONTAINER;
class STRING_TREE;
namespace ENTITY {
	class ENEMY;
	class ENEMY_CANON;
	class ENTITY;
	class ROBOT;
	class BULLET;
	class EXPLOSION;
	class GOAL;
	class ITEM;
	class TARGET;
	class TERRAIN_AABB;
	class TERRAIN_CYLINDER;
	class TERRAIN_FLOOR;
}
namespace COMPONENT {
	class UPDATER_MANAGER;
	class COLLISION_MANAGER;
	class COLLISION_LIST;
}
namespace DRAWER {
	class DRAWERS_SHADER;
}
namespace EFFEKSEER {
	class MANAGER;
}
class ENTITY_MANAGER;
class ROBOT_PROCESSOR;
class ROUND_MISSION;
class CAMERA_DEBUG;
class ENTITY_FACTORY{
public:
	ENTITY_FACTORY();
	~ENTITY_FACTORY();
	ENTITY::ENEMY* instanceEntityEnemy( const VECTOR3& pos);
	ENTITY::ENEMY_CANON* instanceEntityEnemyCanon( const VECTOR3& pos);
	ENTITY::ROBOT* instanceEntityRobot(ROBOT_PROCESSOR* RobotProcessor, const VECTOR3& pos);
	ENTITY::BULLET* instancePlayerBullet(const VECTOR3& pos, const VECTOR3& velo);
	ENTITY::BULLET* instanceEnemyBullet(const VECTOR3& pos, const VECTOR3& velo);
	ENTITY::GOAL* instanceEntityGoal(const VECTOR3& pos);
	ENTITY::GOAL* instanceEntityGoal(const VECTOR3& pos,float r );
	ENTITY::ITEM* instanceEntityItem(const VECTOR3& pos);
	ENTITY::TARGET* instanceEntityTarget(const VECTOR3& pos);
	ENTITY::TERRAIN_AABB* instanceEntityTerrainAABB(const VECTOR3& pos);
	ENTITY::TERRAIN_AABB* instanceEntityTerrainAABB(const VECTOR3& pos,const VECTOR3& scale);
	ENTITY::TERRAIN_CYLINDER* instanceEntityTerrainCylinder(const VECTOR3& pos);
	ENTITY::TERRAIN_CYLINDER* instanceEntityTerrainCylinder(const VECTOR3& pos,float r,float height);
	ENTITY::ENTITY* instanceEntityFromStringTree(STRING_TREE* stringTree);

	void setContainer(CONTAINER* container) { Container = container; }
	void setUpdaterManager(COMPONENT::UPDATER_MANAGER* updaterManager) { UpdaterManager = updaterManager; }
	void setCollisionManager(COMPONENT::COLLISION_MANAGER* collisionManager) { CollisionManager = collisionManager; }
	void setDrawers3d(DRAWER::DRAWERS_SHADER* drawers3d) { Drawers3d = drawers3d; }
	void setDrawers2d(DRAWER::DRAWERS_SHADER* drawers2d) { Drawers2d = drawers2d; }
	void setEffekseerManager(EFFEKSEER::MANAGER* effekseerManager) { EffekseerManager = effekseerManager; }
	void setAppearTempEntityList(std::vector< ENTITY::ENTITY*>* appearTempEntityList) { AppearTempEntityList = appearTempEntityList; }
	void setEntityManager(ENTITY_MANAGER* entityManager) { EntityManager = entityManager; }
	void setRoundMission(ROUND_MISSION* roundMission) { RoundMission = roundMission; }
	void setCamera(CAMERA_DEBUG* camera) { Camera = camera; }


	CONTAINER* container() { return Container; }
	COMPONENT::UPDATER_MANAGER* updaterManager() { return UpdaterManager; }
	COMPONENT::COLLISION_MANAGER* collisionManager() { return CollisionManager; }
	DRAWER::DRAWERS_SHADER* drawers3d() { return Drawers3d; }
	DRAWER::DRAWERS_SHADER* drawers2d() { return Drawers2d; }
	EFFEKSEER::MANAGER* effekseerManager() { return EffekseerManager; }
	ENTITY_MANAGER* entityManager() { return EntityManager; }
	ROUND_MISSION* roundMission() { return RoundMission; }
	CAMERA_DEBUG* camera() { return Camera; }

private:
	//エンティティを作るための基本リソース-------------------------
	CONTAINER* Container = nullptr;
	COMPONENT::UPDATER_MANAGER* UpdaterManager = nullptr;
	COMPONENT::COLLISION_MANAGER* CollisionManager = nullptr;
	DRAWER::DRAWERS_SHADER* Drawers3d = nullptr;
	DRAWER::DRAWERS_SHADER* Drawers2d = nullptr;
	EFFEKSEER::MANAGER* EffekseerManager = nullptr;
	std::vector< ENTITY::ENTITY*>* AppearTempEntityList = nullptr;
	ENTITY_MANAGER* EntityManager = nullptr;
	ROUND_MISSION* RoundMission = nullptr;
	CAMERA_DEBUG* Camera = nullptr;

};
