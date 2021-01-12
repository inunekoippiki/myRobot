#include "../Library/VECTOR3.h"
#include "UI_ANNOTATION.h"
#include "ROBOT_PROCESSOR.h"
#include "ROBOT_MODULE.h"
#include "ENTITY_ROBOT.h"
#include "OUTPUT_MODULE_ROBOT_POS.h"
OUTPUT_MODULE_ROBOT_POS::OUTPUT_MODULE_ROBOT_POS(
	ROBOT_PROCESSOR& robotProcessor,
	ENTITY::ROBOT* robot,
	ROBOT_MODULE* robotModule ):
	Robot(robot),
	ModuleList(
		{
			OUTPUT_MODULE_SIMPLE(&Pos.x),
			OUTPUT_MODULE_SIMPLE(&Pos.y),
			OUTPUT_MODULE_SIMPLE(&Pos.z)
		}
	) {
	robotProcessor.addOutputModule("�ԗ��ʒux", OUTPUT_MODULE_DATA({ &ModuleList[0],robotModule->uiAnnotation("�ԗ��ʒux") }));
	robotProcessor.addOutputModule("�ԗ��ʒuy", OUTPUT_MODULE_DATA({ &ModuleList[1],robotModule->uiAnnotation("�ԗ��ʒuy") }));
	robotProcessor.addOutputModule("�ԗ��ʒuz", OUTPUT_MODULE_DATA({ &ModuleList[2],robotModule->uiAnnotation("�ԗ��ʒuz") }));
}

OUTPUT_MODULE_ROBOT_POS::~OUTPUT_MODULE_ROBOT_POS() {
}

void OUTPUT_MODULE_ROBOT_POS::update() {
	Pos = Robot->pos();
}