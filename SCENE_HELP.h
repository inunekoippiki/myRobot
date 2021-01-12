#pragma once
#include "UI_MANAGER.h"
#include "HELP_WINDOW.h"
#include "UI_MENU.h"
#include "SCENE.h"
class IMAGE_2D;
class STATE_MANAGER;
class SCENE_HELP:public SCENE{
public:
	SCENE_HELP(SCENE_MANAGER* sceneManager);
	~SCENE_HELP();
	void create(SCENE_MANAGER* sceneManager);
	void proc()override;
	using NEXT_SCENE_METHOD = void (SCENE_HELP::*)();
private:
	void onClickBack();
	//���V�[��
	NEXT_SCENE_METHOD NextSceneMethod = nullptr;
	void nextScene();
	//���\�[�X
	SCENE_MANAGER* SceneManager = nullptr;
	//UI
	UI_MANAGER UiManager;
	UI* RootUi = nullptr;
	UI* BackUi = nullptr;
	HELP_WINDOW HelpWindow;
	//��
	SOUND* SoundButton = nullptr;
};

