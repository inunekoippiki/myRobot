#pragma once
#include "SCENE.h"
#include "LIGHT.h"
#include "CAMERA_FIXED.h"
#include "DRAWERS_SHADER.h"
#include "TITLE_ROBOT.h"
#include "UI.h"
#include "UI_MANAGER.h"
class SCENE_MANAGER;
class IMAGE_2D;
class STATIC_FONT;
class CONTAINER;
class SOUND;
class TREE;
namespace DRAWER {
	class BATCH;
	class DRAWERS;
}
class SCENE_TITLE :public SCENE {
public:
	SCENE_TITLE(SCENE_MANAGER* sceneManager);
	~SCENE_TITLE();
	void proc();
	void nextSceneRound();
	void nextSceneSetting();
	void nextSceneTutorial();
	void nextSceneMapEdit();

	using NEXT_SCENE_METHOD = void (SCENE_TITLE::*)();
private:
	void onClickRoundSelect();
	void onClickSetting();
	void onClickExit();
	//タイトルの項目のUIを作る
	void createSelectUi(const char* s, UI* ui, const VECTOR2 pos, const VECTOR2& scale)const;
	//リソース
	SCENE_MANAGER* SceneManager = nullptr;
	//次シーン
	NEXT_SCENE_METHOD NextSceneMethod = nullptr;
	//
	LIGHT Light;
	CAMERA_FIXED Camera;
	DRAWER::DRAWERS_SHADER Drawers3d;
	DRAWER::BATCH* Floor = nullptr;
	TITLE_ROBOT Robot;

	UI_MANAGER UiManager;
	UI* UiRoot = nullptr;
	UI UiTitleName;
	UI UiRoundButton;
	UI UiOptionButton;
	UI UiExitButton;
	UI UiSaveDataDeleteButton;
	//音
	SOUND* SoundBgm = nullptr;
	SOUND* SoundButton = nullptr;
};

