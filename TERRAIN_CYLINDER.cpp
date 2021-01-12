#include "../Library/INDEV.h"
#include "../Library/CONTAINER.h"
#include "../Library/STRING_TREE.h"
#include "../Library/STRING_TREE_SL.h"
#include "DRAWERS_SHADER.h"
#include "INPUT_COMMON.h"
#include "COLLISION_CALLBACK.h"
#include "COLLISION3D_CYLINDER_YAA.h"
#include "ENTITY_FACTORY.h"
#include "TERRAIN_CYLINDER.h"
namespace ENTITY {
	TERRAIN_CYLINDER::TERRAIN_CYLINDER(CONTAINER* c, DRAWER::DRAWERS_SHADER* drawers, COMPONENT::COLLISION_LIST* collisionList){
		create(c, drawers, collisionList);
	}
	TERRAIN_CYLINDER::TERRAIN_CYLINDER(ENTITY_FACTORY* entityFactory):
		TERRAIN_CYLINDER(entityFactory->container(), entityFactory->drawers3d(), entityFactory->collisionManager()->staticCollisions()){
	}
	TERRAIN_CYLINDER::~TERRAIN_CYLINDER() {
		Drawer->Delete();
		delete Collision;
	}
	void TERRAIN_CYLINDER::update() {
		Drawer->setPos(Position.pos());
		Collision->setPos(Position.pos() - VECTOR3(0.0f, Drawer->scale().y * 0.5f, 0.0f));
		const float& scaleY = Height.height();
		Drawer->setScale(VECTOR3(Radius.r(), scaleY, Radius.r()));
		Collision->setR(Radius.r());
		const float& r = Radius.r();
		Drawer->setScale(VECTOR3(r, Height.height(), r));
		Collision->setHeight(Height.height());
	}
	void TERRAIN_CYLINDER::activeUpdate(){
	}
	void TERRAIN_CYLINDER::onCollision(COLLISION3D* collision) { 

	}
	void TERRAIN_CYLINDER::onCollisionExtrude(const VECTOR3& norm) {
		Position.setPos(Position.pos() + norm);
		Drawer->setPos(Position.pos());
		Collision->setPos(Position.pos() - Drawer->scale() * 0.5f);
	}
	COMPONENT::POSITION* TERRAIN_CYLINDER::componentPosition(){
		return &Position;
	}
	COMPONENT::RADIUS* TERRAIN_CYLINDER::componentRadius(){
		return &Radius;
	}
	COMPONENT::HEIGHT* TERRAIN_CYLINDER::componentHeight(){
		return &Height;
	}
	void TERRAIN_CYLINDER::setPos(const VECTOR3& pos) {
		Position.setPos(pos);
	}
	void TERRAIN_CYLINDER::setR(float r){
		Radius.setR(r);
	}
	void TERRAIN_CYLINDER::setHeight(float height){
		Height.setHeight(height);
	}
	std::string TERRAIN_CYLINDER::saveDataString() {
		std::string data;
		data += "{";
		{
			data += "type{TERRAIN_CYLINDER}";
			data += "pos{" + STRING_TREE_SAVER::vector3(Position.pos()) + "}";
			data += "height{" + std::to_string(Height.height()) + "}";
			data += "r{" + std::to_string(Radius.r()) + "}";
		}data += "}";

		return data;
	}
	void TERRAIN_CYLINDER::stringDataLoad(STRING_TREE* stringTree) {
		setPos(STRING_TREE_LOADER::vector3(stringTree->atw("pos")));
		setHeight(stringTree->atw("height")->toFloat());
		setR(stringTree->atw("r")->toFloat());
	}
	void TERRAIN_CYLINDER::create(CONTAINER* c, DRAWER::DRAWERS_SHADER* drawers, COMPONENT::COLLISION_LIST* collisionList) {
		Drawer = new DRAWER::BATCH();
		Drawer->setBatch(c->batch("PrimitiveCylinder"));
		drawers->add(Drawer);
		Collision = new COLLISION3D_CYLINDER_YAA(this);
		CollisionHandle = collisionList->create(this);
		setR(1.0f);
		setHeight(1.0f);
	}
}