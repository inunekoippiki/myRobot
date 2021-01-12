#include "../Library/WINDOW.h"
#include "../Library/INDEV.h"
#include "../Library/DEBUG_STR.h"
#include "../Library/GRAPHIC.h"
#include "../Library/IMAGE_2D.h"
#include "SOUND_MANAGER.h"
#include "UI_FACTORY.h"
#include "UI_FUNC_ATTACHER.h"
#include "SCENE_MANAGER.h"
#include "SCENE_HELP.h"
SCENE_HELP::SCENE_HELP(SCENE_MANAGER* sceneManager) {
	create(sceneManager);
}

SCENE_HELP::~SCENE_HELP() {
	SAFE_DELETE(RootUi);
}

void SCENE_HELP::create(SCENE_MANAGER* sceneManager){
	SceneManager = sceneManager;
	RootUi = UI_FACTORY::instanceEmpty();
	RootUi->setIsUnconditionalCollisionHit(true);
	//UI_MANAGERにルートUIをセット
	UiManager.setRootUi(RootUi);
	HelpWindow.create(c(), font());
	RootUi->addChilds(HelpWindow.rootUi());
	//もとの画面に戻るボタンUIを作る
	{
		DRAWER::IMAGE2D* drawer = DRAWER::IMAGE2D::instance(c()->texture("backIcon"), VECTOR2(1857.0f, 70.0f), VECTOR2::one());
		BackUi = UI_FACTORY::instance(drawer);
		BackUi->setPushFunc([this]() {onClickBack();});
		UI_FUNC_ATTACHER::OverlapColorChange(BackUi, drawer);
	}
	RootUi->addChilds(BackUi);
	//音
	SoundButton = c()->sound("button");
}

void SCENE_HELP::proc(){
	WINDOW* w = WINDOW::instance();
	GRAPHIC* g = GRAPHIC::instance();
	INDEV* indev = INDEV::instance();
	DEBUG_STR* ds = DEBUG_STR::instance();
	indev->getState();
	g->clearTarget(COLOR(0.4f, 0.4f, 0.4f, 1.0f));
	UiManager.update();

	SHADER* shader = image2d();
	g->clearTarget();
	BEGIN_PATH_
		RootUi->draw(shader);
		ds->draw(shader);
	END_PATH_
		g->present();

	if (NextSceneMethod != nullptr) {
		(this->*NextSceneMethod)();
	}
}

void SCENE_HELP::onClickBack(){
	NextSceneMethod = &SCENE_HELP::nextScene;
	SOUND_MANAGER::instance()->playSound(SoundButton);
}

void SCENE_HELP::nextScene(){
	NextSceneMethod = nullptr;
	SceneManager->backScene();
}
