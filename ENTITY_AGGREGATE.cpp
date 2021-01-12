#include "../Library/VECTOR3.h"
#include "ENTITY.h"
#include "ITEM.h"
#include "POSITION.h"
#include "ENTITY_AGGREGATE.h"
ENTITY_AGGREGATE::ENTITY_AGGREGATE() {
}

ENTITY_AGGREGATE::~ENTITY_AGGREGATE() {
}

VECTOR3 ENTITY_AGGREGATE::nearestItemPos(const VECTOR3& pos, const std::vector<ENTITY::ENTITY*>& entityList) {
	ENTITY::ENTITY* nearestItem = nullptr;
	float minSqDistance = FLT_MAX;
	for (auto& i : entityList) {
		if (i->componentItem() == nullptr) continue;
		if (i->componentPosition() == nullptr) continue;
		float sqDistance = sqLength((pos - i->componentPosition()->pos()));
		if (sqDistance < minSqDistance) {
			minSqDistance = sqDistance;
			nearestItem = i;
		}
	}
	if (nearestItem == nullptr) {
		return pos;
	}
	return nearestItem->componentPosition()->pos();
}

VECTOR3 ENTITY_AGGREGATE::nearestTargetPos(const VECTOR3& pos, const std::vector<ENTITY::ENTITY*>& entityList){
	ENTITY::ENTITY* nearestTarget = nullptr;
	float minSqDistance = FLT_MAX;
	for (auto& i : entityList) {
		if (i->componentTarget() == nullptr) continue;
		if (i->componentPosition() == nullptr) continue;
		float sqDistance = sqLength((pos - i->componentPosition()->pos()));
		if (sqDistance < minSqDistance) {
			minSqDistance = sqDistance;
			nearestTarget = i;
		}
	}
	if (nearestTarget == nullptr) {
		return pos;
	}
	return nearestTarget->componentPosition()->pos();
}

VECTOR3 ENTITY_AGGREGATE::nearestGoalPos(const VECTOR3& pos, const std::vector<ENTITY::ENTITY*>& entityList) {
	ENTITY::ENTITY* nearestGoal = nullptr;
	float minSqDistance = FLT_MAX;
	for (auto& i : entityList) {
		if (i->componentGoal() == nullptr) continue;
		if (i->componentPosition() == nullptr) continue;
		float sqDistance = sqLength((pos - i->componentPosition()->pos()));
		if (sqDistance < minSqDistance) {
			minSqDistance = sqDistance;
			nearestGoal = i;
		}
	}
	if (nearestGoal == nullptr) {
		return pos;
	}
	return nearestGoal->componentPosition()->pos();
}
