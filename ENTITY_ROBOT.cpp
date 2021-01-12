#define _USE_MATH_DEFINES
#include <cmath>
#include "../Library/NODE.h"
#include "../Library/INDEV.h"
#include "../Library/CONTAINER.h"
#include "../Library/DEBUG_STR.h"
#include "../Library/STRING_TREE.h"
#include "SCENE_ROUND.h"
#include "DRAWER_TREE.h"
#include "DRAWER_BATCH2.h"
#include "DRAWER_TREE2.h"
#include "DRAWER_IMAGE3D.h"
#include "DRAWERS_SHADER.h"
#include "INPUT_COMMON.h"
#include "COLLISION_CALLBACK.h"
#include "COLLISION3D_AABB.h"
#include "UI_ANNOTATION.h"
#include "ENTITY_BULLET.h"
#include "ENTITY_FACTORY.h"
#include "ENTITY_MEDIATOR.h"
#include "GOAL.h"
#include "ROUND_MISSION.h"
#include "ENTITY_MANAGER.h"
#include "ENTITY_ROBOT.h"
namespace ENTITY {
	ROBOT::ROBOT(
		ENTITY_FACTORY* entityFactory,
		ROBOT_PROCESSOR* robotProcessor) :
		EntityManager(entityFactory->entityManager()),
		RoundMission(entityFactory->roundMission()),
		InputModuleList(
			{
				INPUT_MODULE_SIMPLE(&CanonVerticalRad) ,
				INPUT_MODULE_SIMPLE(&CanonHorizontalRad) ,
				INPUT_MODULE_SIMPLE(&CanonShot),
				INPUT_MODULE_SIMPLE(&RightWheelPower),
				INPUT_MODULE_SIMPLE(&LeftWheelPower)
			}
		),
		RobotProcessor(robotProcessor),
		RobotModule("Assets/robotModuleData.txt"),
		OutputModuleNearestItemPos(*RobotProcessor, this, &RobotModule, EntityManager->entityMediator()),
		OutputModuleRobotPos(*RobotProcessor, this, &RobotModule),
		OutputModuleNearestGoalPos(*RobotProcessor, this, &RobotModule, EntityManager->entityMediator()),
		OutputModuleNearestTargetPos(*RobotProcessor, this, &RobotModule, EntityManager->entityMediator()) {

		create(EntityManager->entityFactory());
	}
	ROBOT::~ROBOT() {
		for (auto& i : DebugDrawerPosition) {
			i->Delete();
		}
		delete Collision;
	}
	void ROBOT::reset() {
		CanonVerticalRad = 0.0f;
		CanonHorizontalRad = 0.0f;
		CanonShot = 0.0f;
		CanonShotTimer = 0;
		RightWheelPower = 0.0f;
		LeftWheelPower = 0.0f;
		Rad = VECTOR3();
		Physics.setVelo(VECTOR3());
		HitPoint.hpFull();
	}
	void ROBOT::update() {
		constexpr float degToRad = (float)M_PI / 180.0f;
		Model.update(Position.pos(), Rad.y, VECTOR3(CanonVerticalRad * degToRad, CanonHorizontalRad * degToRad, 0.0f));
		HpGauge.setRatio(HitPoint.ratio());
		HpGauge.setPos(Model.topPos());
		Collision->setPos(Model.minPos());
		Collision->setD(Model.scale());
	}
	void ROBOT::activeUpdate(){
		DEBUG_STR* ds = DEBUG_STR::instance();
		INDEV* indev = INDEV::instance();
		Physics.update();
		Position.setPos(Position.pos() + Physics.velo());
		if (!HitPoint.isDead()) {
			aliveUpdate();
		}
		constexpr float degToRad = (float)M_PI / 180.0f;

		CanonShotTimer += clamp(CanonShot * 0.01f, 0.0f, 1.0f);

		OutputModuleNearestItemPos.update();
		OutputModuleRobotPos.update();
		OutputModuleNearestGoalPos.update();
		OutputModuleNearestTargetPos.update();
		RobotProcessor->stepIn();
		if (HitPoint.isDead()) {
			RoundMission->deadRobot();
		}
	}
	void ROBOT::collisionUpdate() {
		Collision->setPos(Model.minPos());
		Collision->setD(Model.scale());
	}
	void ROBOT::onCollision(COLLISION3D* collision) {
		ENTITY* entity = collision->entity();
		if (entity->componentItem() != nullptr) {
			collision->entity()->Delete();
			RoundMission->getItem();
		}
		if (COMPONENT::GOAL* goal = entity->componentGoal();goal != nullptr) {
			if (!goal->isAlreadyGoal()) {
				goal->setIsAlreadyGoal(true);
				RoundMission->goal();
			}
		}
	}
	void ROBOT::onCollisionExtrude(const VECTOR3& norm) {
		Position.setPos(Position.pos() + norm);
		Physics.collide(norm);
	}
	void ROBOT::setPos(const VECTOR3& pos) {
		Position.setPos(pos);
		Collision->setPos(Model.minPos());
	}
	COLLISION3D* ROBOT::collision() const {
		return Collision;
	}
	COMPONENT::HIT_POINT* ROBOT::componentHitPoint() {
		return &HitPoint;
	}
	COMPONENT::POSITION* ROBOT::componentPosition() {
		return &Position;
	}
	void ROBOT::create(ENTITY_FACTORY* entityFactory) {
		create(entityFactory->container(),
			entityFactory->drawers3d(),
			entityFactory->drawers2d(),
			entityFactory->collisionManager()->playerCollisions());
	}
	void ROBOT::create(CONTAINER* c,
		DRAWER::DRAWERS_SHADER* drawers3d,
		DRAWER::DRAWERS_SHADER* drawers2d,
		COMPONENT::COLLISION_LIST* collisionList) {
		Model.create(c, drawers3d);
		HitPoint.setMaxHp(100);
		HitPoint.hpFull();

		HpGauge.create(c, drawers2d);

		Collision = new COLLISION3D_AABB(this);
		CollisionHandle = collisionList->create(this);
		Physics.setGravity(-0.06f);
		Physics.setAirResistance(0.98f);
		INPUT_MODULE_LIST inputModuleList{ {
		{ "–CŠp“x(c)",{&InputModuleList[0] ,RobotModule.uiAnnotation("–CŠp“x(c)") } },
		{ "–CŠp“x(‰¡)",{&InputModuleList[1] ,RobotModule.uiAnnotation("–CŠp“x(‰¡)") } },
		{ "–C”­ŽË",{&InputModuleList[2] ,RobotModule.uiAnnotation("–C”­ŽË") } },
		{ "‰EŽÔ—Ö",{&InputModuleList[3] ,RobotModule.uiAnnotation("‰EŽÔ—Ö") } },
		{ "¶ŽÔ—Ö",{&InputModuleList[4] ,RobotModule.uiAnnotation("¶ŽÔ—Ö") } }
		} };

		RobotProcessor->createInputModuleList(std::move(inputModuleList));
		collisionUpdate();
		for (int i = 0;i < 16;i++) {
			DRAWER::IMAGE3D* drawer = new DRAWER::IMAGE3D();
			drawer->setTexture(c->texture("nodeConnectorIcon"));
			drawer->setScale(VECTOR2(5.0f, 5.0f));
			drawer->setColor(COLOR(1.0f, 1.0f, 1.0f, 0.5f));
			drawer->setPivot(drawer->drawMethodInvisible());
			DebugDrawerPosition.push_back(drawer);
			SCENE_ROUND::DebugDrawerImage3d->add(drawer);
		}
	}
	void ROBOT::aliveUpdate() {
		const VECTOR3& pos = Position.pos();
		//¶‰EŽÔ—Ö‚Ì•
		float l = 1.0f;
		//¶ŽÔ—Ö‚ÌˆÊ’u
		VECTOR2 LeftWheelPos = rotate(pos.xz() + VECTOR2(l*0.5f, 0.0f), Rad.y, pos.xz());
		//‰EŽÔ—Ö‚ÌˆÊ’u
		VECTOR2 RightWheelPos = rotate(pos.xz() + VECTOR2(-l * 0.5f, 0.0f), Rad.y, pos.xz());
		//¶ŽÔ—Ö‚©‚ç’†SA‰EŽÔ—Ö‚ÉŒü‚©‚¤ƒxƒNƒgƒ‹
		VECTOR2 rv = normalize(LeftWheelPos - pos.xz());
		VECTOR2 move;
		DebugDrawerPosition[0]->setPos(pos);
		//¶ŽÔ—Ö‚ªi‚Þ‹——£
		float LeftWheelPower_ = std::clamp(LeftWheelPower*0.01f, -1.0f, 1.0f) * WheelPower;
		//‰EŽÔ—Ö‚ªi‚Þ‹——£
		float RightWheelPower_ = std::clamp(RightWheelPower * 0.01f, -1.0f, 1.0f) * WheelPower;
		//¶‰EŽÔ—Ö‚ð“®‚©‚µ‚½•ª‚¾‚¯“®‚­
		//¶‰Ei‚Þ‹——£ˆê‚¾‚Æ‰ñ“]‚Ì’†S‚Í‹‚ß‚ç‚ê‚È‚¢
		if (RightWheelPower_ != LeftWheelPower_) {
			//¶ŽÔ—Ö‚©‚ç’†S‚Ü‚Å‚Ì‹——£
			float rl = (LeftWheelPower_ * l) / (RightWheelPower_ - LeftWheelPower_);
			//‰~Žü‚ÌŠ„‡‚ð‹‚ß‚é
			float r = 0.0f;
			if (rl != 0.0f) {
				r = LeftWheelPower_ / (2.0f * (float)M_PI * rl);
			}
			else {
				r = RightWheelPower_ / (2.0f * (float)M_PI * (rl + l));
			}			
			//‰~Žü‚ÌŠ„‡‚©‚ç‰ñ“]Šp“x‚ð‹‚ß‚é
			r *= 2.0f * (float)M_PI;
			Rad.y += r;
			VECTOR2 o = LeftWheelPos + rv * rl;
			VECTOR2 p = rotate(pos.xz(), r, o);
			DebugDrawerPosition[3]->setPos(VECTOR3(o.x, pos.y, o.z));
			Position.setPos(VECTOR3(p.x, pos.y, p.z));
		}
		else {
			VECTOR2 p = rotate(VECTOR2(0.0f, 1.0f), Rad.y) * RightWheelPower_;
			Position.setPos(Position.pos() + VECTOR3(p.x, 0.0f, p.z));
		}
		Model.lWheelRotate(LeftWheelPower_);
		Model.rWheelRotate(RightWheelPower_);
		if (CanonShotTimer >= CanonShotInterval) {
			CanonShotTimer = 0;
			VECTOR3 pos = Model.canonTipPos();
			VECTOR3 velo = pos - Model.canonPos();
			EntityManager->entityFactory()->instancePlayerBullet(pos, normalize(velo));
		}
	}
}
