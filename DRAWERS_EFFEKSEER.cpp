#include "EFFEKSEER.h"
#include "DRAWERS_EFFEKSEER.h"
namespace DRAWER {
	DRAWERS_EFFEKSEER::DRAWERS_EFFEKSEER() {
	}

	DRAWERS_EFFEKSEER::~DRAWERS_EFFEKSEER() {
	}
	void DRAWERS_EFFEKSEER::draw(){
		EffekseerManager->draw();
	}
}