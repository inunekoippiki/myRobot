#include <algorithm>
#include "../Library/INDEV.h"
#include "INPUT_COMMON.h"
#include "UI_SLIDER.h"
UI_SLIDER::UI_SLIDER() {
}

void UI_SLIDER::create(UI* rootUi, UI* gaugeUi, UI* sliderUi){
	RootUi = rootUi;
	GaugeUi = gaugeUi;
	SliderUi = sliderUi;
	RootUi->setIsReleaseDisable(true);
	RootUi->addChilds(GaugeUi);
	GaugeUi->addChilds(SliderUi);
	SliderUi->setIsCollisionDisable(true);
	GaugeUi->setDragUpdate([this]() {onDragUpdate();});
}

float UI_SLIDER::amount() const{
	return Amount;
}

void UI_SLIDER::setAmount(float amount){
	Amount = amount;
	//0~1�𕝂ɃQ�[�WUI���x���W�ɕϊ�
	float x = (GaugeUi->collision()->wh().x - SliderUi->collision()->wh().x) * Amount;
	SliderUi->setPos(VECTOR2(x, 0.0f));
}

void UI_SLIDER::onDragUpdate(){
	//�}�E�X���W���Q�[�WUI�̃��[�J�����W�ɕϊ�
	VECTOR2 pos = GaugeUi->worldPosToLocalPos(INPUT_COMMON::MousePosition(INDEV::instance()));
	//�X���C�_�[UI���Q�[�WUI�𓮂��镝���v�Z
	float gaugeWidth = GaugeUi->collision()->wh().x - SliderUi->collision()->wh().x;
	//�Q�[�WUI����͂ݏo�Ȃ��悤�ɃN�����v
	float x = std::clamp(pos.x - SliderUi->collision()->wh().x * 0.5f, 0.0f, GaugeUi->collision()->wh().x - SliderUi->collision()->wh().x);
	//0~1�ɕϊ�
	Amount = x / gaugeWidth;
	//�X���C�_�[UI�̈ʒu��ݒ�
	SliderUi->setPos(VECTOR2(x, 0.0f));
}


UI_SLIDER::~UI_SLIDER() {
	delete RootUi;
}