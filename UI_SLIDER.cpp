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
	//0~1を幅にゲージUI上のx座標に変換
	float x = (GaugeUi->collision()->wh().x - SliderUi->collision()->wh().x) * Amount;
	SliderUi->setPos(VECTOR2(x, 0.0f));
}

void UI_SLIDER::onDragUpdate(){
	//マウス座標をゲージUIのローカル座標に変換
	VECTOR2 pos = GaugeUi->worldPosToLocalPos(INPUT_COMMON::MousePosition(INDEV::instance()));
	//スライダーUIがゲージUIを動ける幅を計算
	float gaugeWidth = GaugeUi->collision()->wh().x - SliderUi->collision()->wh().x;
	//ゲージUIからはみ出ないようにクランプ
	float x = std::clamp(pos.x - SliderUi->collision()->wh().x * 0.5f, 0.0f, GaugeUi->collision()->wh().x - SliderUi->collision()->wh().x);
	//0~1に変換
	Amount = x / gaugeWidth;
	//スライダーUIの位置を設定
	SliderUi->setPos(VECTOR2(x, 0.0f));
}


UI_SLIDER::~UI_SLIDER() {
	delete RootUi;
}