#include <random>
#include <fstream>
#include <memory>
#include "../Library/STRING_TREE.h"
#include "../Library/DEBUG_STR.h"
#include "../Library/GRAPHIC.h"
#include "../Library/CONTAINER.h"
#include "../Library/IMAGE_2D.h"
#include "../Library/SOFT_SHADOW.h"
#include "../Library/OUT_LINE_SHADER.h"
#include "UI.h"
#include "UI_FACTORY.h"
#include "UI_FUNC_ATTACHER.h"
#include "DRAWER_EMPTY.h"
#include "DRAWER_STATIC_FONT.h"
#include "DRAWER_IMAGE3D.h"
#include "DRAWERS_SHADER.h"
#include "TERRAIN_FLOOR.h"
#include "ENTITY_ROBOT.h"
#include "ENTITY_GOAL.h"
#include "ENTITY_ITEM.h"
#include "SCENE_ROUND.h"
#include "SCENE_MANAGER.h"
#include "SOUND_MANAGER.h"
#include "SCENE_ROUND_PLAY.h"
SCENE_ROUND_PLAY::SCENE_ROUND_PLAY():
	Mt19937(std::random_device()()){
	Light.init(STRING_TREE(STRING_TREE::loadFile("Assets/ROUND/lightData.txt")));
}

SCENE_ROUND_PLAY::~SCENE_ROUND_PLAY() {
	delete OutLineShader;
	delete Robot;
	delete Camera;
	SAFE_DELETE(MapData);
}

