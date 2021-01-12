#pragma once
#include "../Library/common.h"
#include "COLLISION3D.h"

namespace COMPONENT {
	class COLLISION_MANAGER;
	class COLLISION_LIST;
	/*
	�Փˏ����R�[���o�b�N���邽�߂̃N���X�B
	COLLISION3D* collision()�ŃR���W�����I�u�W�F�N�g���擾����
	���̃I�u�W�F�N�g�ƏՓ˂��Ă���Γo�^���̃R�[���o�b�N�p�֐����Ăяo��
	void onCollision(COLLISION3D* collision)�͑���̏�񂪓n�����
	void onCollisionExtrude(const VECTOR3& norm)�͓��������㉟���߂��Ȃ���΂Ȃ�Ȃ��x�N�g�����n�����
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
	�Փˎ��̏����͗��p���ɏ������ƂɂȂ邯��Ǒ��d�p���ł��Ȃ��Ƃ���
	����ɗ��p���̃C���X�^���X��ݒ肵�Ă������ƂŃI�[�o�[���C�h�݂����Ȃ��Ƃ��ł���
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