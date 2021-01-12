#pragma once
namespace COMPONENT {
	class COLLISION_CALLBACK;
	/*
	以前はインスタンスのポインタを直接持っていたけれど
	普通にdeleteできて間違えそうだったのでこれで隠す
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