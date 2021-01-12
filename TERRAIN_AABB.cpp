#include <type_traits>
#include "../Library/INDEV.h"
#include "../Library/CONTAINER.h"
#include "../Library/STRING_TREE.h"
#include "../Library/STRING_TREE_SL.h"
#include "DRAWERS_SHADER.h"
#include "INPUT_COMMON.h"
#include "COLLISION_CALLBACK.h"
#include "COLLISION3D_AABB.h"
#include "ENTITY_FACTORY.h"
#include "TERRAIN_AABB.h"
namespace ENTITY {
	TERRAIN_AABB::TERRAIN_AABB(
		CONTAINER* c,
		DRAWER::DRAWERS_SHADER* drawers,
		COMPONENT::COLLISION_LIST* collisionList){
		create(c, drawers, collisionList);
	}
	TERRAIN_AABB::TERRAIN_AABB(ENTITY_FACTORY* entityFactory) : 
		TERRAIN_AABB(
			entityFactory->container(), 
			entityFactory->drawers3d(), 
			entityFactory->collisionManager()->staticCollisions()) {
	}
	TERRAIN_AABB::~TERRAIN_AABB() {
		Drawer->Delete();
		delete Collision;
	}
	void TERRAIN_AABB::update() {
		Drawer->setPos(Position.pos());
		Collision->setPos(Position.pos() - Scale.scale() * 0.5f);
		Drawer->setScale(Scale.scale());
		Collision->setD(Scale.scale());
	}
	void TERRAIN_AABB::activeUpdate(){
		collisionUpdate();
	}
	void TERRAIN_AABB::collisionUpdate() {
		Collision->setPos(Position.pos() - Drawer->scale() * 0.5f);
		Collision->setD(Drawer->scale());
	}
	void TERRAIN_AABB::onCollisionExtrude(const VECTOR3& norm) {
		Position.setPos(Position.pos()+norm);
		Drawer->setPos(Position.pos());
	}
	COMPONENT::POSITION* TERRAIN_AABB::componentPosition(){
		return &Position;
	}
	COMPONENT::SCALE* TERRAIN_AABB::componentScale(){
		return &Scale;
	}
	void TERRAIN_AABB::setPos(const VECTOR3& pos){
		Position.setPos(pos);
	}
	void TERRAIN_AABB::setScale(const VECTOR3& scale){
		Scale.setScale(scale);
	}
	COLLISION3D* TERRAIN_AABB::collision() const {
		return Collision; 
	}
	std::string TERRAIN_AABB::saveDataString() {
		std::string data;
		data += "{";
		{
			data += "type{TERRAIN_AABB}";
			data += "pos{" + STRING_TREE_SAVER::vector3(Position.pos()) + "}";
			data += "scale{" + STRING_TREE_SAVER::vector3(Scale.scale()) + "}";
		}data += "}";

		return data;
	}
	void TERRAIN_AABB::stringDataLoad(STRING_TREE* stringTree) {
		setPos(STRING_TREE_LOADER::vector3(stringTree->atw("pos")));
		setScale(STRING_TREE_LOADER::vector3(stringTree->atw("scale")));
	}
	void TERRAIN_AABB::create(CONTAINER* c, DRAWER::DRAWERS_SHADER* drawers, COMPONENT::COLLISION_LIST* collisionList) {
		Drawer = new DRAWER::BATCH();
		Drawer->setBatch(c->batch("PrimitiveBox"));
		drawers->add(Drawer);
		Collision = new COLLISION3D_AABB(this);
		setScale(VECTOR3::one());
		CollisionHandle = collisionList->create(this);
		collisionUpdate();
	}
}