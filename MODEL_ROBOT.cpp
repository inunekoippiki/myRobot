#include "../Library/CONTAINER.h"
#include "DRAWERS_SHADER.h"
#include "DRAWER_TREE.h"
#include "DRAWER_TREE2.h"
#include "DRAWER_BATCH2.h"
#include "MODEL_ROBOT.h"
MODEL_ROBOT::MODEL_ROBOT() {
}

MODEL_ROBOT::~MODEL_ROBOT() {
	Drawer->Delete();
	LWheel->Delete();
	RWheel->Delete();
	CanonDrawer->Delete();
}

void MODEL_ROBOT::create(CONTAINER* c,DRAWER::DRAWERS_SHADER* drawers3d){
	Drawer = new DRAWER::TREE();
	Tree = c->treeOrigin("robot");
	Drawer->setTree(&Tree);
	drawers3d->add(Drawer);

	CanonDrawer = new DRAWER::TREE2();
	CanonTree = c->treeOrigin("robotCanon");
	CanonDrawer->setTree(&CanonTree);
	drawers3d->add(CanonDrawer);

	RWheel = new DRAWER::BATCH2();
	RWheel->setBatch(c->batch("robotRightWheel"));
	drawers3d->add(RWheel);
	LWheel = new DRAWER::BATCH2();
	LWheel->setBatch(c->batch("robotLeftWheel"));
	drawers3d->add(LWheel);

	CanonBarrelLocator = CanonDrawer->tree()->nodeWorld("canonBarrelLocator");
	CanonRootLocator = Tree.nodeWorld("CanonRoot_Locator");
	LWheelLocator = Tree.nodeWorld("L_Wheel_Locator");
	RWheelLocator = Tree.nodeWorld("R_Wheel_Locator");
}

void MODEL_ROBOT::setPos(const VECTOR3& pos){
	Drawer->setPos(pos);
}

void MODEL_ROBOT::update(const VECTOR3& pos, float ry, const VECTOR3& canonRad){
	Drawer->setPos(pos);
	Drawer->setRad(VECTOR3(0.0f, ry, 0.0f));
	Drawer->update();
	//¶ŽÔ—Ö
	LWheel->setWorld(*LWheelLocator);
	//‰EŽÔ—Ö
	RWheel->setWorld(*RWheelLocator);
	//–C
	CanonDrawer->setRad(canonRad);
	CanonDrawer->setWorld(*CanonRootLocator);
	CanonDrawer->update();
}

void MODEL_ROBOT::lWheelRotate(float rad){
	LWheel->setRad(LWheel->rad().x + rad);
}

void MODEL_ROBOT::rWheelRotate(float rad){
	RWheel->setRad(RWheel->rad().x + rad);
}

VECTOR3 MODEL_ROBOT::canonPos() const{
	return CanonRootLocator->pos();
}

VECTOR3 MODEL_ROBOT::canonTipPos() const{
	return CanonBarrelLocator->pos();
}

VECTOR3 MODEL_ROBOT::topPos()const { 
	return Drawer->pos() + VECTOR3(0.0f, Drawer->scale().y * 0.5f, 0.0f);
}

VECTOR3 MODEL_ROBOT::minPos() const{
	return Drawer->pos() - Drawer->scale() * 0.5f;
}

VECTOR3 MODEL_ROBOT::scale() const{
	return Drawer->scale();
}
