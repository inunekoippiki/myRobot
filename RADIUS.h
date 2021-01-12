#pragma once
#include "../Library/common.h"
#include "../Library/VECTOR3.h"
namespace COMPONENT {
	class RADIUS {
	public:
		RADIUS();
		~RADIUS();
		float r() const { return R; }
		void setR(float r);
	private:
		float R = 0.0f;
	};
}