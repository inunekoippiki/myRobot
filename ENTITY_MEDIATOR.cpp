#include "../Library/VECTOR3.h"
#include "ENTITY_AGGREGATE.h"
#include "ENTITY_ROBOT.h"
#include "ENTITY_MEDIATOR.h"

ENTITY_MEDIATOR::ENTITY_MEDIATOR(std::vector<ENTITY::ENTITY*>* entityList) :
	EntityList(entityList) {
}

ENTITY_MEDIATOR::~ENTITY_MEDIATOR() {
}

VECTOR3 ENTITY_MEDIATOR::robotPos(){
	if (Robot == nullptr) {
		return VECTOR3();
	}
	return Robot->pos();
}

VECTOR3 ENTITY_MEDIATOR::nearestItemPos(const VECTOR3& pos){
	return ENTITY_AGGREGATE::nearestItemPos(pos, *EntityList);
}

VECTOR3 ENTITY_MEDIATOR::nearestTargetPos(const VECTOR3& pos){
	return ENTITY_AGGREGATE::nearestTargetPos(pos, *EntityList);
}

VECTOR3 ENTITY_MEDIATOR::nearestGoalPos(const VECTOR3& pos){
	return ENTITY_AGGREGATE::nearestGoalPos(pos, *EntityList);
}
