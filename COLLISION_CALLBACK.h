#pragma once
#include "../Library/common.h"
#include "COLLISION3D.h"

namespace COMPONENT {
	class COLLISION_MANAGER;
	class COLLISION_LIST;
	/*
	衝突情報をコールバックするためのクラス。
	COLLISION3D* collision()でコリジョンオブジェクトを取得して
	他のオブジェクトと衝突していれば登録元のコールバック用関数を呼び出す
	void onCollision(COLLISION3D* collision)は相手の情報が渡される
	void onCollisionExtrude(const VECTOR3& norm)は当たった後押し戻さなければならないベクトルが渡される
	*/

	class COLLISION_CALLBACK {
	public:
		COLLISION_CALLBACK();
		virtual ~COLLISION_CALLBACK() {}
		virtual void onCollision(COLLISION3D* collision) = 0;
		virtual void onCollisionExtrude(const VECTOR3& norm) = 0;
		virtual COLLISION3D* collision()const = 0;
		void Delete() { IsDelete = true; }
		bool isDelete()const { return IsDelete; }
	private:
		bool IsDelete = false;
	};

	HAS_METHOD(onCollision);
	HAS_METHOD(onCollisionExtrude);

	/*
	衝突時の処理は利用側に書くことになるけれど多重継承できないときは
	これに利用側のインスタンスを設定しておくことでオーバーライドみたいなことができる
	*/
	template<class T>
	class COLLISION_CALLBACK_ :public COLLISION_CALLBACK {
	public:
		COLLISION_CALLBACK_(T* obj) :
			Obj(obj) {
		};
		void onCollision(COLLISION3D* collision)override {
			if constexpr (has_method_onCollision<T>::template has_method_type<void (T::*)(COLLISION3D*)>::value) {
				Obj->onCollision(collision);
			}
		}
		void onCollisionExtrude(const VECTOR3& norm)override {
			if constexpr (has_method_onCollisionExtrude<T>::template has_method_type<void (T::*)(const VECTOR3&)>::value) {
				Obj->onCollisionExtrude(norm);
			}
		};
		COLLISION3D* collision()const override {
			return Obj->collision();
		};
	private:
		T* Obj = nullptr;
	};
}