#include "../Library/VECTOR3.h"
#include "COLLISION3D.h"
#include "COLLISION_CALLBACK.h"
#include "COLLISION_MANAGER.h"
namespace COMPONENT {

	COLLISION_MANAGER::COLLISION_MANAGER() {
	}

	COLLISION_MANAGER::~COLLISION_MANAGER() {
	}

	void COLLISION_MANAGER::exeCollisionExtrude() {
		exeCollision(StaticCollisions, PlayerCollisions, hitFuncOnCollisionExtrude());
		exeCollision(StaticCollisions, EnemyCollisions, hitFuncOnCollisionExtrude());
		exeCollision(StaticCollisions, PlayerBulletCollisions, hitFuncOnCollisionExtrude());
		exeCollision(StaticCollisions, EnemyBulletCollisions, hitFuncOnCollisionExtrude());
	}

	void COLLISION_MANAGER::exeCollision() {
		//プレイヤーの攻撃とエネミーは当たる
		exeCollision(PlayerBulletCollisions, EnemyCollisions, hitFuncOnCollision());
		//エネミーの攻撃とプレイヤーは当たる
		exeCollision(EnemyBulletCollisions, PlayerCollisions, hitFuncOnCollision());
		//プレイヤーとエネミーは当たる
		exeCollision(PlayerCollisions, EnemyCollisions, hitFuncOnCollision());
	}
}
