#include "../Library/CONTAINER.h"
#include "../Library/STRING_TREE.h"
#include "../Library/STRING_TREE_SL.h"
#include "DRAWERS_SHADER.h"
#include "COLLISION3D_AABB.h"
#include "COLLISION_MANAGER.h"
#include "ENTITY_FACTORY.h"
#include "DRAWER_BATCH.h"
#include "DRAWER_IMAGE3D.h"
#include "ENTITY_TARGET.h"
namespace ENTITY {
	TARGET::TARGET(
		ENTITY_FACTORY* entityFactory,
		COMPONENT::COLLISION_LIST* collisionList) :
		Target(entityFactory->roundMission()) {
		create(entityFactory, collisionList);
	}
	TARGET::~TARGET() {
		Drawer->Delete();
		delete Collision;
	}
	void TARGET::update() {
		Drawer->setPos(Position.pos());
		Collision->setPos(Position.pos() - Scale.scale() * 0.5f);
		Drawer->setScale(Scale.scale());
		Collision->setD(Scale.scale());
		HpGauge.setPos(Position.pos() + VECTOR3(0.0f, Scale.scale().y * 0.5f, 0.0f));
	}
	void TARGET::activeUpdate(){
		Physics.update();
		setPos(Position.pos() + Physics.velo());
		HpGauge.setRatio(HitPoint.ratio());
	}
	void TARGET::onCollision(COLLISION3D* collision) {
		if (HitPoint.isDead()) {
			Delete();
		}
	}
	void TARGET::onCollisionExtrude(const VECTOR3& norm) {
		Physics.collide(norm);
		setPos(Position.pos() + norm);
	}
	void TARGET::setPos(const VECTOR3& pos) {
		Position.setPos(pos);
	}
	void TARGET::setScale(const VECTOR3& scale) {
		Scale.setScale(scale);
	}
	COMPONENT::POSITION* TARGET::componentPosition() {
		return &Position;
	}
	COMPONENT::SCALE* TARGET::componentScale(){
		return &Scale;
	}
	COMPONENT::HIT_POINT* TARGET::componentHitPoint(){
		return &HitPoint;
	}
	COMPONENT::TARGET* TARGET::componentTarget(){
		return &Target;
	}
	COLLISION3D* TARGET::collision() const {
		return Collision;
	}
	std::string TARGET::saveDataString() {
		std::string data;
		data += "{";
		{
			data += "type{TARGET}";
			data += "pos{" + STRING_TREE_SAVER::vector3(Position.pos()) + "}";
			data += "scale{" + STRING_TREE_SAVER::vector3(Scale.scale()) + "}";
			data += "hp{" + std::to_string(HitPoint.hp()) + "}";
		}data += "}";

		return data;
	}
	void TARGET::stringDataLoad(STRING_TREE* stringTree) {
		setPos(STRING_TREE_LOADER::vector3(stringTree->atw("pos")));
		setScale(STRING_TREE_LOADER::vector3(stringTree->atw("scale")));
		HitPoint.setHp(stringTree->atw("hp")->toInt());
	}
	void TARGET::create(ENTITY_FACTORY* entityFactory, COMPONENT::COLLISION_LIST* collisionList) {
		CONTAINER* c = entityFactory->container();
		HitPoint.setMaxHp(100);
		HitPoint.hpFull();
		Physics.setGravity(-0.06f);
		Physics.setAirResistance(0.98f);
		Drawer = new DRAWER::BATCH();
		Drawer->setBatch(c->batch("Target"));
		entityFactory->drawers3d()->add(Drawer);
		HpGauge.create(c, entityFactory->drawers2d());
		Collision = new COLLISION3D_AABB(this);
		setScale(VECTOR3(1.0f,1.0f,1.0f));
		setPos(VECTOR3());
		CollisionHandle = collisionList->create(this);
	}
}