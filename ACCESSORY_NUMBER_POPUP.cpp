#include "DRAWER_STATIC_FONT.h"
#include "ACCESSORY_NUMBER_POPUP.h"
ACCESSORY_NUMBER_POPUP::ACCESSORY_NUMBER_POPUP() {
}

ACCESSORY_NUMBER_POPUP::~ACCESSORY_NUMBER_POPUP() {
}

void ACCESSORY_NUMBER_POPUP::create(STATIC_FONT* font, DRAWER::DRAWERS_SHADER* drawers2d){
	Drawer = DRAWER::STATIC_FONT::instance("", font, VECTOR2(), VECTOR2());
}

void ACCESSORY_NUMBER_POPUP::pop(int damage,const VECTOR3& pos){
	Drawer->setString(std::to_string(damage));
}

void ACCESSORY_NUMBER_POPUP::update(){
}
