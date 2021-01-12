#include "../Library/INDEV.h"
#include "../Library/CONTAINER.h"
#include "../Library/STRING_TREE.h"
#include "../Library/STRING_TREE_SL.h"
#include "INPUT_COMMON.h"
#include "DRAWERS_SHADER.h"
#include "COLLISION_CALLBACK.h"
#include "COLLISION3D_AABB.h"
#include "DRAWER_TREE.h"
#include "DRAWER_BATCH2.h"
#include "DRAWER_TREE2.h"
#include "ENTITY_MANAGER.h"
#include "ENTITY_MEDIATOR.h"
#include "ENTITY_FACTORY.h"
#include "ENTITY_BULLET.h"
#include "SOUND_MANAGER.h"
#include "ENTITY_ENEMY_CANON.h"
namespace ENTITY {
	ENEMY_CANON::ENEMY_CANON(ENTITY_FACTORY* entityFactoty) :
		Target(entityFactoty->roundMission()),
		EntityManager(entityFactoty->entityManager()) {
		create(entityFactoty);
	}
	ENEMY_CANON::~ENEMY_CANON() {
		Drawer->Delete();
		CanonDrawer->Delete();
		LWheel->Delete();
		RWheel->Delete();
		delete Collision;
	}
	void ENEMY_CANON::update() {
		Drawer->setPos(Position.pos());
		Collision->setPos(Position.pos() - Drawer->scale() * 0.5f);
		HpGauge.setPos(Position.pos() + VECTOR3(0.0f, Drawer->scale().y * 0.5f, 0.0f));

		Drawer->update();
		CanonDrawer->setWorld(*Tree.nodeWorld("CanonRoot_Locator"));
		CanonDrawer->update();
		LWheel->setWorld(*Tree.nodeWorld("L_Wheel_Locator"));
		RWheel->setWorld(*Tree.nodeWorld("R_Wheel_Locator"));
		collisionUpdate();
		HpGauge.setRatio(HitPoint.ratio());
	}
	void ENEMY_CANON::activeUpdate(){
		VECTOR2 frontVec{ sinf(Drawer->rad().y) ,cosf(Drawer->rad().y) };
		const VECTOR3& targetPos = EntityManager->entityMediator()->robotPos();
		VECTOR2 targetVec = normalize(targetPos.xz() - Position.pos().xz());
		float r = rotate(frontVec, targetVec);
		Physics.update();
		Position.setPos(Position.pos() + Physics.velo());
		Drawer->setPos(Position.pos());
		if (abs(r) > RotateSpeed) {
			Drawer->setRad(Drawer->rad() + VECTOR3(0.0f, RotateSpeed * (r / abs(r)), 0.0f));
		}
		float lwr = 0.0f;
		float rwr = 0.0f;
		(r < 0 ? lwr : rwr) = abs(r);
		LWheel->setRad(LWheel->rad() + VECTOR3(RotateSpeed * lwr, 0.0f, 0.0f));
		RWheel->setRad(RWheel->rad() + VECTOR3(RotateSpeed * rwr, 0.0f, 0.0f));
		if (HitPoint.isDead()) {
			Delete();
		}
		Timer++;
		if (Timer % CanonShotIntervalFrame == 0) {
			VECTOR3 pos = CanonDrawer->tree()->nodeWorld("canonBarrelLocator")->pos();
			VECTOR3 velo = targetPos - pos;
			VECTOR2 veloXZ = frontVec;
			ENTITY_FACTORY* entityFactory = EntityManager->entityFactory();
			COMPONENT::PHYSICS* physics = entityFactory->instanceEnemyBullet(pos, VECTOR3::zero())->componentPhysics();
			physics->airResistance();
			float t = length(velo);
			float a =  physics->airResistance();
			float g = physics->gyavityY();
			float yl = velo.y;
			float xl = length(velo.xz());
			float A = ((1 / (a - 1)) * g * a * a * (pow(a, t) - 1)) / (a - 1) -
				(g * a * t) / (a - 1);
			float vy = (yl - A) /
				((a * (pow(a, t) - 1)) /
					(a - 1));
			float vx = xl /
				((a * (pow(a, t) - 1)) /
					(a - 1));
			veloXZ *= vx;
			VECTOR3 bulletVec{ veloXZ.x, vy, veloXZ.z };
			physics->addForce(bulletVec);
			CanonDrawer->setRad(VECTOR3(
				acosf(normalize(bulletVec).y) - 1.57f, 0.0f, 0.0f));
			SOUND_MANAGER::instance()->playSound(SoundShot, pos);
		}
	}
	void ENEMY_CANON::collisionUpdate() {
		Collision->setPos(Drawer->pos() - Drawer->scale() * 0.5f);
		Collision->setD(Drawer->scale());
	}
	void ENEMY_CANON::onCollision(COLLISION3D* collision) {
	}
	void ENEMY_CANON::onCollisionExtrude(const VECTOR3& norm) {
		Position.setPos(Position.pos() + norm);
		Physics.collide(norm);
	}
	void ENEMY_CANON::setPos(const VECTOR3& pos) {
		Position.setPos(pos);
	}
	void ENEMY_CANON::setScale(const VECTOR3& scale) {
		Drawer->setScale(scale);
		Collision->setD(Drawer->scale());
	}
	COLLISION3D* ENEMY_CANON::collision() const {
		return Collision;
	}
	COMPONENT::POSITION* ENEMY_CANON::componentPosition() {
		return &Position;
	}
	COMPONENT::HIT_POINT* ENEMY_CANON::componentHitPoint() {
		return &HitPoint;
	}
	COMPONENT::TARGET* ENEMY_CANON::componentTarget() {
		return &Target;
	}
	std::string ENEMY_CANON::saveDataString(){
		std::string data;
		data += "{";
		{
			data += "type{ENEMY_CANON}";
			data += "pos{" + STRING_TREE_SAVER::vector3(Position.pos()) + "}";
			data += "hp{" + std::to_string(HitPoint.hp()) + "}";
		}data += "}";

		return data;
	}
	void ENEMY_CANON::stringDataLoad(STRING_TREE* stringTree){
		setPos(STRING_TREE_LOADER::vector3(stringTree->atw("pos")));
		HitPoint.setHp(stringTree->atw("hp")->toInt());
	}
	void ENEMY_CANON::create(ENTITY_FACTORY* entityFactory) {
		CONTAINER* c = entityFactory->container();
		DRAWER::DRAWERS_SHADER* drawers3d = entityFactory->drawers3d();
		DRAWER::DRAWERS_SHADER* drawers2d = entityFactory->drawers2d();
		COMPONENT::COLLISION_LIST* collisionList = entityFactory->collisionManager()->enemyCollisions();
		COMPONENT::UPDATER_MANAGER* updaterManager = entityFactory->updaterManager();

		RotateSpeed = 0.04f;
		CanonShotIntervalFrame = 300;

		Drawer = new DRAWER::TREE;
		Tree = c->treeOrigin("enemy");
		Drawer->setTree(&Tree);
		drawers3d->add(Drawer);

		CanonDrawer = new DRAWER::TREE2();
		CanonTree = c->treeOrigin("enemyCanon");
		CanonDrawer->setTree(&CanonTree);
		drawers3d->add(CanonDrawer);

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
		collisionUpdate();

		SoundShot = c->sound("cannon2");

	}
}