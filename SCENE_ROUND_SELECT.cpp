#include "../Library/IMAGE_2D.h"
#include "../Library/CONTAINER.h"
#include "../Library/WINDOW.h"
#include "../Library/GRAPHIC.h"
#include "../Library/DEBUG_STR.h"
#include "../Library/INDEV.h"
#include "../Library/STRING_TREE.h"
#include "../Library/STATIC_FONT.h"
#include "FADE.h"
#include "UI.h"
#include "UI_FACTORY.h"
#include "UI_FUNC_ATTACHER.h"
#include "DRAWER_DUMMY_IMAGE2D.h"
#include "SCENE_FACTORY.h"
#include "SCENE_MANAGER.h"
#include "STAGE_DATA.h"
#include "SOUND_MANAGER.h"
#include "SCENE_ROUND_SELECT.h"
SCENE_ROUND_SELECT::SCENE_ROUND_SELECT(SCENE_MANAGER* sceneManager) :
	SceneManager(sceneManager),
	StageData(STRING_TREE::loadFile("Assets/stageData/stageData.txt")) {

	RootUi = UI_FACTORY::instanceEmpty();
	SAVE_DATA* saveData = commonData()->saveData();

	UI_SCROLL::NODE_LIST ListUi;
	//列数
	int col = 6;
	for (int i = 0;i < (StageData.childs().size() / col)+1;i++) {
		UI* line = UI_FACTORY::instance(DRAWER::DUMMY_IMAGE2D::instance(VECTOR2(1472.0f, 256.0f), VECTOR2(), VECTOR2::one()));
		float xShift = 256.0f;
		for (int i2 = 0;i2 < col;i2++) {
			int round = i * col + i2;
			if (StageData.childs().size() <= round) { break; }
			UI* node = instanceRoundSelectNode(round);
			node->setPos(VECTOR2(xShift * i2, 0.0f));
			line->addChilds(node);

		}
		ListUi.push_back(line);
	}
	RoundSelectScroll.create(UI_FACTORY::instance(c()->texture("RoundSelectScrollBack"), VECTOR2(), VECTOR2::one()),
		UI_FACTORY::instance(c()->texture("RoundSelectScrollBarBack"), VECTOR2(1760.0f, 128.0f), VECTOR2::one()),
		UI_FACTORY::instance(c()->texture("roundSelectScrollBar"), VECTOR2(), VECTOR2::one()),
		UI_FACTORY::instance(c()->texture("roundSelectScrollNodeBack"), VECTOR2(256, 256), VECTOR2::one()),
		UI_FACTORY::instanceEmpty(),
		UI_FACTORY::instanceEmpty(),
		std::move(ListUi),
		3);
	RootUi->addChilds(RoundSelectScroll.rootUi());
	RootUi->addChilds(UI_FACTORY::instance(DRAWER::STATIC_FONT::instance("ラウンド選択", font(), VECTOR2(), VECTOR2(64.0f, 64.0f))));

	//ダイヤログのUI
	{
		RoundSelectDialogUi.create(DRAWER::IMAGE2D::instance(c()->texture("roundSelectDialogBack"), VECTOR2(384.0f, 256.0f), VECTOR2::one()));
		RoundSelectDialogUi.setIsReleaseDisable(true);
		RoundSelectDialogUi.setIsDisable(true);
		RoundSelectDialogUi.setIsUnconditionalCollisionHit(true);
		RoundSelectDialogStringDrawer = DRAWER::STATIC_FONT::instance("", font(), VECTOR2(64.0f, 32.0f), VECTOR2(96.0f, 96.0f));
		RoundSelectDialogUi.addChilds(UI_FACTORY::instance(RoundSelectDialogStringDrawer));
		{
			DRAWER::STATIC_FONT* drawer = DRAWER::STATIC_FONT::instance("はい", font(), VECTOR2(174.0f, 512.0f), VECTOR2(64.0f, 64.0f));
			UI* yesUi = UI_FACTORY::instance(drawer);
			UI_FUNC_ATTACHER::OverlapColorChange(yesUi, drawer);
			yesUi->setPushFunc([this]() {onClickYes();});
			RoundSelectDialogUi.addChilds(yesUi);
		}
		{
			DRAWER::STATIC_FONT* drawer = DRAWER::STATIC_FONT::instance("いいえ", font(), VECTOR2(736.0f, 512.0f), VECTOR2(64.0f, 64.0f));
			UI* noUi = UI_FACTORY::instance(drawer);
			UI_FUNC_ATTACHER::OverlapColorChange(noUi, drawer);
			noUi->setPushFunc([this]() {onClickNo();});
			RoundSelectDialogUi.addChilds(noUi);
		}
		RootUi->addChilds(&RoundSelectDialogUi);
	}
	//UIマネージャーにルートUIをセット
	UiManager.setRootUi(RootUi);
	//
	UiMenu.create(c(), font());
	UiMenu.listAdd(c(), font(), "タイトルへ",
		[this]() {onClickToTitle(); }
	);
	RootUi->addChilds(UiMenu.rootUi());

	UiManager.setRootUi(RootUi);

	//サウンド情報
	SoundBgm = c()->sound("bgm_title");
	SoundButton = c()->sound("button");
	SOUND_MANAGER::instance()->setNextBgm(SoundBgm);
	SceneManager->fade()->inTrigger();
}

