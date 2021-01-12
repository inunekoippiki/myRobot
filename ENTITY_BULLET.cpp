#include "../Library/DEBUG_STR.h"
#include "../Library/CONTAINER.h"
#include "../Library/SOUND.h"
#include "DRAWER_BATCH.h"
#include "DRAWERS_SHADER.h"
#include "COLLISION3D_SPHERE.h"
#include "COLLISION_MANAGER.h"
#include "ENTITY_FACTORY.h"
#include "HIT_POINT.h"
#include "SOUND_MANAGER.h"
#include "ENTITY_BULLET.h"
namespace ENTITY {
	BULLET::BULLET(
		ENTITY_FACTORY* entityFactory,
		COMPONENT::COLLISION_LIST* collisionList) :
		EffekseerManager(entityFactory->effekseerManager()){
		create(entityFactory->drawers3d(),entityFactory->container(),collisionList);
	}

	BULLET::~BULLET() {
		Drawer->Delete();
		delete Collision;
	}
	void BULLET::update() {
		Collision->setPos(Pos);
		Drawer->setPos(Pos);
	}
	void BULLET::activeUpdate()	{
		CollisionOnce = false;
		Timer++;
		if (Timer > LifeTime) {
			Delete();
		}
		Physics.update();
		Pos += Physics.velo();
	}
	void BULLET::onCollision(COLLISION3D* collision) {
		if (collision->entity()->componentHitPoint() != nullptr) {
			collision->entity()->componentHitPoint()->damage(30);
			Delete();
			EffekseerManager->play("canonHit", Pos);
			SOUND_MANAGER::instance()->playSound(SoundBomb, Pos);
		}
		DEBUG_STR* ds = DEBUG_STR::instance();
		ds->set("bullet x:%f y:%f z:%f", Pos.x, Pos.y, Pos.z);
		if (!CollisionOnce) {
			ds->set("Hit");
		}
		CollisionOnce = true;
	}
	void BULLET::onCollisionExtrude(const VECTOR3& norm) {
		if (!norm.isZero()) {
			Physics.collide(norm);
			setPos(Pos + norm);
			Delete();
			EffekseerManager->play("canonHit", Pos);
			SOUND_MANAGER::instance()->playSound(SoundBomb, Pos);
		}
	}
	void BULLET::setPos(const VECTOR3& pos) {
		Pos = pos;
		Collision->setPos(Pos);
		Drawer->setPos(Pos);
	}
	void BULLET::setVelo(const VECTOR3& velo){
		Physics.addForce(velo);
	}
	void BULLET::setR(float r) {
		R = r;
		Collision->setR(R);
		Drawer->setScale(VECTOR3(R, R, R));
	}
	COMPONENT::PHYSICS* BULLET::componentPhysics(){
		return &Physics;
	}
	COLLISION3D* BULLET::collision() const {
		return Collision;
	}
	void BULLET::create(DRAWER::DRAWERS_SHADER* drawer3d, CONTAINER* c,COMPONENT::COLLISION_LIST* collisionList) {
		R = 0.2f;
		Drawer = new DRAWER::BATCH();
		Drawer->setBatch(c->batch("PrimitiveSphere"));
		Drawer->setPos(Pos);
		Drawer->setScale(VECTOR3(R,R,R));
		drawer3d->add(Drawer);
		Physics.setGravity(-0.01f);
		Physics.setAirResistance(0.99f);
		Collision = new COLLISION3D_SPHERE(this);
		Collision->setPos(Pos);
		Collision->setR(R);
		CollisionHandle = collisionList->create(this);
		LifeTime = 600;
		Damage = 30;
		SoundBomb = c->sound("bomb2");
	}
}