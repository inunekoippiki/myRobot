#include "../Library/INDEV.h"
#include "../Library/CONTAINER.h"
#include "../Library/STRING_TREE.h"
#include "../Library/STRING_TREE_SL.h"
#include "SOUND_MANAGER.h"
#include "DRAWERS_SHADER.h"
#include "COLLISION_CALLBACK.h"
#include "INPUT_COMMON.h"
#include "COLLISION3D_AABB.h"
#include "DRAWER_TREE.h"
#include "DRAWER_BATCH2.h"
#include "ENTITY_MANAGER.h"
#include "ENTITY_MEDIATOR.h"
#include "ENTITY_FACTORY.h"
#include "ENTITY_ENEMY.h"
namespace ENTITY {
	ENEMY::ENEMY(ENTITY_FACTORY* entityFactoty) :
		Target(entityFactoty->roundMission()),
		EntityManager(entityFactoty->entityManager()){
		create(entityFactoty);
	}
	ENEMY::~ENEMY() {
		Drawer->Delete();
		LWheel->Delete();
		RWheel->Delete();
		delete Collision;
	}
	void ENEMY::update() {
		Drawer->setPos(Position.pos());
		Collision->setPos(Position.pos() - Drawer->scale() * 0.5f);
		HpGauge.setPos(Position.pos() + VECTOR3(0.0f, Drawer->scale().y * 0.5f, 0.0f));

		Drawer->update();
		LWheel->setWorld(*Tree.nodeWorld("L_Wheel_Locator"));
		RWheel->setWorld(*Tree.nodeWorld("R_Wheel_Locator"));
		collisionUpdate();
		HpGauge.setRatio(HitPoint.ratio());
	}
	void ENEMY::activeUpdate(){
		VECTOR2 frontVec{ sinf(Drawer->rad().y) ,cosf(Drawer->rad().y) };
		const VECTOR3& targetPos = EntityManager->entityMediator()->robotPos();
		VECTOR2 targetVec = normalize(targetPos.xz() - Position.pos().xz());
		float r = rotate(frontVec, targetVec);
		Position.setPos(Position.pos() + VECTOR3(frontVec.x, 0.0f, frontVec.y) * MoveSpeed);
		Physics.update();
		Position.setPos(Position.pos() + Physics.velo());
		Drawer->setPos(Position.pos());
		if (abs(r) > RotateSpeed) {
			Drawer->setRad(Drawer->rad() + VECTOR3(0.0f, RotateSpeed * (r / abs(r)), 0.0f));
		}
		float lwr = 0.0f;
		float rwr = 0.0f;
		(r < 0 ? lwr : rwr) = abs(r);
		LWheel->setRad(LWheel->rad() + VECTOR3(MoveSpeed + RotateSpeed * lwr, 0.0f, 0.0f));
		RWheel->setRad(RWheel->rad() + VECTOR3(MoveSpeed + RotateSpeed * rwr, 0.0f, 0.0f));
		if (HitPoint.isDead()) {
			Delete();
		}
	}
	void ENEMY::collisionUpdate() {
		Collision->setPos(Drawer->pos() - Drawer->scale() * 0.5f);
		Collision->setD(Drawer->scale());
	}
	void ENEMY::onCollision(COLLISION3D* collision) {
		SOUND_MANAGER* sm = SOUND_MANAGER::instance();
		ENTITY* e = collision->entity();
		bool isHit = false;
		if (e->componentHitPoint() != nullptr) {
			e->componentHitPoint()->damage(Damage);
			isHit = true;
		}
		if (auto targetPhysics = e->componentPhysics();targetPhysics != nullptr) {
			if (auto targetPosition = e->componentPosition();targetPosition != nullptr) {
				targetPhysics->addForce(normalize(targetPosition->pos() - Position.pos())*0.1f);
				isHit = true;
			}
		}
		if (isHit) {
			sm->playSound(SoundExplosion, Position.pos());
			EntityManager->entityFactory()->effekseerManager()->play("explosion", Position.pos());
			Delete();
		}
	}
	void ENEMY::onCollisionExtrude(const VECTOR3& norm) {
		Position.setPos(Position.pos() + norm);
		Physics.collide(norm);
	}
	void ENEMY::setPos(const VECTOR3& pos) {
		Position.setPos(pos);
	}
	void ENEMY::setScale(const VECTOR3& scale) {
		Drawer->setScale(scale);
		Collision->setD(Drawer->scale());
	}
	COLLISION3D* ENEMY::collision() const {
		return Collision;
	}
	COMPONENT::POSITION* ENEMY::componentPosition(){
		return &Position;
	}
	COMPONENT::HIT_POINT* ENEMY::componentHitPoint(){
		return &HitPoint;
	}
	COMPONENT::TARGET* ENEMY::componentTarget() {
		return &Target; 
	}
	std::string ENEMY::saveDataString(){
		std::string data;
		data += "{";
		{
			data += "type{ENEMY}";
			data += "pos{" + STRING_TREE_SAVER::vector3(Position.pos()) + "}";
			data += "hp{" + std::to_string(HitPoint.hp()) + "}";
		}data += "}";

		return data;
	}
	void ENEMY::stringDataLoad(STRING_TREE* stringTree){
		setPos(STRING_TREE_LOADER::vector3(stringTree->atw("pos")));
		HitPoint.setHp(stringTree->atw("hp")->toInt());
	}
	void ENEMY::create(ENTITY_FACTORY* entityFactory){
		CONTAINER* c = entityFactory->container();
		DRAWER::DRAWERS_SHADER* drawers3d = entityFactory->drawers3d();
		DRAWER::DRAWERS_SHADER* drawers2d = entityFactory->drawers2d();
		COMPONENT::COLLISION_LIST* collisionList = entityFactory->collisionManager()->enemyCollisions();
		COMPONENT::UPDATER_MANAGER* updaterManager = entityFactory->updaterManager();

		RotateSpeed = 0.04f;
		MoveSpeed = 0.1f;

		Drawer = new DRAWER::TREE;
		Tree = c->treeOrigin("enemy");
		Drawer->setTree(&Tree);
		drawers3d->add(Drawer);

		RWheel = new DRAWER::BATCH2();
		RWheel->setBatch(c->batch("enemyRightWheel"));
		drawers3d->add(RWheel);

		LWheel = new DRAWER::BATCH2();
		LWheel->setBatch(c->batch("enemyLeftWheel"));
		drawers3d->add(LWheel);

		HpGauge.create(c, drawers2d);
		Collision = new COLLISION3D_AABB(this);
		CollisionHandle = collisionList->create(this);
		Physics.setGravity(-0.06f);
		Physics.setAirResistance(0.98f);
		HitPoint.setMaxHp(30);
		HitPoint.hpFull();
		Damage = 60;
		collisionUpdate();

		//‰¹
		SoundExplosion = c->sound("bomb2");

	}
}