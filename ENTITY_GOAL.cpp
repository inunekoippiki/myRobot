#include "../Library/DEBUG_STR.h"
#include "../Library/STRING_TREE.h"
#include "../Library/STRING_TREE_SL.h"
#include "COLLISION3D_SPHERE.h"
#include "COLLISION_MANAGER.h"
#include "ENTITY_FACTORY.h"
#include "ENTITY_GOAL.h"
namespace ENTITY {
	GOAL::GOAL(
		EFFEKSEER::MANAGER* effekseerManager,
		COMPONENT::COLLISION_LIST* collisionList) :
		EffekseerManager(effekseerManager){
		create(effekseerManager, collisionList);
	}

	GOAL::GOAL(ENTITY_FACTORY* entityFactory):
		GOAL(entityFactory->effekseerManager(),
			entityFactory->collisionManager()->enemyBulletCollisions()){
	}

	GOAL::~GOAL() {
		EffekseerManager->stopRoot(GoalEffect);
		delete Collision;
	}
	void GOAL::update(){
		EffekseerManager->setPos(GoalEffect, Position.pos());
		Collision->setPos(Position.pos());
		const float& r = Radius.r();
		EffekseerManager->setScale(GoalEffect, VECTOR3(r, r, r));
		Collision->setR(r);
	}
	void GOAL::activeUpdate(){
		CollisionOnce = false;
	}
	void GOAL::collisionUpdate(){

	}
	void GOAL::onCollision(COLLISION3D* collision) {
		DEBUG_STR* ds = DEBUG_STR::instance();
		if (!CollisionOnce) {
			ds->set("Goal");
		}
		CollisionOnce = true;
	}
	void GOAL::onCollisionExtrude(const VECTOR3& norm){
	}
	void GOAL::setPos(const VECTOR3& pos){
		Position.setPos(pos);
	}
	void GOAL::setR(float r) {
		Radius.setR(r);
	}
	COMPONENT::GOAL* GOAL::componentGoal(){
		return &Goal;
	}
	COMPONENT::POSITION* GOAL::componentPosition(){
		return &Position;
	}
	COMPONENT::RADIUS* GOAL::componentRadius(){
		return &Radius;
	}
	COLLISION3D* GOAL::collision() const {
		return Collision;
	}
	std::string GOAL::saveDataString(){
		std::string data;
		data += "{";
		{
			data += "type{GOAL}";
			data += "pos{" + STRING_TREE_SAVER::vector3(Position.pos()) + "}";
			data += "r{" + std::to_string(Radius.r()) + "}";
		}data += "}";

		return data;
	}
	void GOAL::stringDataLoad(STRING_TREE* stringTree){
		setPos(STRING_TREE_LOADER::vector3(stringTree->atw("pos")));
		setR(stringTree->atw("r")->toFloat());
	}
	void GOAL::create(
		EFFEKSEER::MANAGER* effekseerManager,
		COMPONENT::COLLISION_LIST* collisionList){
		GoalEffect = EffekseerManager->play("goalPoint", Position.pos());
		Collision = new COLLISION3D_SPHERE(this);
		setPos(VECTOR3());
		setR(1.0);
		CollisionHandle = collisionList->create(this);
		collisionUpdate();
	}
}