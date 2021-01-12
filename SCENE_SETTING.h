#pragma once
#include "../Library/CONTAINER.h"
#include "../Library/IMAGE_2D.h"
#include "SCENE.h"
#include "UI.h"
#include "UI_MENU.h"
#include "SETTING_SLIDER.h"
#include "SETTING_CHECK.h"
#include "UI_MANAGER.h"
class SCENE_SETTING:public SCENE{
public:
	SCENE_SETTING(SCENE_MANAGER* sceneManager);
	~SCENE_SETTING();
	using NEXT_SCENE_METHOD = void (SCENE_SETTING::*)();
	void proc()override;
private:
	void onClickToTitle();
	//リソース
	SCENE_MANAGER* SceneManager = nullptr;
	//次シーン
	NEXT_SCENE_METHOD NextSceneMethod = nullptr;
	void nextSceneTitle();
	//
	UI_MANAGER UiManager;
	UI* UiRoot = nullptr;
	UI_MENU UiMenu;

	SETTING_SLIDER VolumeSlider;
	SETTING_SLIDER SoundVolumeSlider;
	SETTING_SLIDER BgmVolumeSlider;
	SETTING_SLIDER AimSensitivitySlider;
	SETTING_SLIDER OneFrameProcessSlider;
	SETTING_CHECK DebugDispCheckBox;
	//音
	SOUND* SoundButton = nullptr;
};

