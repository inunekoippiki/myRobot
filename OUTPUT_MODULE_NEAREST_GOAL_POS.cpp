#include "../Library/VECTOR3.h"
#include "UI_ANNOTATION.h"
#include "ROBOT_PROCESSOR.h"
#include "ROBOT_MODULE.h"
#include "ENTITY_ROBOT.h"
#include "ENTITY_MEDIATOR.h"
#include "OUTPUT_MODULE_NEAREST_GOAL_POS.h"
OUTPUT_MODULE_NEAREST_GOAL_POS::OUTPUT_MODULE_NEAREST_GOAL_POS(
	ROBOT_PROCESSOR& robotProcessor,
	ENTITY::ROBOT* robot,
	ROBOT_MODULE* robotModule,
	ENTITY_MEDIATOR* entityMediator) :
	EntityMediator(entityMediator),
	Robot(robot),
	ModuleList(
		{
			OUTPUT_MODULE_SIMPLE(&Pos.x),
			OUTPUT_MODULE_SIMPLE(&Pos.y),
			OUTPUT_MODULE_SIMPLE(&Pos.z)
		}
	) {
	robotProcessor.addOutputModule("ˆê”Ô‹ß‚¢ƒS[ƒ‹ˆÊ’ux", OUTPUT_MODULE_DATA({ &ModuleList[0],robotModule->uiAnnotation("ˆê”Ô‹ß‚¢ƒS[ƒ‹ˆÊ’ux") }));
	robotProcessor.addOutputModule("ˆê”Ô‹ß‚¢ƒS[ƒ‹ˆÊ’uy", OUTPUT_MODULE_DATA({ &ModuleList[1],robotModule->uiAnnotation("ˆê”Ô‹ß‚¢ƒS[ƒ‹ˆÊ’uy") }));
	robotProcessor.addOutputModule("ˆê”Ô‹ß‚¢ƒS[ƒ‹ˆÊ’uz", OUTPUT_MODULE_DATA({ &ModuleList[2],robotModule->uiAnnotation("ˆê”Ô‹ß‚¢ƒS[ƒ‹ˆÊ’uz") }));

}

OUTPUT_MODULE_NEAREST_GOAL_POS::~OUTPUT_MODULE_NEAREST_GOAL_POS() {
}

void OUTPUT_MODULE_NEAREST_GOAL_POS::update() {
	Pos = EntityMediator->nearestGoalPos(Robot->pos());
}