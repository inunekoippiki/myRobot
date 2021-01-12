#include "../Library/CONTAINER.h"
#include "DRAWERS_SHADER.h"
#include "COLLISION_CALLBACK.h"
#include "COLLISION3D_TERRAIN.h"
#include "TERRAIN_FLOOR.h"
namespace ENTITY {
	TERRAIN_FLOOR::TERRAIN_FLOOR(CONTAINER* c, DRAWER::DRAWERS_SHADER* drawers, COMPONENT::COLLISION_LIST* collisionList) {
		create(c, drawers, collisionList);
	}
	TERRAIN_FLOOR::~TERRAIN_FLOOR() {
		Drawer->Delete();
		delete Collision;
	}

	void TERRAIN_FLOOR::update(){
	}

	void TERRAIN_FLOOR::activeUpdate(){
	}

	void TERRAIN_FLOOR::onCollisionExtrude(const VECTOR3& norm) {

	}
	void TERRAIN_FLOOR::setPos(const VECTOR3& pos) {
		Drawer->setPos(pos);
	}
	void TERRAIN_FLOOR::setScale(const VECTOR3& scale) {
		Drawer->setScale(scale);
	}
	COLLISION3D* TERRAIN_FLOOR::collision() const { 
		return Collision;
	}
	void TERRAIN_FLOOR::create(CONTAINER* c, DRAWER::DRAWERS_SHADER* drawers, COMPONENT::COLLISION_LIST* collisionList) {
		Drawer = new DRAWER::BATCH();
		Drawer->setBatch(c->batch("Floor"));
		drawers->add(Drawer);
		Collision = new COLLISION3D_TERRAIN(c,this);
		CollisionHandle = collisionList->create(this);
	}
}