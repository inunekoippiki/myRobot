#pragma once
namespace COMPONENT {
	class COLLISION_CALLBACK;
	/*
	�ȑO�̓C���X�^���X�̃|�C���^�𒼐ڎ����Ă��������
	���ʂ�delete�ł��ĊԈႦ�����������̂ł���ŉB��
	*/
	class COLLISION_HANDLE {
	public:
		COLLISION_HANDLE();
		COLLISION_HANDLE(COLLISION_CALLBACK* collision);
		COLLISION_HANDLE& operator=(const COLLISION_HANDLE& rhs) = delete;
		COLLISION_HANDLE& operator=(COLLISION_HANDLE&& rhs) noexcept;
		~COLLISION_HANDLE();
		void Delete();
	private:
		COLLISION_CALLBACK* Collision = nullptr;
	};

}