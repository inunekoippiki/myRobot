#pragma once
#include "UI.h"
//スライダーのUI
class UI_SLIDER{
public:
	UI_SLIDER();
	~UI_SLIDER();
	void create(UI* rootUi,UI* gaugeUi,UI* sliderUi);
	float amount()const;
	UI* rootUi() { return RootUi; }
	void setAmount(float amount);
private:
	//スライダードラッグ中実行する関数
	void onDragUpdate();
	float Amount = 0.0f;//0~1
	UI* RootUi = nullptr;
	UI* GaugeUi = nullptr;
	UI* SliderUi = nullptr;
};

