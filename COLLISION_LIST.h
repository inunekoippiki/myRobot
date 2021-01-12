#pragma once
#include <vector>
#include "COLLISION_CALLBACK.h"
#include "COLLISION_HANDLE.h"
namespace COMPONENT {
	class COLLISION_LIST {
	public:
		~COLLISION_LIST();
		//登録元の
		//void onCollision(COLLISION3D* collision)
		//void onCollisionExtrude(const VECTOR3& norm)
		//がヒットしている時呼ばれるようになる
		//COLLISION3D* collision()constはコリジョンオブジェクトを返さなければならない
		template<class T>
		COLLISION_HANDLE create(T* obj) {
			COLLISION_CALLBACK* p = new COLLISION_CALLBACK_(obj);
			List.push_back(p);
			return COLLISION_HANDLE(p);
		}
		//要素を追加

		//要素を削除
		void erase(size_t idx);
		size_t size();
		COLLISION_CALLBACK*& operator[](size_t idx) {
			return List[idx];
		}
	private:
		std::vector<COLLISION_CALLBACK*> List;
	};
}