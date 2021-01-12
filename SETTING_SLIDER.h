#pragma once
#include "../Library/CONTAINER.h"
#include "../Library/STATIC_FONT.h"
#include "DRAWER_STATIC_FONT.h"
#include "SETTING.h"
#include "UI_SLIDER.h"
class SETTING_SLIDER {
public:
	SETTING_SLIDER();
	~SETTING_SLIDER();
	void create(
		CONTAINER* c,
		STATIC_FONT* font,
		const char*name,
		float min, 
		float max,
		float valueUnit,
		bool isRound);

	void create(
		CONTAINER* c,
		STATIC_FONT* font,
		const char* name,
		SETTING_VALUE_SLIDE* settngSlider,
		bool isRound);

	void update();
	UI* rootUi() { return RootUi; }
	float value();
private:
	UI* RootUi = nullptr;
	UI* NameUi = nullptr;
	UI_SLIDER Slider;
	UI* ValueUi = nullptr;
	DRAWER::STATIC_FONT* ValueUiDrawer = nullptr;
	//値の最小
	float Min = 0.0f;
	//値の最大
	float Max = 0.0f;
	//値の単位
	float ValueUnit = 0.0f;
	//値を整数に丸めるか
	bool IsRound = false;
	//音
	SOUND* SoundButton = nullptr;
};

