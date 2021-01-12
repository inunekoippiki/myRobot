#pragma once
#include <string>
class SCENE;
class SCENE_MANAGER;
class STAGE_DATA;
namespace SCENE_FACTORY {
	SCENE* instanceTitle(SCENE_MANAGER* sceneManager);
	SCENE* instanceRoundSelect( SCENE_MANAGER* sceneManager);
	SCENE* instanceRoundSetting(SCENE_MANAGER* sceneManager);
	SCENE* instanceRound(SCENE_MANAGER* sceneManager, const std::string& mapFileName, const std::string& missionFileName, int stageIdx);
	SCENE* instanceRound(SCENE_MANAGER* sceneManager, const std::string& mapFileName, const std::string& missionFileName);
	SCENE* instanceRound(SCENE_MANAGER* sceneManager, STAGE_DATA* data, int selectRound);
	SCENE* instanceRound(SCENE_MANAGER* sceneManager);
	SCENE* instanceMapEdit(SCENE_MANAGER* sceneManager);
	SCENE* instanceHelp(SCENE_MANAGER* sceneManager);

}