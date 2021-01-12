#include "../Library/STRING_TREE.h"
#include "ENTITY_ENEMY_CANON.h"
#include "ENTITY_ENEMY.h"
#include "ENTITY_ROBOT.h"
#include "ENTITY_BULLET.h"
#include "ENTITY_GOAL.h"
#include "ENTITY_ITEM.h"
#include "ENTITY_TARGET.h"
#include "TERRAIN_AABB.h"
#include "TERRAIN_CYLINDER.h"
#include "TERRAIN_FLOOR.h"
#include "COLLISION_MANAGER.h"
#include "ENTITY_MANAGER.h"
#include "ENTITY_MEDIATOR.h"
#include "ENTITY_FACTORY.h"

ENTITY_FACTORY::ENTITY_FACTORY(){
}

ENTITY_FACTORY::~ENTITY_FACTORY(){
}

ENTITY::ENEMY* ENTITY_FACTORY::instanceEntityEnemy(const VECTOR3& pos){
    ENTITY::ENEMY* p = new ENTITY::ENEMY(this);
    p->setPos(pos);
    AppearTempEntityList->push_back(p);
    return p;
}

ENTITY::ENEMY_CANON* ENTITY_FACTORY::instanceEntityEnemyCanon(const VECTOR3& pos){
    ENTITY::ENEMY_CANON* p = new ENTITY::ENEMY_CANON(this);
    p->setPos(pos);
    AppearTempEntityList->push_back(p);
    return p;
}

ENTITY::ROBOT* ENTITY_FACTORY::instanceEntityRobot(ROBOT_PROCESSOR* RobotProcessor, const VECTOR3& pos){
    ENTITY::ROBOT* p = new ENTITY::ROBOT(this,RobotProcessor);
    EntityManager->entityMediator()->setRobot(p);
    p->setPos(pos);
    return p;
}

ENTITY::BULLET* ENTITY_FACTORY::instancePlayerBullet(const VECTOR3& pos, const VECTOR3& velo){
    ENTITY::BULLET* p = new ENTITY::BULLET(this,CollisionManager->playerBulletCollisions());
    p->setPos(pos);
    p->setVelo(velo);
    AppearTempEntityList->push_back(p);
    return p;
}

ENTITY::BULLET* ENTITY_FACTORY::instanceEnemyBullet(const VECTOR3& pos, const VECTOR3& velo){
    ENTITY::BULLET* p = new ENTITY::BULLET(this, CollisionManager->enemyBulletCollisions());
    p->setPos(pos);
    p->setVelo(velo);
    AppearTempEntityList->push_back(p);
    return p;
}

ENTITY::GOAL* ENTITY_FACTORY::instanceEntityGoal(const VECTOR3& pos){
    ENTITY::GOAL* p = new ENTITY::GOAL(this);
    p->setPos(pos);
    AppearTempEntityList->push_back(p);
    return p;
}

ENTITY::GOAL* ENTITY_FACTORY::instanceEntityGoal(const VECTOR3& pos, float r){
    ENTITY::GOAL* p = new ENTITY::GOAL(this);
    p->setPos(pos);
    p->setR(r);
    AppearTempEntityList->push_back(p);
    return p;
}

ENTITY::ITEM* ENTITY_FACTORY::instanceEntityItem(const VECTOR3& pos){
    ENTITY::ITEM* p = new ENTITY::ITEM(this);
    p->setPos(pos);
    AppearTempEntityList->push_back(p);
    return p;
}

ENTITY::TARGET* ENTITY_FACTORY::instanceEntityTarget(const VECTOR3& pos){
    ENTITY::TARGET* p = new ENTITY::TARGET(this, CollisionManager->enemyCollisions());
    p->setPos(pos);
    AppearTempEntityList->push_back(p);
    return p;
}

ENTITY::TERRAIN_AABB* ENTITY_FACTORY::instanceEntityTerrainAABB(const VECTOR3& pos){
    ENTITY::TERRAIN_AABB* p = new ENTITY::TERRAIN_AABB(this);
    p->setPos(pos);
    AppearTempEntityList->push_back(p);
    return p;
}

ENTITY::TERRAIN_AABB* ENTITY_FACTORY::instanceEntityTerrainAABB(const VECTOR3& pos, const VECTOR3& scale){
    ENTITY::TERRAIN_AABB* p = new ENTITY::TERRAIN_AABB(this);
    p->setPos(pos);
    p->setScale(scale);
    AppearTempEntityList->push_back(p);
    return p;
}

ENTITY::TERRAIN_CYLINDER* ENTITY_FACTORY::instanceEntityTerrainCylinder(const VECTOR3& pos){
    ENTITY::TERRAIN_CYLINDER* p = new ENTITY::TERRAIN_CYLINDER(this);
    p->setPos(pos);
    AppearTempEntityList->push_back(p);
    return p;
}

ENTITY::TERRAIN_CYLINDER* ENTITY_FACTORY::instanceEntityTerrainCylinder(const VECTOR3& pos, float r, float height){
    ENTITY::TERRAIN_CYLINDER* p = new ENTITY::TERRAIN_CYLINDER(this);
    p->setPos(pos);
    p->setHeight(height);
    p->setR(r);
    AppearTempEntityList->push_back(p);
    return p;
}

ENTITY::ENTITY* ENTITY_FACTORY::instanceEntityFromStringTree(STRING_TREE* stringTree){
    const std::string& type = stringTree->atw("type")->data();
    ENTITY::ENTITY* instanceEntity = nullptr;
    if (type == typeid(ENTITY::BULLET).name()) {
        instanceEntity = new ENTITY::BULLET(this, CollisionManager->playerBulletCollisions());
    }
    else if (type == "ENEMY") {
        instanceEntity = new ENTITY::ENEMY(this);
    }
    else if (type == "ENEMY_CANON") {
        instanceEntity = new ENTITY::ENEMY_CANON(this);
    }
    else if (type == "GOAL") {
        instanceEntity = new ENTITY::GOAL(this);
    }
    else if(type == "ITEM"){
        instanceEntity = new ENTITY::ITEM(this);
    }
    else if (type == "TARGET") {
        instanceEntity = new ENTITY::TARGET(this, CollisionManager->enemyCollisions());
    }
    else if (type == "TERRAIN_AABB") {
        instanceEntity = new ENTITY::TERRAIN_AABB(this);
    }
    else if (type == "TERRAIN_CYLINDER") {
        instanceEntity = new ENTITY::TERRAIN_CYLINDER(this);
    }
    else if (type == typeid(ENTITY::TERRAIN_FLOOR).name()) {
        instanceEntity = new ENTITY::TERRAIN_FLOOR(Container, Drawers3d, CollisionManager->staticCollisions());
    }
    if (instanceEntity==nullptr) {
        WARNING(true, "ENTITY ENTITY_FACTORY::instanceEntityFromStringTree",(type+"‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ").c_str());
    }
    instanceEntity->stringDataLoad(stringTree);
    AppearTempEntityList->push_back(instanceEntity);
    return instanceEntity;
}
