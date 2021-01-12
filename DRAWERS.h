#pragma once
#include <vector>
class SHADER;
namespace DRAWER {
	class BASE;
	class DRAWERS {
	public:
		DRAWERS();
		virtual ~DRAWERS();
		virtual void draw() = 0;
	private:
	};
}