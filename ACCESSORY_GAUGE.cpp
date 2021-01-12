#include "../Library/common.h"
#include "../Library/CONTAINER.h"
#include "DRAWER_IMAGE3D.h"
#include "DRAWERS_SHADER.h"
#include "ACCESSORY_GAUGE.h"
ACCESSORY_GAUGE::ACCESSORY_GAUGE() {
}

ACCESSORY_GAUGE::~ACCESSORY_GAUGE() {
	WARNING(Drawer==nullptr,"create‚³‚ê‚Ä‚¢‚È‚¢","")
	Drawer->Delete();
}

void ACCESSORY_GAUGE::create(CONTAINER* c,DRAWER::DRAWERS_SHADER* drawers2d){
	Drawer = new DRAWER::IMAGE3D;
	Drawer->setTexture(c->texture("enemyHpGauge"));
	Drawer->setPivot(Drawer->drawMethodCentered());
	drawers2d->add(Drawer);
}

void ACCESSORY_GAUGE::setRatio(float ratio){
	Drawer->setScale(VECTOR2(ratio, 1.0f));
}

void ACCESSORY_GAUGE::setPos(const VECTOR3& pos){
	Drawer->setPos(pos);
}
