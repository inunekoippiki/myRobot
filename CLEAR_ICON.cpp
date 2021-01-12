#include "../Library/CONTAINER.h"
#include "CLEAR_ICON.h"
CLEAR_ICON::CLEAR_ICON() {
}

CLEAR_ICON::~CLEAR_ICON() {
}

void CLEAR_ICON::create(CONTAINER* c) {
	ClearIconUi.create(DRAWER::IMAGE2D::instance(c->texture("clearIcon"), VECTOR2(704.0f, 400.0f), VECTOR2::one()));
	ClearIconUi.setIsCollisionDisable(true);
	ClearIconUi.setIsReleaseDisable(true);
	ClearIconUi.setIsDisable(true);
	ClearIconUiMorphTime = 90;
}

void CLEAR_ICON::start(){
	ClearIconUi.setIsDisable(false);
	ClearIconUi.setScale(VECTOR2(0.0f, 1.0f));
	ClearIconUiMorphTimer = 0;
}

void CLEAR_ICON::update(){
	ClearIconUiMorphTimer++;
	if (ClearIconUiMorphTimer <= ClearIconUiMorphTime) {
		ClearIconUi.setScale(VECTOR2(std::lerp(0.0f, 1.0f, (float)ClearIconUiMorphTimer / ClearIconUiMorphTime), 1.0f));
	}
}

void CLEAR_ICON::exit() {
	ClearIconUi.setIsDisable(true);
}
