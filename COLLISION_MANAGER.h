#pragma once
#include <vector>
#include "../Library/VECTOR3.h"
#include "../Library/collisionUtil.h"
#include "COLLISION_LIST.h"
#include "COLLISION_CALLBACK.h"
namespace COMPONENT {
	class COLLISION_MANAGER {
	public:
		COLLISION_MANAGER();
		~COLLISION_MANAGER();
		//�����Ȃ��R���W�������X�g�i�n�`�Ȃǁj
		COLLISION_LIST* staticCollisions() { return &StaticCollisions; }
		//�v���C���[�̃R���W�������X�g
		COLLISION_LIST* playerCollisions() { return &PlayerCollisions; }
		//�G�l�~�[�̃R���W�������X�g
		COLLISION_LIST* enemyCollisions() { return &EnemyCollisions; }
		//�v���C���[�̍U���̃R���W�������X�g
		COLLISION_LIST* playerBulletCollisions() { return &PlayerBulletCollisions; }
		//�G�l�~�[�̍U���̃R���W�������X�g
		COLLISION_LIST* enemyBulletCollisions() { return &EnemyBulletCollisions; }
		//
		COLLISION_LIST* dummyCollisions() { return &DummyCollisions; }
		void exeCollisionExtrude();
		void exeCollision();
	private:
		//2�̔��胊�X�g���}�b�`���O
		template <class HIT_FUNC>
		static void exeCollision(COLLISION_LIST& a, COLLISION_LIST& b, const HIT_FUNC& hitfunc) {
			for (int i = 0;i < a.size();) {
				if (a[i]->isDelete()) {
					a.erase(i);
					continue;
				}
				for (int i2 = 0;i2 < b.size();) {
					if (b[i2]->isDelete()) {
						b.erase(i2);
						continue;
					}
					hitfunc(a[i], b[i2]);
					i2++;
				}
				i++;
			}
		};
		//1�̔��胊�X�g�̒��g���m�Ń}�b�`���O
		template <class HIT_FUNC>
		static void exeCollision(COLLISION_LIST& collisions, const HIT_FUNC& hitfunc) {
			for (int i = 0;i < collisions.size();) {
				if (collisions[i]->isDelete()) {
					collisions.erase(i);
					continue;
				}
				for (int i2 = i + 1;i2 < collisions.size();) {
					if (collisions[i2]->isDelete()) {
						collisions.erase(i2);
						continue;
					}
					hitfunc(collisions[i], collisions[i2]);
					i2++;
				}
				i++;
			}
		}
		static constexpr auto hitFuncOnCollision() {
			return [](COLLISION_CALLBACK* a, COLLISION_CALLBACK* b) {
				if (a->collision()->isHit(b->collision())) {
					a->onCollision(b->collision());
					b->onCollision(a->collision());
				}
			};
		}
		//b�������o�����
		static constexpr auto hitFuncOnCollisionExtrude() {
			return [](COLLISION_CALLBACK* a, COLLISION_CALLBACK* b) {
				b->onCollisionExtrude(b->collision()->isHitExtrude(a->collision()));
			};
		}
		COLLISION_LIST PlayerCollisions;
		COLLISION_LIST EnemyCollisions;
		COLLISION_LIST PlayerBulletCollisions;
		COLLISION_LIST EnemyBulletCollisions;
		COLLISION_LIST StaticCollisions;
		COLLISION_LIST DummyCollisions;
	};
}