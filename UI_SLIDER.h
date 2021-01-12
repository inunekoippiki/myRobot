#pragma once
#include "UI.h"
//�X���C�_�[��UI
class UI_SLIDER{
public:
	UI_SLIDER();
	~UI_SLIDER();
	void create(UI* rootUi,UI* gaugeUi,UI* sliderUi);
	float amount()const;
	UI* rootUi() { return RootUi; }
	void setAmount(float amount);
private:
	//�X���C�_�[�h���b�O�����s����֐�
	void onDragUpdate();
	float Amount = 0.0f;//0~1
	UI* RootUi = nullptr;
	UI* GaugeUi = nullptr;
	UI* SliderUi = nullptr;
};

