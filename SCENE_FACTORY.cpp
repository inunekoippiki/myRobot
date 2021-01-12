#include "SCENE_TITLE.h"
#include "SCENE_ROUND_SELECT.h"
#include "SCENE_ROUND.h"
#include "STAGE_DATA.h"
#include "SCENE_SETTING.h"
#include "SCENE_MAP_EDIT.h"
#include "SCENE_HELP.h"
#include "SCENE_FACTORY.h"

SCENE* SCENE_FACTORY::instanceTitle(SCENE_MANAGER* sceneManager){
	return new SCENE_TITLE(sceneManager);
}

SCENE* SCENE_FACTORY::instanceRoundSelect(SCENE_MANAGER* sceneManager){
	return new SCENE_ROUND_SELECT(sceneManager);
}

SCENE* SCENE_FACTORY::instanceRoundSetting(SCENE_MANAGER* sceneManager){
	return new SCENE_SETTING(sceneManager);
}

SCENE* SCENE_FACTORY::instanceRound(SCENE_MANAGER* sceneManager, const std::string& mapFileName, const std::string& missionFileName, int stageIdx){
	return new SCENE_ROUND(sceneManager, mapFileName, missionFileName, stageIdx);
}

SCENE* SCENE_FACTORY::instanceRound(SCENE_MANAGER* sceneManager, const std::string& mapFileName, const std::string& missionFileName){
	return new SCENE_ROUND(sceneManager, mapFileName, missionFileName, -1);
}

SCENE* SCENE_FACTORY::instanceRound(SCENE_MANAGER* sceneManager, STAGE_DATA* data, int selectRound){
	return new SCENE_ROUND(sceneManager, data->mapFileName(selectRound), data->missionFileName(selectRound), selectRound);
}

SCENE* SCENE_FACTORY::instanceRound(SCENE_MANAGER* sceneManager){
	return new SCENE_ROUND(sceneManager, "testMission","testStage",-1);
}

SCENE* SCENE_FACTORY::instanceMapEdit(SCENE_MANAGER* sceneManager){
	return new SCENE_MAP_EDIT(sceneManager);
}

SCENE* SCENE_FACTORY::instanceHelp(SCENE_MANAGER* sceneManager){
	return new SCENE_HELP(sceneManager);
}
