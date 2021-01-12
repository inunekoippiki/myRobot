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
		//�v���C���[�̍U���ƃG�l�~�[�͓�����
		exeCollision(PlayerBulletCollisions, EnemyCollisions, hitFuncOnCollision());
		//�G�l�~�[�̍U���ƃv���C���[�͓�����
		exeCollision(EnemyBulletCollisions, PlayerCollisions, hitFuncOnCollision());
		//�v���C���[�ƃG�l�~�[�͓�����
		exeCollision(PlayerCollisions, EnemyCollisions, hitFuncOnCollision());
	}
}
