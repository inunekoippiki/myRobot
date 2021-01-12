#pragma once
#include "../Library/STRING_TREE.h"
#include "SCENE.h"
#include "DRAWER_STATIC_FONT.h"
#include "UI_MANAGER.h"
#include "UI_SCROLL.h"
#include "UI_MENU.h"
class IMAGE_2D;
class SCENE_MANAGER;
class STATIC_FONT;
class CONTAINER;
class UI;
class SOUND;
class SCENE_ROUND_SELECT:public SCENE{
public:
	SCENE_ROUND_SELECT(SCENE_MANAGER* sceneManager);
	~SCENE_ROUND_SELECT();
	using NEXT_SCENE_METHOD = void (SCENE_ROUND_SELECT::*)();
	void proc()override;
	void nextSceneRound();

private:
	void onClickYes();
	void onClickNo();
	void onClickToTitle();
	void onClickRound(int round);
	UI* instanceRoundSelectNode(int round);
	void putDialog(int round);
	//リソース
	SCENE_MANAGER* SceneManager = nullptr;
	//次シーン
	NEXT_SCENE_METHOD NextSceneMethod = nullptr;
	void nextSceneTitle();
	//
	UI_MANAGER UiManager;
	UI* RootUi = nullptr;
	UI RoundSelectDialogUi;
	DRAWER::STATIC_FONT* RoundSelectDialogStringDrawer = nullptr;
	UI_SCROLL RoundSelectScroll;
	UI_MENU UiMenu;
	STRING_TREE StageData;
	int SelectRound = 0;
	//音
	SOUND* SoundBgm = nullptr;
	SOUND* SoundButton = nullptr;
};

