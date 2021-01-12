#include "../Library/IMAGE_2D.h"
#include "../Library/SOFT_SHADOW.h"
#include "../Library/GRAPHIC.h"
#include "../Library/INDEV.h"
#include "../Library/CONTAINER.h"
#include "../Library/DEBUG_STR.h"
#include "../Library/STATIC_FONT.h"
#include "INPUT_COMMON.h"
#include "SCENE_MANAGER.h"
#include "DRAWERS.h"
#include "DRAWERS_SHADER.h"
#include "DRAWER_STATIC_FONT.h"
#include "DRAWER_IMAGE3D.h"
#include "UI_FACTORY.h"
#include "UI_FUNC_ATTACHER.h"
#include "DRAWER_EMPTY.h"
#include "CAMERA_DEBUG.h"
#include "COLLISION2D_POINT.h"
#include "TERRAIN_AABB.h"
#include "TERRAIN_CYLINDER.h"
#include "TERRAIN_FLOOR.h"
#include "PROCESS_NODE_MANAGER.h"
#include "ENTITY_ROBOT.h"
#include "FADE.h"
#include "DRAWER_ARROW.h"
#include "SCENE_FACTORY.h"
#include "SOUND_MANAGER.h"
#include "SCENE_ROUND.h"

DRAWER::DRAWERS_SHADER* SCENE_ROUND::DebugDrawerImage3d = nullptr;

SCENE_ROUND::SCENE_ROUND(SCENE_MANAGER* sceneManager, const std::string& mapFileName, const std::string& missionFileName,int stageIdx):
	SceneManager(sceneManager) {
	StageIdx = stageIdx;
	create(sceneManager, mapFileName, missionFileName);
}

SCENE_ROUND::~SCENE_ROUND() {
	delete RootUi;
}

void SCENE_ROUND::proc(){
	GRAPHIC* g = GRAPHIC::instance();
	INDEV* indev = INDEV::instance();
	DEBUG_STR* ds = DEBUG_STR::instance();
	COLLISION2D_POINT mousePoint{};
	indev->getState();
	mousePoint.setPos(INPUT_COMMON::MousePosition(indev));
	VECTOR2 MousePos = INPUT_COMMON::MousePosition(indev);
	VECTOR2 pos = VECTOR2((MousePos.x / (g->baseWidth()) - 0.5f) * 2.0f, -(MousePos.y / (g->baseHeight()) - 0.5f) * 2.0f);
	std::visit([](auto state) {state->update();}, State);
	UiManager.update();
	UiAnnotationManager.update();
	ds->set("lineDrawCallCnt:%d", DRAWER::ARROW::drawCallCnt);
	DRAWER::ARROW::drawCallCnt = 0;
	transitionUpdate();

	g->clearTarget(COLOR(0.4f, 0.4f, 0.4f, 1.0f));
	SHADER* shader = nullptr;
	std::visit([](auto state) {state->draw();}, State);
	shader = image2d();
	BEGIN_PATH_
		UiAnnotationManager.draw(shader);
		ds->draw(shader);
		transitionDraw(shader);
		SceneManager->fade()->draw(shader);;
	END_PATH_
		g->present();
	if (SceneManager->fade()->outEndFlag()) {
		(this->*NextSceneMethod)();
	}
}

void SCENE_ROUND::startPlay(){
	screenTransition();
	RoundEdit.onExit();
	RoundPlay.onEnter();
	State = &RoundPlay;
}

void SCENE_ROUND::startEdit(){
	screenTransition();
	RoundPlay.onExit();
	RoundEdit.onEnter();
	State = &RoundEdit;
}

void SCENE_ROUND::uiDraw(){
	SHADER* shader = image2d();
	BEGIN_PATH_
		RootUi->draw(shader);
	END_PATH_
}

void SCENE_ROUND::screenTransition(){
	GRAPHIC* g = GRAPHIC::instance();
	TransitionTextureTimer = 0.0f;
	g->writeBufferRenderTarget(TransitionRenderTargetTexture.rtv());
	TransitionTexturePos = VECTOR2();
}

void SCENE_ROUND::clearRound(){
	if (StageIdx >= 0) {
		SAVE_DATA* saveData = commonData()->saveData();
		saveData->clearStage(StageIdx);
		saveData->openStage(StageIdx + 1);
		saveData->saveDirectory();
	}
}

bool SCENE_ROUND::isExistNextRound() const{
	STAGE_DATA* data = commonData()->stageData();
	return data->isExistRound(StageIdx + 1);
}

void SCENE_ROUND::nextStage(){
	STAGE_DATA* data = commonData()->stageData();
	StageIdx++;
	RoundPlay.setMap(data->mapFileName(StageIdx));
	RoundPlay.setMission(STRING_TREE(STRING_TREE::loadFile(data->missionFileName(StageIdx))));
	RoundPlay.reset();

}

