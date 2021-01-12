#include "../Library/INDEV.h"
#include "INPUT_COMMON.h"
#include "ENTITY.h"
#include "POSITION.h"
#include "RADIUS.h"
#include "HEIGHT.h"
#include "SCALE.h"
#include "ENTITY_TRANSFORMER.h"
ENTITY_TRANSFORMER::ENTITY_TRANSFORMER() {
	MoveSpeed = 0.1f;
	ScalingSpeed = 0.1f;
}

ENTITY_TRANSFORMER::~ENTITY_TRANSFORMER() {
}

void ENTITY_TRANSFORMER::change(ENTITY::ENTITY* entity){
	switch (State){
	case ENTITY_TRANSFORMER::STATE::NONE:
		break;
	case ENTITY_TRANSFORMER::STATE::POSITION:
		changePosition(entity);
		break;
	case ENTITY_TRANSFORMER::STATE::SCALE:
		changeScale(entity);
		break;
	default:
		break;
	}
}

void ENTITY_TRANSFORMER::changePosition(ENTITY::ENTITY* entity){
	INDEV* indev = INDEV::instance();
	auto position = entity->componentPosition();
	if (position !=nullptr) {
		position->setPos(position->pos() + INPUT_COMMON::Debug3dObjectMove(indev) * MoveSpeed);
	}
}

void ENTITY_TRANSFORMER::changeScale(ENTITY::ENTITY* entity){
	INDEV* indev = INDEV::instance();
	auto scale = entity->componentScale();
	if (scale != nullptr) {
		scale->setScale(scale->scale() + INPUT_COMMON::Debug3dObjectMove(indev) * ScalingSpeed);
	}
	auto radius = entity->componentRadius();
	if (radius != nullptr) {
		const VECTOR3& move = INPUT_COMMON::Debug3dObjectMove(indev);
		radius->setR(radius->r() + (move.x+move.z) * ScalingSpeed);
	}
	auto height = entity->componentHeight();
	if (height != nullptr) {
		height->setHeight(height->height() + INPUT_COMMON::Debug3dObjectMove(indev).y * ScalingSpeed);
	}

}

void ENTITY_TRANSFORMER::changeState(STATE state){
	State = state;
}
