#include "UI_FACTORY.h"
#include "UI_FUNC_ATTACHER.h"
#include "DRAWER_STATIC_FONT.h"
#include "SETTING_SLIDER.h"
SETTING_SLIDER::SETTING_SLIDER() {
}

SETTING_SLIDER::~SETTING_SLIDER() {
	delete RootUi;
}

void SETTING_SLIDER::create(
	CONTAINER* c, 
	STATIC_FONT* font, 
	const char* name, 
	float min, 
	float max, 
	float valueUnit,
	bool isRound){

	Min = min;
	Max = max;
	ValueUnit = valueUnit;
	IsRound = isRound;
	RootUi = UI_FACTORY::instanceEmpty();
	RootUi->setIsReleaseDisable(true);
	NameUi = UI_FACTORY::instance(DRAWER::STATIC_FONT::instance(name, font, VECTOR2(0.0f,14.0f), VECTOR2(50.0f,50.0f)));
	//ゲージのUIを作る
	UI* gaugeUi = nullptr;
	{
		DRAWER::IMAGE2D* drawer = DRAWER::IMAGE2D::instance(c->texture("sliderUiGauge"), VECTOR2::zero(), VECTOR2::one());
		gaugeUi = UI_FACTORY::instance(drawer);
		UI_FUNC_ATTACHER::OverlapColorChange(gaugeUi, drawer);
	}
	//スライダーのUIを作る
	UI* sliderUi = nullptr;
	{
		DRAWER::IMAGE2D* drawer = DRAWER::IMAGE2D::instance(c->texture("sliderUiSlider"), VECTOR2::zero(), VECTOR2::one());
		sliderUi = UI_FACTORY::instance(drawer);
	}
	//スライダーUIを作る
	Slider.create(UI_FACTORY::instanceEmpty(),gaugeUi,sliderUi);
	Slider.rootUi()->setPos(VECTOR2(0.0f, 64.0f));
	ValueUi = UI_FACTORY::instance(c->texture("sliderUiValueBack"), VECTOR2(960.0f, 64.0f), VECTOR2::one());
	ValueUiDrawer = DRAWER::STATIC_FONT::instance("",font, VECTOR2(0.0f, 7.0f),VECTOR2(50.0f,50.0f), DRAWER::STATIC_FONT::drawMethodAdjustDraw_Over());
	ValueUiDrawer->setMaxWidth(8);
	ValueUi->addChilds(UI_FACTORY::instance(ValueUiDrawer));
	RootUi->addChilds(NameUi);
	RootUi->addChilds(Slider.rootUi());
	RootUi->addChilds(ValueUi);
	//音
	SoundButton = c->sound("button");
}

void SETTING_SLIDER::create(CONTAINER* c, STATIC_FONT* font, const char* name, SETTING_VALUE_SLIDE* settngSlider, bool isRound){
	create(c, font, name, (float)settngSlider->minValue(), (float)settngSlider->maxValue(), (float)settngSlider->changeAmount(), isRound);
	Slider.setAmount(settngSlider->percentage());
}

void SETTING_SLIDER::update(){
	if (IsRound) {
		ValueUiDrawer->setString(std::to_string((int)value()));
	}
	else {
		ValueUiDrawer->setString(std::to_string(value()));
	}
}

float SETTING_SLIDER::value(){
	float width = Max - Min;
	float value = Slider.amount() * width + Min;
	if (IsRound) {
		return (int)(ValueUnit * (int)(value / ValueUnit));
	}
	else {
		return ValueUnit * (int)(value / ValueUnit);
	}
}
