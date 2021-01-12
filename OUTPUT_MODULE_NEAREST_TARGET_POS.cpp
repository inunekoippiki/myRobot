#include "../Library/VECTOR3.h"
#include "UI_ANNOTATION.h"
#include "ROBOT_PROCESSOR.h"
#include "ROBOT_MODULE.h"
#include "ENTITY_ROBOT.h"
#include "ENTITY_MANAGER.h"
#include "ENTITY_MEDIATOR.h"
#include "OUTPUT_MODULE_NEAREST_TARGET_POS.h"
OUTPUT_MODULE_NEAREST_TARGET_POS::OUTPUT_MODULE_NEAREST_TARGET_POS(
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
	robotProcessor.addOutputModule("��ԋ߂��ڕW�ʒux", OUTPUT_MODULE_DATA({ &ModuleList[0],robotModule->uiAnnotation("��ԋ߂��ڕW�ʒux") }));
	robotProcessor.addOutputModule("��ԋ߂��ڕW�ʒuy", OUTPUT_MODULE_DATA({ &ModuleList[1],robotModule->uiAnnotation("��ԋ߂��ڕW�ʒuy") }));
	robotProcessor.addOutputModule("��ԋ߂��ڕW�ʒuz", OUTPUT_MODULE_DATA({ &ModuleList[2],robotModule->uiAnnotation("��ԋ߂��ڕW�ʒuz") }));

}

OUTPUT_MODULE_NEAREST_TARGET_POS::~OUTPUT_MODULE_NEAREST_TARGET_POS() {
}

void OUTPUT_MODULE_NEAREST_TARGET_POS::update() {
	Pos = EntityMediator->nearestTargetPos(Robot->pos());
}