SCENE_ROUND_SELECT::~SCENE_ROUND_SELECT() {
	delete RootUi;
}

void SCENE_ROUND_SELECT::proc(){
	WINDOW* w = WINDOW::instance();
	GRAPHIC* g = GRAPHIC::instance();
	INDEV* indev = INDEV::instance();
	DEBUG_STR* ds = DEBUG_STR::instance();
	indev->getState();
	g->clearTarget(COLOR(0.4f, 0.4f, 0.4f, 1.0f));
	UiManager.update();
	SHADER* shader = image2d();
	BEGIN_PATH_
		RootUi->draw(shader);
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

void SCENE_ROUND_SELECT::nextSceneRound() {
	//スタックに積む
	SCENE_MANAGER* sceneManager = SceneManager;
	STAGE_DATA* data = commonData()->stageData();
	int selectRound = SelectRound;
	//次のステートを設定
	sceneManager->setNextScene(SCENE_FACTORY::instanceRound(sceneManager, data, selectRound));
}

void SCENE_ROUND_SELECT::onClickYes(){
	NextSceneMethod = &SCENE_ROUND_SELECT::nextSceneRound;
	SceneManager->fade()->outTrigger();
	SOUND_MANAGER::instance()->playSound(SoundButton);
}

void SCENE_ROUND_SELECT::onClickNo(){
	RoundSelectDialogUi.setIsDisable(true);
	SOUND_MANAGER::instance()->playSound(SoundButton);
}

void SCENE_ROUND_SELECT::onClickToTitle(){
	NextSceneMethod = &SCENE_ROUND_SELECT::nextSceneTitle;
	SceneManager->fade()->outTrigger();
	SOUND_MANAGER::instance()->playSound(SoundButton);
}

void SCENE_ROUND_SELECT::onClickRound(int round){
	putDialog(round);
	SOUND_MANAGER::instance()->playSound(SoundButton);
}

UI* SCENE_ROUND_SELECT::instanceRoundSelectNode(int round){
	SAVE_DATA* saveData = commonData()->saveData();
	UI* ui = UI_FACTORY::instance(c()->texture("roundSelectIcon"), VECTOR2(), VECTOR2::one());
	ui->setPushFunc([this, round]() {onClickRound(round);});
	DRAWER::STATIC_FONT* drawer = DRAWER::STATIC_FONT::instance(std::to_string(round).c_str(), font(), VECTOR2(), VECTOR2(100,100));
	UI* uiString = UI_FACTORY::instance(drawer);
	uiString->setIsCollisionDisable(true);
	ui->addChilds(uiString);
	if (!saveData->isOpenStage(round)) {
		ui->addChilds(UI_FACTORY::instance(c()->texture("roundSelectUnopenIcon"), VECTOR2(), VECTOR2::one(),COLOR(1.0f,1.0f,1.0f,0.6f)));
		ui->addChilds(UI_FACTORY::instance(DRAWER::STATIC_FONT::instance("未開放", font(), VECTOR2(48.0f, 128.0f),VECTOR2(32.0f,32.0f),COLOR(0.4f,0.4f,0.4f,1.0f))));
	}
	if (saveData->isClearStage(round)) {
		UI* clearUi= UI_FACTORY::instance(c()->texture("checkMark"), VECTOR2(35.0f, 64.0f), VECTOR2::one(), COLOR(1.0f, 1.0f, 1.0f, 1.0f));
		clearUi->setIsCollisionDisable(true);
		ui->addChilds(clearUi);
	}

	UI_FUNC_ATTACHER::OverlapColorChange(ui, drawer, COLOR(1.0f, 0.6f, 0.6f, 1.0f));
	return ui;
}

void SCENE_ROUND_SELECT::putDialog(int round) {
	RoundSelectDialogStringDrawer->setString("ステージ" + std::to_string(round) + "を\n始めますか？");
	RoundSelectDialogUi.setIsDisable(false);
	SelectRound = round;

}
void SCENE_ROUND_SELECT::nextSceneTitle(){
	SCENE_MANAGER* sceneManager = SceneManager;
	sceneManager->setNextScene(SCENE_FACTORY::instanceTitle(sceneManager));
}
