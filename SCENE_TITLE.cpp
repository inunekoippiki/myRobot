#include "../Library/IMAGE_2D.h"
#include "../Library/SOFT_SHADOW.h"
#include "../Library/WINDOW.h"
#include "../Library/GRAPHIC.h"
#include "../Library/INDEV.h"
#include "../Library/CONTAINER.h"
#include "../Library/DEBUG_STR.h"
#include "../Library/STATIC_FONT.h"
#include "../Library/TREE.h"
#include "../Library/collisionUtil.h"
#include "createAssets.h"
#include "INPUT_COMMON.h"
#include "FADE.h"
#include "UI_FACTORY.h"
#include "UI_FUNC_ATTACHER.h"
#include "COLLISION2D_POINT.h"
#include "DRAWERS.h"
#include "DRAWER_BATCH.h"
#include "DRAWER_STATIC_FONT.h"
#include "MODEL_ROBOT.h"
#include "SCENE_MANAGER.h"
#include "SCENE_FACTORY.h"
#include "SOUND_MANAGER.h"
#include "SCENE_TITLE.h"
SCENE_TITLE::SCENE_TITLE(SCENE_MANAGER* sceneManager) :
	SceneManager(sceneManager){
	GRAPHIC* g = GRAPHIC::instance();
	//UIを作る
	{
		TEXTURE* texture = c()->texture("titleName");
		UiTitleName.create(DRAWER::IMAGE2D::instance(texture, VECTOR2(g->centerX() - texture->width() * 0.5f, 128.0f), VECTOR2::one()));
		UiTitleName.setIsReleaseDisable(true);
	}
	float offsetX = 550;
	int fontSize = 54;
	int interval = 80;

	createSelectUi("ラウンド選択", &UiRoundButton, VECTOR2(g->centerX() - STATIC_FONT::stringWidth("ラウンド選択", fontSize) * 0.5f, offsetX + interval * 0), VECTOR2(fontSize, fontSize));
	UiRoundButton.setPushFunc([this]() {onClickRoundSelect();});

	createSelectUi("設定", &UiOptionButton, VECTOR2(g->centerX() - STATIC_FONT::stringWidth("設定", fontSize) * 0.5f, offsetX + interval * 1), VECTOR2(fontSize, fontSize));
	UiOptionButton.setPushFunc([this]() {onClickSetting();});

	createSelectUi("終了", &UiExitButton, VECTOR2(g->centerX() - STATIC_FONT::stringWidth("終了", fontSize) * 0.5f, offsetX + interval * 2), VECTOR2(fontSize, fontSize));
	UiExitButton.setPushFunc([this]() {onClickExit();});

	UiRoot = UI_FACTORY::instanceEmpty();
	UiRoot->addChilds(&UiTitleName);
	UiRoot->addChilds(&UiRoundButton);
	UiRoot->addChilds(&UiOptionButton);
	UiRoot->addChilds(&UiExitButton);
	UiManager.setRootUi(UiRoot);

	Light.init(STRING_TREE(STRING_TREE::loadFile("Assets/ROUND/lightData.txt")));
	Camera.create(STRING_TREE(STRING_TREE::loadFile("Assets/ROUND/cameraData.txt")));
	Camera.setPos(VECTOR3(0.0f, 7.0f, -9.0f));
	Camera.setLookAt(VECTOR3(0.0f, 0.0f, 0.0f));
	Drawers3d.setShader(softShadow());
	Floor = new DRAWER::BATCH();
	Floor->setBatch(c()->batch("Floor"));
	Floor->setScale(VECTOR3(100.0f, 1.0f, 100.0f));
	Drawers3d.add(Floor);
	Robot.create(c(), &Drawers3d, &Camera);



	SceneManager->fade()->inTrigger();

	SoundBgm = c()->sound("bgm_title");
	SoundButton = c()->sound("button");
	SOUND_MANAGER::instance()->setNextBgm(SoundBgm);
}

SCENE_TITLE::~SCENE_TITLE(){
	Floor->Delete();
	SAFE_DELETE(UiRoot);
}

