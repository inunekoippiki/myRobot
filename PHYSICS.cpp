#include "PHYSICS.h"
namespace COMPONENT {

	void PHYSICS::collide(const VECTOR3& norm) {
		if (norm.x != 0.0f) {
			Velo.x = 0.0f;
		}
		if (norm.y != 0.0f) {
			Velo.y = 0.0f;
		}
		if (norm.z != 0.0f) {
			Velo.z = 0.0f;
		}
	}

	void PHYSICS::update() {
		Velo += Gravity;
		Velo *= AirResistance;
	}
}