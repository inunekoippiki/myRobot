#pragma once
#include <random>
#include <utility>
#include <vector>
#include "../Library/COLOR.h"
#include "../Library/MATRIX.h"
#include "EFFEKSEER.h"
#include "CAMERA_DEBUG.h"
#include "COLLISION_MANAGER.h"
#include "ENTITY_FACTORY.h"
#include "ROBOT_PROCESSOR.h"
#include "LIGHT.h"
#include "ENTITY_MANAGER.h"
#include "AXIS_DISP.h"
#include "ROUND_MISSION.h"
#include "ERROR_POPUP.h"
#include "CLEAR_ICON.h"
#include "FAILED_ICON.h"
class CONTAINER;
class IMAGE_2D;
class SOFT_SHADOW;
class OUT_LINE_SHADER;
class STATIC_FONT;
namespace DRAWER {
	class DRAWERS_SHADER;
	class STATIC_FONT;
}
namespace ENTITY {
	class ROBOT;
};
class UI;
class SCENE_ROUND;
class SOUND;
class SCENE_ROUND_PLAY{
public:
	SCENE_ROUND_PLAY();
	~SCENE_ROUND_PLAY();
	void create(
		SCENE_ROUND* sceneRound,
		UI* uiRoot,
		COMMON_DATA* commonData,
		SOFT_SHADOW* softShadowShader);
	void setMap(const std::string& mapFileName);
	void setMission(const STRING_TREE& missionData);
	void reset();
	void update();
	void draw();
	void onEnter();
	void onExit();
	ROBOT_PROCESSOR* robotProcessor() { return &RobotProcessor; }
	ROUND_MISSION* roundMission() { return &RoundMission; }
	void debugVariableListUpdate();
private:
	void onClickPlayStart();
	void onClickNextStage();
	void onClickCameraReset();
	void onClickPlayStop();
	void onClickToEdit();

	void play();
	void clear();
	void failed();
	void errorPopupDisp();
	void clearUpdate();
	void failedUpdate();
	void nextRound();
	void shaderSet(SHADER* shader);
	enum class STATE{
		STOP,PLAY,CLEAR,FAILED
	};
	STATE State = STATE::STOP;
	int Timer = 0;
	std::mt19937 Mt19937;
	SCENE_ROUND* SceneRound = nullptr;
	COMMON_DATA* CommonData = nullptr;
	CONTAINER* C = nullptr;
	STATIC_FONT* Font = nullptr;
	IMAGE_2D* Image2dShader = nullptr;
	SOFT_SHADOW* SoftShadowShader = nullptr;
	OUT_LINE_SHADER* OutLineShader = nullptr;
	LIGHT Light;
	CAMERA_DEBUG* Camera = nullptr;
	ENTITY::ROBOT* Robot = nullptr;
	ROBOT_PROCESSOR RobotProcessor;
	UI* PlayToEditSwitchingButtonUi = nullptr;
	UI* WarningIconUi = nullptr;
	UI* PlayButtonUi = nullptr;
	UI* PlayStopButtonUi = nullptr;
	UI* CameraHelpUi = nullptr;
	UI* CameraResetButtonUi = nullptr;

	CLEAR_ICON ClearIcon;
	UI NextStageButtonUi;
	FAILED_ICON FailedIcon;

	ERROR_POPUP ErrorPopup;
	STRING_TREE* MapData = nullptr;
	ROUND_MISSION RoundMission;
	ENTITY_MANAGER EntityManager;

	std::vector<DRAWER::STATIC_FONT*> DebugVariableList;
	AXIS_DISP AxisDisp;
	//‰¹
	SOUND* SoundBgmPlay = nullptr;
	SOUND* SoundBgmStart = nullptr;
	SOUND* SoundBgmEnd = nullptr;
	SOUND* SoundClear = nullptr;
	SOUND* SoundButton = nullptr;

};

