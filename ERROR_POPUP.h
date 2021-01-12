#pragma once
#include "../Library/STATIC_FONT.h"
#include "UI.h"
class CONTAINER;
class SCENE_ROUND;
class ERROR_POPUP{
public:
	ERROR_POPUP();
	~ERROR_POPUP();
	void create(CONTAINER* c,STATIC_FONT* font, SCENE_ROUND* sceneRound);
	using ERROR_TYPE = decltype(std::declval<ROBOT_COMPILER_ERROR>().errorList());
	void errorPopupDisp(ERROR_TYPE errorList);
	void errorPopupDisp(const char* s, const char* details);
	UI* rootUi() { return ErrorPopup; }
private:
	void onClick(UI* ui);
	CONTAINER* C = nullptr;
	STATIC_FONT* Font = nullptr;
	SCENE_ROUND* SceneRound = nullptr;
	UI* ErrorPopup = nullptr;
	UI* ErrorPopupFront = nullptr;
	//‰¹
	SOUND* SoundError = nullptr;

};