void SCENE_ROUND_PLAY::create(
	SCENE_ROUND* sceneRound,
	UI* uiRoot, 
	COMMON_DATA* commonData,
	SOFT_SHADOW* softShadowShader) {

	SceneRound = sceneRound;
	CommonData = commonData;
	C = commonData->c();
	Font = commonData->staticFont();
	Image2dShader = commonData->image2dShader();
	SoftShadowShader = softShadowShader;
	OutLineShader = new OUT_LINE_SHADER(2048, 2048);
	DEBUG_STR* ds = DEBUG_STR::instance();
	GRAPHIC* g = GRAPHIC::instance();
	EntityManager.create(C, SoftShadowShader, Image2dShader,&RoundMission);
	SCENE_ROUND::DebugDrawerImage3d = EntityManager.drawers2d();
	Camera = new CAMERA_DEBUG(STRING_TREE(STRING_TREE::loadFile("Assets/ROUND/cameraData.txt")));
	Camera->setRotateSpeed(commonData->setting()->aimSensitivity()->value()*0.01f);
	Robot = EntityManager.entityFactory()->instanceEntityRobot(&RobotProcessor,VECTOR3(0.0f, 0.5f, 0.0f));
	{
		DRAWER::IMAGE2D* drawer = DRAWER::IMAGE2D::instance(C->texture("editToPlaySwitchingIcon"), VECTOR2(1792.0f, 184.0f), VECTOR2::one());
		PlayToEditSwitchingButtonUi = UI_FACTORY::instance(drawer);
		PlayToEditSwitchingButtonUi->setPushFunc([this]() {onClickToEdit();});
		PlayToEditSwitchingButtonUi->setIsDisable(true);
		UI_FUNC_ATTACHER::OverlapColorChange(PlayToEditSwitchingButtonUi, drawer, COLOR(1.0f, 0.7f, 0.7f, 1.0f));
		uiRoot->addChilds(PlayToEditSwitchingButtonUi);
	}
	{
		WarningIconUi = UI_FACTORY::instance(C->texture("warningIcon"), VECTOR2(1760, 153), VECTOR2::one());
		WarningIconUi->setIsCollisionDisable(true);
		WarningIconUi->setIsDisable(true);
		uiRoot->addChilds(WarningIconUi);
	}
	{
		PlayButtonUi = UI_FACTORY::instance(C->texture("playButtonBack"), VECTOR2(768.0f, 896.0f), VECTOR2::one());
		DRAWER::STATIC_FONT* drawer = DRAWER::STATIC_FONT::instance("スタート", Font, VECTOR2(0.0f, 0.0f), VECTOR2(128.0f, 128.0f), DRAWER::STATIC_FONT::drawMethodAdjustDraw_Over());
		drawer->setMaxWidth(6);
		UI* stringUi = UI_FACTORY::instance(drawer);
		stringUi->setIsCollisionDisable(true);
		PlayButtonUi->addChilds(stringUi);
		PlayButtonUi->setPushFunc([this]() {onClickPlayStart();});
		UI_FUNC_ATTACHER::OverlapColorChange(PlayButtonUi, drawer);
		PlayButtonUi->setIsDisable(true);
		uiRoot->addChilds(PlayButtonUi);
	}
	{
		DRAWER::IMAGE2D* drawer = DRAWER::IMAGE2D::instance(C->texture("PlayStopIcon"), VECTOR2(1792.0f, 184.0f), VECTOR2::one());
		PlayStopButtonUi = UI_FACTORY::instance(drawer);
		PlayStopButtonUi->setPushFunc([this]() {onClickPlayStop();});
		PlayStopButtonUi->setIsDisable(true);
		UI_FUNC_ATTACHER::OverlapColorChange(PlayStopButtonUi, drawer, COLOR(1.0f, 0.7f, 0.7f, 1.0f));
		uiRoot->addChilds(PlayStopButtonUi);
	} 
	{
		CameraHelpUi = UI_FACTORY::instance(C->texture("cameraHelp"), VECTOR2(134.0f, 902.0f), VECTOR2::one());
		CameraHelpUi->setIsCollisionDisable(true);
		uiRoot->addChilds(CameraHelpUi);
	}
	{
		DRAWER::IMAGE2D* drawer = DRAWER::IMAGE2D::instance(C->texture("cameraResetButton"), VECTOR2(37.0f, 1011.0f), VECTOR2::one());
		CameraResetButtonUi = UI_FACTORY::instance(drawer);
		CameraResetButtonUi->setPushFunc([this]() {onClickCameraReset();});
		uiRoot->addChilds(CameraResetButtonUi);
		UI_FUNC_ATTACHER::OverlapColorChange(CameraResetButtonUi, drawer);
	}
	{	
		ClearIcon.create(C);
		uiRoot->addChilds(ClearIcon.rootUi());
	} 
	{
		NextStageButtonUi.create(DRAWER::IMAGE2D::instance(C->texture("nextStageBack"), VECTOR2(1322.0f,897.0f), VECTOR2::one()));
		DRAWER::STATIC_FONT* drawer = DRAWER::STATIC_FONT::instance("次のステージへ", Font, VECTOR2(32.0f, 32.0f), VECTOR2(96.0f, 96.0f), DRAWER::STATIC_FONT::drawMethodAdjustDraw_Over());
		drawer->setMaxWidth(6);
		UI* stringUi = UI_FACTORY::instance(drawer);
		stringUi->setIsCollisionDisable(true);
		NextStageButtonUi.addChilds(stringUi);
		NextStageButtonUi.setPushFunc([this]() {onClickNextStage();});
		UI_FUNC_ATTACHER::OverlapColorChange(&NextStageButtonUi, drawer);
		NextStageButtonUi.setIsReleaseDisable(true);
		NextStageButtonUi.setIsDisable(true);
		uiRoot->addChilds(&NextStageButtonUi);
	}
	{
		FailedIcon.create(C);
		uiRoot->addChilds(FailedIcon.rootUi());
	}
	{
		ErrorPopup.create(C, Font,SceneRound);
		uiRoot->addChilds(ErrorPopup.rootUi());
	}
	AxisDisp.create(C);
	AxisDisp.setPos(VECTOR2(70.0f, 980.0f));
	//サウンド情報
	SoundBgmPlay = C->sound("bgm_play");
	SoundBgmStart = C->sound("bgm_start");
	SoundBgmEnd = C->sound("muon");
	SoundClear = C->sound("clear");
	SoundButton = C->sound("button");
}

