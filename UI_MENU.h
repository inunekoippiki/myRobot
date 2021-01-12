#pragma once
#include "../Library/CONTAINER.h"
#include "../Library/STATIC_FONT.h"
#include <vector>
#include "UI.h"
class UI_MENU{
public:
	UI_MENU();
	~UI_MENU();
	UI* rootUi() { return RootUi; }
	void create(CONTAINER* c, STATIC_FONT* font);
	void listAdd(CONTAINER* c,STATIC_FONT* font,const char* name,const std::function<void()>& pushFunc);
private:
	void onClickMenu();
	void onClickBack();
	UI* RootUi = nullptr;
	UI* MenuButtonUi = nullptr;
	UI* MenuBerUi = nullptr;
	std::vector<UI*> List;
	//‰¹
	SOUND* SoundButton = nullptr;
};