void SCENE_TITLE::proc(){
	WINDOW* w = WINDOW::instance();
	GRAPHIC* g = GRAPHIC::instance();
	INDEV* indev = INDEV::instance();
	DEBUG_STR* ds = DEBUG_STR::instance();
	indev->getState();

	Robot.update();

	Camera.shaderUpdate(softShadow());
	COLLISION2D_POINT mousePoint{};
	mousePoint.setPos(INPUT_COMMON::MousePosition(indev));
	ds->set("mouseX:%f mouseY:%f", mousePoint.pos().x, mousePoint.pos().y);
	ds->set("windowBase w:%d h:%d", w->baseWidth(), w->baseHeight());
	ds->set("windowClient w:%ud h:%ud", w->clientWidth(), w->clientHeight());
	ds->set("graphicBase w:%f h:%f", g->baseWidth(), g->baseHeight());
	ds->set("graphic w:%ud h:%ud", g->width(), g->height());
	g->clearTarget(COLOR(0.4f, 0.4f, 0.4f, 1.0f));
	UiManager.update();
#if( _DEBUG )
	if (indev->isTrigger(KEY_E)) {
		SceneManager->fade()->outTrigger();
		this->NextSceneMethod = &SCENE_TITLE::nextSceneMapEdit;
	}
#endif
	Light.shaderUpdate(softShadow());
	Drawers3d.draw();
	g->setDepthWritingDisable();
	g->outLineDraw(softShadow()->shaderResourceViewDepth(), softShadow()->shaderResourceViewNormal(), 0.00001f);
	g->setDepthWritingEnable();
	g->fogDraw(softShadow()->shaderResourceViewDepth(), COLOR(0.7f, 0.8f, 1.0f, 1.0f), 0.0005f);

	SHADER* shader = image2d();
	BEGIN_PATH_
		UiRoot->draw(shader);
	END_PATH_
	BEGIN_PATH_
		ds->draw(shader);
		SceneManager->fade()->draw(shader);
	END_PATH_
	g->present();
	if (SceneManager->fade()->outEndFlag()) {
		(this->*NextSceneMethod)();
	}
}

void SCENE_TITLE::nextSceneRound(){
	SceneManager->setNextScene(SCENE_FACTORY::instanceRoundSelect(SceneManager));
}

void SCENE_TITLE::nextSceneSetting(){
	SceneManager->setNextScene(SCENE_FACTORY::instanceRoundSetting(SceneManager));
}

void SCENE_TITLE::nextSceneTutorial(){
	SceneManager->setNextScene(SCENE_FACTORY::instanceRoundSelect(SceneManager));
}

void SCENE_TITLE::nextSceneMapEdit(){
	SceneManager->setNextScene(SCENE_FACTORY::instanceMapEdit(SceneManager));
}

void SCENE_TITLE::onClickRoundSelect(){
	NextSceneMethod = &SCENE_TITLE::nextSceneRound;
	SceneManager->fade()->outTrigger();
	SOUND_MANAGER::instance()->playSound(SoundButton);
}

void SCENE_TITLE::onClickSetting(){
	NextSceneMethod = &SCENE_TITLE::nextSceneSetting;
	SceneManager->fade()->outTrigger();
	SOUND_MANAGER::instance()->playSound(SoundButton);
}

void SCENE_TITLE::onClickExit(){
	SendMessage(WINDOW::instance()->hostHandle(), WM_CLOSE, 0, 0);
	SOUND_MANAGER::instance()->playSound(SoundButton);
}


void SCENE_TITLE::createSelectUi(const char* s,UI* ui, const VECTOR2 pos, const VECTOR2& scale)const{
	COLOR defaultColor = COLOR(0.3f, 0.3f, 0.3f, 1.0f);
	DRAWER::STATIC_FONT* drawer = DRAWER::STATIC_FONT::instance(s, font(), pos, scale, DRAWER::STATIC_FONT::drawMethodDefault(), defaultColor);
	ui->create(drawer);
	ui->setIsReleaseDisable(true);
	UI_FUNC_ATTACHER::OverlapColorChange(ui, drawer, defaultColor, COLOR(1.0f, 0.0f, 0.0f, 1.0f));
}
