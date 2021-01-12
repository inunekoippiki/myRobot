#pragma once
#include "DRAWERS.h"
namespace EFFEKSEER {
	class MANAGER;
}
namespace DRAWER {
	class DRAWERS_EFFEKSEER:public DRAWERS {
	public:
		DRAWERS_EFFEKSEER();
		~DRAWERS_EFFEKSEER();
		void draw() override;
	private:
		EFFEKSEER::MANAGER* EffekseerManager = nullptr;
	};
}