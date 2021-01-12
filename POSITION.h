#pragma once
#include "../Library/common.h"
#include "../Library/VECTOR3.h"
namespace COMPONENT {
	class POSITION {
	public:
		POSITION();
		 ~POSITION();
		 VECTOR3 pos() const{ return Pos; }
		 void setPos(const VECTOR3& pos);
	private:
		VECTOR3 Pos;
	};
}