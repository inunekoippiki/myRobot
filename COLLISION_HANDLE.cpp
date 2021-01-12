#include "COLLISION_HANDLE.h"
#include "COLLISION_CALLBACK.h"
namespace COMPONENT {
	COLLISION_HANDLE::COLLISION_HANDLE(){
	}
	COLLISION_HANDLE::COLLISION_HANDLE(COLLISION_CALLBACK* collision) :
		Collision(collision) {
	}
	COLLISION_HANDLE::~COLLISION_HANDLE() {
		Delete();
	}
	COLLISION_HANDLE& COLLISION_HANDLE::operator=(COLLISION_HANDLE&& rhs)noexcept {
		if (Collision != rhs.Collision) {
			Delete();
		}
		Collision = rhs.Collision;
		rhs.Collision = nullptr;
		return *this;
	}

	void COLLISION_HANDLE::Delete() {
		if (Collision != nullptr) {
			Collision->Delete();
			Collision = nullptr;
		}
	}
}