void SCENE_ROUND_PLAY::setMap(const std::string& mapFileName){
	if (MapData != nullptr) {
		delete MapData;
	}
	MapData = new STRING_TREE(STRING_TREE::loadFile(mapFileName));
}

void SCENE_ROUND_PLAY::setMission(const STRING_TREE& missionData){
	RoundMission.create(missionData, Font);
}

void SCENE_ROUND_PLAY::update(){
	DEBUG_STR* ds = DEBUG_STR::instance();
	Timer++;

	ds->set("RecursionDepth:%d" ,RobotProcessor.jumpBackPointStack().size());
	Camera->update();
	SOUND_MANAGER::instance()->setPlayerPos(Camera->cameraPos());
	EntityManager.updateProjView(Camera->proj(), Camera->view());
	DRAWER::IMAGE3D::setProjView(Camera->projView());
	switch (State){
	case SCENE_ROUND_PLAY::STATE::STOP:
		Robot->update();
		EntityManager.update();
		break;
	case SCENE_ROUND_PLAY::STATE::PLAY:
		Robot->activeUpdate();
		Robot->update();
		EntityManager.activeUpdate();
		RoundMission.update();
		if (RoundMission.isClear()) {
			clear();
		}
		if (RoundMission.isFail()) {
			failed();
		}

		break;
	case SCENE_ROUND_PLAY::STATE::CLEAR:
		clearUpdate();
		break;
	case SCENE_ROUND_PLAY::STATE::FAILED:
		failedUpdate();
		break;
	default:
		break;
	}
	debugVariableListUpdate();
	AxisDisp.update(Camera->rotateMatrix());
}

void SCENE_ROUND_PLAY::draw(){
	GRAPHIC* g = GRAPHIC::instance();
	shaderSet(SoftShadowShader);
	shaderSet(OutLineShader);
	SHADER* shader = SoftShadowShader;
	Light.shaderUpdate(shader);
	EntityManager.draw3d();
	g->setDepthWritingDisable();
	g->outLineDraw(SoftShadowShader->shaderResourceViewDepth(), SoftShadowShader->shaderResourceViewNormal(),0.00001f);
	g->setDepthWritingEnable();
	g->fogDraw(SoftShadowShader->shaderResourceViewDepth(),COLOR(0.7f,0.8f,1.0f,1.0f), 0.0005f);
	EntityManager.drawEffect();
	EntityManager.draw2d();

	SceneRound->uiDraw();
	shader = Image2dShader;
	BEGIN_PATH_
		RoundMission.draw(shader);
		AxisDisp.draw(shader);
	END_PATH_
	//BEGIN_PATH_
	//	SoftShadowShader->drawMap(shader);
	//END_PATH_
}
void SCENE_ROUND_PLAY::onEnter(){
	PlayToEditSwitchingButtonUi->setIsDisable(false);
	PlayButtonUi->setIsDisable(false);
	CameraHelpUi->setIsDisable(false);
	CameraResetButtonUi->setIsDisable(false);

	SOUND_MANAGER::instance()->setNextBgm(SoundBgmPlay);
}
void SCENE_ROUND_PLAY::onExit(){
	PlayToEditSwitchingButtonUi->setIsDisable(true);
	WarningIconUi->setIsDisable(true);
	PlayButtonUi->setIsDisable(true);
	PlayStopButtonUi->setIsDisable(true);
	CameraHelpUi->setIsDisable(true);
	CameraResetButtonUi->setIsDisable(true);
}

