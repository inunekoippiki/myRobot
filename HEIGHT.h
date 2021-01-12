#pragma once
#include "../Library/common.h"
#include "../Library/VECTOR3.h"
namespace COMPONENT {
	class HEIGHT {
	public:
		HEIGHT();
		~HEIGHT();
		float height()const { return Height; }
		void setHeight(float height);
	private:
		float Height = 0.0f;
	};
}