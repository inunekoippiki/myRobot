#include "UI_FACTORY.h"
#include "UI_FUNC_ATTACHER.h"
#include "DRAWER_STATIC_FONT.h"
#include "SETTING_CHECK.h"
SETTING_CHECK::SETTING_CHECK() {
}

SETTING_CHECK::~SETTING_CHECK() {
	delete RootUi;
}

void SETTING_CHECK::create(CONTAINER* c, STATIC_FONT* font, const char* name){
	RootUi = UI_FACTORY::instanceEmpty();
	RootUi->setIsReleaseDisable(true);
	NameUi = UI_FACTORY::instance(DRAWER::STATIC_FONT::instance(name, font, VECTOR2(0.0f, 14.0f), VECTOR2(50.0f, 50.0f)));
	UI* checkBoxUi = nullptr;
	{
		DRAWER::IMAGE2D* drawer = DRAWER::IMAGE2D::instance(c->texture("CheckBoxUiBack"), VECTOR2(), VECTOR2::one());
		checkBoxUi = UI_FACTORY::instance(drawer);
		UI_FUNC_ATTACHER::OverlapColorChange(checkBoxUi, drawer);
	}
	Check.create(UI_FACTORY::instanceEmpty(),
		checkBoxUi,
		UI_FACTORY::instance(c->texture("CheckBoxUiCheck"), VECTOR2(), VECTOR2::one()));
	Check.rootUi()->setPos(VECTOR2(0.0f, 64.0f));
	RootUi->addChilds(NameUi);
	RootUi->addChilds(Check.rootUi());
	//‰¹
	SoundButton = c->sound("button");
}

bool SETTING_CHECK::isCheck(){
	return Check.isCheck();
}

void SETTING_CHECK::setCheck(bool isCheck){
	Check.setCheck(isCheck);
}
