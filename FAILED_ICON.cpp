#include "../Library/CONTAINER.h"
#include "FAILED_ICON.h"
FAILED_ICON::FAILED_ICON() {
}

FAILED_ICON::~FAILED_ICON() {
}

void FAILED_ICON::create(CONTAINER* c){
	FailedIconUi.create(DRAWER::IMAGE2D::instance(c->texture("failedIcon"), VECTOR2(704.0f, 400.0f), VECTOR2::one()));
	FailedIconUi.setIsCollisionDisable(true);
	FailedIconUi.setIsReleaseDisable(true);
	FailedIconUi.setIsDisable(true);
}

void FAILED_ICON::start(){
	FailedIconUi.setIsDisable(false);
	FailedIconUi.setScale(VECTOR2(1.0f, 1.0f));
	FailedIconUi.setPos(VECTOR2(704.0f, -256.0f));
	FailedIconUiVelo = VECTOR2();
}

void FAILED_ICON::update(){
	if (FailedIconUi.pos().y > 400) {
		if (abs(FailedIconUiVelo.y) < 0.5f) {
			FailedIconUiVelo.y = 0.0f;
		}
		FailedIconUi.setPos(VECTOR2(FailedIconUi.pos().x, 400.0f));
		FailedIconUiVelo.y = -FailedIconUiVelo.y * 0.6f;

	}
	FailedIconUiVelo.y += 0.4f;
	FailedIconUi.setPos(FailedIconUi.pos() + FailedIconUiVelo);
}

void FAILED_ICON::exit() {
	FailedIconUi.setIsDisable(true);
}