void SCENE_ROUND_PLAY::play() {
	RobotProcessor.startCompile(SceneRound->processNodeList());
	if (RobotProcessor.robotCompiler()->error()->isNotError()) {
		RobotProcessor.stepStart();
		PlayStopButtonUi->setIsDisable(false);
		PlayButtonUi->setIsDisable(true);
		State = STATE::PLAY;
		SOUND_MANAGER::instance()->setNextBgm(SoundBgmStart);
	}
	else {
		errorPopupDisp();
		WarningIconUi->setIsDisable(false);
	}
}

void SCENE_ROUND_PLAY::reset() {
	State = STATE::STOP;
	EntityManager.allDeleteEntitys();
	EntityManager.loadEntitys(MapData->atw("root")->atw("entitys"));
	EntityManager.deleteUpdate();
	Robot->reset();
	Robot->setPos(VECTOR3(0.0f, 0.5f, 0.0f));
	PlayButtonUi->setIsDisable(false);
	PlayStopButtonUi->setIsDisable(true);
	RobotProcessor.ProcessEnd();
	RoundMission.reset();
	ClearIcon.exit();
	FailedIcon.exit();
	NextStageButtonUi.setIsDisable(true);
	SOUND_MANAGER::instance()->setNextBgm(SoundBgmPlay);
}

void SCENE_ROUND_PLAY::clear(){
	State = STATE::CLEAR;
	ClearIcon.start();
	if (SceneRound->isExistNextRound()) {
		NextStageButtonUi.setIsDisable(false);
	}
	SceneRound->clearRound();
	SOUND_MANAGER::instance()->playSound(SoundClear);
	SOUND_MANAGER::instance()->setNextBgm(SoundBgmEnd);
}

void SCENE_ROUND_PLAY::failed(){
	State = STATE::FAILED;
	FailedIcon.start();
	SOUND_MANAGER::instance()->setNextBgm(SoundBgmEnd);
}

void SCENE_ROUND_PLAY::errorPopupDisp(){
	ErrorPopup.errorPopupDisp(RobotProcessor.robotCompiler()->error()->errorList());
}

void SCENE_ROUND_PLAY::clearUpdate(){
	EntityManager.update();
	Robot->update();
	ClearIcon.update();
}

void SCENE_ROUND_PLAY::failedUpdate(){
	EntityManager.update();
	Robot->update();
	FailedIcon.update();
}

void SCENE_ROUND_PLAY::nextRound(){
	SceneRound->nextStage();
}

void SCENE_ROUND_PLAY::shaderSet(SHADER* shader){
	Light.shaderUpdate(shader);
	Camera->shaderUpdate(shader);
}


void SCENE_ROUND_PLAY::debugVariableListUpdate() {
	for (auto& i : DebugVariableList) {
		i->Delete();
	}
	DebugVariableList.clear();
	if (CommonData->setting()->debugDisp()->isCheck()) {
		float drawerPosY = 0.0f;
		for (auto& i : RobotProcessor.variableList()) {
			if (i.first.empty())continue;
			if (strchr("-+0123456789", i.first.front()))continue;
			DRAWER::STATIC_FONT* drawer = new DRAWER::STATIC_FONT;
			drawer->create((i.first + ":" + std::to_string(i.second)).c_str(), Font);
			drawer->setPos(VECTOR2(0.0f, drawerPosY));
			drawer->setScale(VECTOR2(32.0f, 32.0f));
			drawer->setColor(COLOR(1.0f, 0.2f, 0.2f, 1.0f));
			drawerPosY += 32.0f;
			DebugVariableList.push_back(drawer);
			EntityManager.drawers2d()->add(drawer);
		}
	}
}

void SCENE_ROUND_PLAY::onClickPlayStart(){
	play();
}

void SCENE_ROUND_PLAY::onClickNextStage(){
	nextRound();
	SOUND_MANAGER::instance()->playSound(SoundButton);
}

void SCENE_ROUND_PLAY::onClickCameraReset(){
	Camera->reset();
}

void SCENE_ROUND_PLAY::onClickPlayStop(){
	reset();
}

void SCENE_ROUND_PLAY::onClickToEdit(){
	SceneRound->startEdit();
}
