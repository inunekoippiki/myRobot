#pragma once
#include "../Library/CONTAINER.h"
#include "../Library/STATIC_FONT.h"
#include "UI.h"
#include "UI_CHECK.h"
class SETTING_CHECK {
public:
	SETTING_CHECK();
	~SETTING_CHECK();
	void create(
		CONTAINER* c,
		STATIC_FONT* font,
		const char* name);
	UI* rootUi() { return RootUi; }
	bool isCheck();
	void setCheck(bool isCheck);
private:
	UI* RootUi = nullptr;
	UI* NameUi = nullptr;
	UI_CHECK Check;
	//‰¹
	SOUND* SoundButton = nullptr;
};
