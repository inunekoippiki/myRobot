#include "../Library/STRING_TREE.h"
#include "../Library/STRING_TREE_SL.h"
#include "COLLISION3D_SPHERE.h"
#include "COLLISION_MANAGER.h"
#include "ENTITY_FACTORY.h"
#include "ENTITY_ITEM.h"
namespace ENTITY{
	ITEM::ITEM(EFFEKSEER::MANAGER* effekseerManager,
		COMPONENT::COLLISION_LIST* collisionList) :
		EffekseerManager(effekseerManager){
		create(effekseerManager, collisionList);
	}
	ITEM::ITEM(ENTITY_FACTORY* entityFactory) :
		ITEM(entityFactory->effekseerManager(), 
			entityFactory->collisionManager()->enemyBulletCollisions()) {
	}
	ITEM::~ITEM() {
		EffekseerManager->stopRoot(ItemEffect);
		delete Collision;
	}
	void ITEM::update(){
		EffekseerManager->setPos(ItemEffect, Position.pos());
		Collision->setPos(Position.pos());
		const float& r = Radius.r();
		EffekseerManager->setScale(ItemEffect, VECTOR3(r, r, r));
		Collision->setR(r * 0.1f);
	}
	void ITEM::activeUpdate(){

	}
	void ITEM::onCollision(COLLISION3D* collision){
		Delete();
	}
	void ITEM::onCollisionExtrude(const VECTOR3& norm){
	}
	void ITEM::setPos(const VECTOR3& pos){
		Position.setPos(pos);
	}
	void ITEM::setR(float r){
		Radius.setR(r);
	}
	COMPONENT::ITEM* ITEM::componentItem() { 
		return &Item; 
	}
	COMPONENT::POSITION* ITEM::componentPosition() { 
		Position.setPos(Position.pos());
		return &Position;
	}
	COMPONENT::RADIUS* ITEM::componentRadius(){
		return &Radius;
	}
	COLLISION3D* ITEM::collision() const {
		return Collision;
	}
	std::string ITEM::saveDataString(){
		std::string data;
		data += "{";
		{
			data += "type{ITEM}";
			data += "pos{" + STRING_TREE_SAVER::vector3(Position.pos()) + "}";
			data += "r{" + std::to_string(Radius.r()) + "}";
		}data += "}";

		return data;
	}
	void ITEM::stringDataLoad(STRING_TREE* stringTree){
		setPos(STRING_TREE_LOADER::vector3(stringTree->atw("pos")));
		setR(stringTree->atw("r")->toFloat());
	}

	void ITEM::create(
		EFFEKSEER::MANAGER* effekseerManager,
		COMPONENT::COLLISION_LIST* collisionList){
		ItemEffect = effekseerManager->play("Item", Position.pos());
		Collision = new COLLISION3D_SPHERE(this);
		Collision->setPos(Position.pos());
		setR(1.0f);
		setPos(VECTOR3());
		CollisionHandle = collisionList->create(this);
	}
}