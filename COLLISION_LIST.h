#pragma once
#include <vector>
#include "COLLISION_CALLBACK.h"
#include "COLLISION_HANDLE.h"
namespace COMPONENT {
	class COLLISION_LIST {
	public:
		~COLLISION_LIST();
		//�o�^����
		//void onCollision(COLLISION3D* collision)
		//void onCollisionExtrude(const VECTOR3& norm)
		//���q�b�g���Ă��鎞�Ă΂��悤�ɂȂ�
		//COLLISION3D* collision()const�̓R���W�����I�u�W�F�N�g��Ԃ��Ȃ���΂Ȃ�Ȃ�
		template<class T>
		COLLISION_HANDLE create(T* obj) {
			COLLISION_CALLBACK* p = new COLLISION_CALLBACK_(obj);
			List.push_back(p);
			return COLLISION_HANDLE(p);
		}
		//�v�f��ǉ�

		//�v�f���폜
		void erase(size_t idx);
		size_t size();
		COLLISION_CALLBACK*& operator[](size_t idx) {
			return List[idx];
		}
	private:
		std::vector<COLLISION_CALLBACK*> List;
	};
}