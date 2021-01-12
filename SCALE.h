#pragma once
#include "../Library/common.h"
#include "../Library/VECTOR3.h"
namespace COMPONENT {
	class SCALE {
	public:
		SCALE();
		~SCALE();
		VECTOR3 scale()const { return Scale; }
		void setScale(const VECTOR3& scale);
	private:
		VECTOR3 Scale;
	};
}