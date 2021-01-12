#pragma once
#include "../Library/VECTOR3.h"
namespace COMPONENT {

	class PHYSICS {
	public:
		PHYSICS() :AirResistance(1.0f) {};
		~PHYSICS() {};
		void update();
		void collide(const VECTOR3& norm);
		VECTOR3 velo()const { return Velo; }
		void setVelo(const VECTOR3& velo) { Velo = velo; }
		void addForce(const VECTOR3& velo) { Velo += velo; }
		void setGravity(const VECTOR3& gravity) { Gravity = gravity; }
		void setGravity(float gravity) { Gravity.y = gravity; }
		//擬似的なあれなので毎アップデートでVeloにこれが掛けられる 1.0fで抵抗なし
		void setAirResistance(float airResistance) { AirResistance = airResistance; }
		float airResistance() const { return AirResistance; }
		VECTOR3 gravity() const {return Gravity;}
		float gyavityY() const { return Gravity.y; }
	private:
		float AirResistance = 0.0f;
		VECTOR3 Gravity;
		VECTOR3 Velo;
	};
}