#include "../Library/INDEV.h"
#include "../Library/CONTAINER.h"
#include "INPUT_COMMON.h"
#include "SOUND_MANAGER.h"
#include "DRAWER_IMAGE2D.h"
#include "UI_FACTORY.h"
#include "UI_FUNC_ATTACHER.h"
#include "HELP_WINDOW.h"
HELP_WINDOW::HELP_WINDOW() {
}

HELP_WINDOW::~HELP_WINDOW() {
	SAFE_DELETE(RootUi);
}

void HELP_WINDOW::create(CONTAINER* c,STATIC_FONT* font){
	//説明画面用テクスチャを読み込む
	Textures.reserve(64);
	for (int i = 0;i < 32;i++) {
		Textures.push_back(c->texture(("tutorial"s + std::to_string(i)).c_str()));
	}
	Textures.push_back(c->texture("help"));
	//ルートUIを作る
	RootUi = UI_FACTORY::instance(c->texture("helpWindowBack"), VECTOR2(0.0f, 0.0f), VECTOR2::one());
	RootUi->setIsReleaseDisable(true);
	//説明画面の縁のUIを作る
	WindowBackUi = UI_FACTORY::instance(c->texture("helpWindowFrame"), VECTOR2(92.0f, 64.0f), VECTOR2(0.9f, 0.9f));
	//説明画面用のUIを作る
	Drawer = DRAWER::IMAGE2D::instance(Textures[NowPage], VECTOR2(96.0f, 54.0f), VECTOR2(0.9f, 0.9f));
	WindowUi = UI_FACTORY::instance(Drawer);
	WindowBackUi->addChilds(WindowUi);
	//ページ数を表示するUIを作る
	PageUiDrawer = DRAWER::STATIC_FONT::instance("", font, VECTOR2(898.0f,1012.0f), VECTOR2(54,54));
	PageUi = UI_FACTORY::instance(PageUiDrawer);

	//次のページに行くボタンUIを作る
	{
		DRAWER::IMAGE2D* drawer = DRAWER::IMAGE2D::instance(c->texture("nextPageButton"), VECTOR2(1115.0f, 1012.0f), VECTOR2::one());
		NextPageButtonUi = UI_FACTORY::instance(drawer);
		NextPageButtonUi->setPushFunc([this]() {onClickNextPage();});
		UI_FUNC_ATTACHER::OverlapColorChange(NextPageButtonUi, drawer);
	}
	//前のページに行くボタンUIを作る
	{
		DRAWER::IMAGE2D* drawer = DRAWER::IMAGE2D::instance(c->texture("backPageButton"), VECTOR2(740.0f, 1012.0f), VECTOR2::one());
		BackPageButtonUi = UI_FACTORY::instance(drawer);
		BackPageButtonUi->setPushFunc([this]() {onClickBackPage();});
		UI_FUNC_ATTACHER::OverlapColorChange(BackPageButtonUi, drawer);
	}

	RootUi->addChilds(WindowBackUi);
	RootUi->addChilds(PageUi);
	RootUi->addChilds(NextPageButtonUi);
	RootUi->addChilds(BackPageButtonUi);
	RootUi->addChilds(UI_FACTORY::instance(DRAWER::STATIC_FONT::instance("ヘルプ", font, VECTOR2(), VECTOR2(64.0f, 64.0f))));
	//音
	SoundButton = c->sound("button");

	updatePage();
}

void HELP_WINDOW::onClickNextPage(){
	NowPage = min(NowPage + 1, (int)Textures.size() - 1);
	updatePage();
	SOUND_MANAGER::instance()->playSound(SoundButton);
}

void HELP_WINDOW::onClickBackPage(){
	NowPage = max(NowPage - 1, 0);
	updatePage();
	SOUND_MANAGER::instance()->playSound(SoundButton);
}

void HELP_WINDOW::updatePage(){
	Drawer->setTexture(Textures[NowPage]);
	PageUiDrawer->setString(std::to_string(NowPage+1) + "/" + std::to_string(Textures.size()));
}