const std::vector<PROCESS_NODE*>& SCENE_ROUND::processNodeList() {
	return RoundEdit.processNodeManager()->processNodeList(); 
}

void SCENE_ROUND::onClickToTitle(){
	NextSceneMethod = &SCENE_ROUND::nextSceneTitle;
	SceneManager->fade()->outTrigger();
	SOUND_MANAGER::instance()->playSound(SoundButton);
}

void SCENE_ROUND::onClickToRoundSelect(){
	NextSceneMethod = &SCENE_ROUND::nextSceneRoundSelect;
	SceneManager->fade()->outTrigger();
	SOUND_MANAGER::instance()->playSound(SoundButton);
}

void SCENE_ROUND::onClickHelpButton(){
	SceneManager->pushNextScene(SCENE_FACTORY::instanceHelp(SceneManager));
	SOUND_MANAGER::instance()->playSound(SoundButton);
}

void SCENE_ROUND::create(SCENE_MANAGER* sceneManager, const std::string& mapFileName, const std::string& missionFileName) {
	DEBUG_STR* ds = DEBUG_STR::instance();
	GRAPHIC* g = GRAPHIC::instance();
	TransitionRenderTargetTexture.init(g->device(), (int)g->width(), (int)g->height());
	SoftShadowShader = softShadow();
	UiAnnotationManager.init(commonData());
	TransitionTextureSpeed = 0.04f;
	//床
	RootUi = UI_FACTORY::instance(new DRAWER::EMPTY);
	RootUi->setIsUnconditionalCollisionHit(true);
	RoundEdit.create(this, RootUi, commonData());
	RoundPlay.create(this, RootUi, commonData(), SoftShadowShader);
	RoundPlay.setMap(mapFileName);
	RoundPlay.setMission(STRING_TREE(STRING_TREE::loadFile(missionFileName)));
	RoundPlay.reset();
	RoundEdit.setModuleScroll(RoundPlay.robotProcessor());
	//UI_MANAGERにルートUIをセット
	UiManager.setRootUi(RootUi);
	//ANNOTATION_MANAGERにルートUIをセット
	UiAnnotationManager.setRootUi(RootUi);
	//ヘルプを表示するボタンUIを作る
	{
		DRAWER::IMAGE2D* drawer = DRAWER::IMAGE2D::instance(c()->texture("helpIcon"), VECTOR2(1857.0f, 72.0f), VECTOR2::one());
		HelpButtonUi = UI_FACTORY::instance(drawer);
		HelpButtonUi->setUpFunc([this]() {onClickHelpButton();});
		UI_FUNC_ATTACHER::OverlapColorChange(HelpButtonUi, drawer);
		RootUi->addChilds(HelpButtonUi);
	}
	MenuUi.create(c(), font());
	MenuUi.listAdd(c(), font(), "タイトルへ", [this]() {onClickToTitle();});
	MenuUi.listAdd(c(), font(), "ステージ選択へ", [this]() {onClickToRoundSelect();});
	RootUi->addChilds(MenuUi.rootUi());
	//音
	SoundButton = c()->sound("button");

	//プレイ画面スタート
	startPlay();
	//フェードイン
	SceneManager->fade()->inTrigger();


}

void SCENE_ROUND::transitionUpdate(){
	GRAPHIC* g = GRAPHIC::instance();
	TransitionTextureTimer += TransitionTextureSpeed;
	const float c1 = 1.70158f;
	const float c3 = c1 + 1.0f;
	TransitionTexturePos.x = (1.0f - pow(1.0f - TransitionTextureTimer, 4.0f)) * g->baseWidth();
}

void SCENE_ROUND::transitionDraw(SHADER* shader){
	if (TransitionTextureTimer < 1.0f) {
		GRAPHIC* g = GRAPHIC::instance();
		shader->setWorld(TEXTURE::getDrawMatrix(g->baseWh(), TransitionTexturePos, VECTOR2::one()));
		shader->setDiffuse(COLOR());
		g->draw(TEXTURE::vertexObj(), TransitionRenderTargetTexture.srv());
	}
}

void SCENE_ROUND::nextSceneTitle(){
	SCENE_MANAGER* sceneManager = SceneManager;
	sceneManager->setNextScene(SCENE_FACTORY::instanceTitle(sceneManager));
}

void SCENE_ROUND::nextSceneRoundSelect(){
	SCENE_MANAGER* sceneManager = SceneManager;
	sceneManager->setNextScene(SCENE_FACTORY::instanceRoundSelect(sceneManager));
}

