#include "UI_FACTORY.h"
#include "UI_FUNC_ATTACHER.h"
#include "DRAWER_STATIC_FONT.h"
#include "SOUND_MANAGER.h"
#include "UI_MENU.h"
UI_MENU::UI_MENU() {
}

UI_MENU::~UI_MENU() {
	SAFE_DELETE(RootUi);
}

void UI_MENU::create(CONTAINER* c, STATIC_FONT* font){
	RootUi = UI_FACTORY::instanceEmpty();
	RootUi->setIsReleaseDisable(true);
	DRAWER::IMAGE2D* drawer = DRAWER::IMAGE2D::instance(c->texture("menuIcon"), VECTOR2(1857.0f, 3.0f), VECTOR2::one());
	MenuButtonUi = UI_FACTORY::instance(drawer);
	MenuButtonUi->setPushFunc([this]() {onClickMenu();});
	UI_FUNC_ATTACHER::OverlapColorChange(MenuButtonUi, drawer);
	MenuBerUi = UI_FACTORY::instanceEmpty();
	MenuBerUi->setPos(VECTOR2(-320.0f+32.0f, 32.0f));
	MenuButtonUi->addChilds(MenuBerUi);
	MenuBerUi->setIsUnconditionalCollisionHit(true);
	MenuBerUi->setIsDisable(true);
	MenuBerUi->setPushFunc([this]() {onClickBack();});
	RootUi->addChilds(MenuButtonUi);
	//‰¹
	SoundButton = c->sound("button");
}

void UI_MENU::listAdd(CONTAINER* c, STATIC_FONT* font, const char* name,const std::function<void()>& pushFunc){
	//F‚ÍŒðŒÝ‚É­‚µ•Ï‚¦‚é
	COLOR color = (List.size() % 2) ? COLOR(1.0f, 1.0f, 1.0f, 1.0f) : COLOR(0.8f, 0.8f, 0.8f, 1.0f);
	UI* backUi = UI_FACTORY::instance(c->texture("menuItemBack"), VECTOR2(0.0f, 64.0f* List.size()), VECTOR2::one(), color);
	backUi->setPushFunc(pushFunc);
	DRAWER::STATIC_FONT* drawer = DRAWER::STATIC_FONT::instance(name, font, VECTOR2(), VECTOR2(64.0f, 64.0f), DRAWER::STATIC_FONT::drawMethodAdjustDraw_Over());
	drawer->setMaxWidth(10);
	UI* stringUi = UI_FACTORY::instance(drawer);
	stringUi->setIsCollisionDisable(true);
	backUi->addChilds(stringUi);
	UI_FUNC_ATTACHER::OverlapAlphaColorChange(backUi, drawer);
	MenuBerUi->addChilds(backUi);

	List.push_back(backUi);
}

void UI_MENU::onClickMenu(){
	MenuBerUi->setIsDisable(false);
	SOUND_MANAGER::instance()->playSound(SoundButton);
}

void UI_MENU::onClickBack(){
	MenuBerUi->setIsDisable(true);
}
