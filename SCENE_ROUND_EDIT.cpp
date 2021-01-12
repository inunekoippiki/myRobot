#include "../Library/common.h"
#include "../Library/IMAGE_2D.h"
#include "../Library/DEBUG_STR.h"
#include "../Library/GRAPHIC.h"
#include "../Library/CONTAINER.h"
#include "COMMON_DATA.h"
#include "UI.h"
#include "UI_FACTORY.h"
#include "UI_FUNC_ATTACHER.h"
#include "DRAWERS_SHADER.h"
#include "PROCESS_NODE_MANAGER.h"
#include "SCENE_ROUND.h"
#include "SOUND_MANAGER.h"
#include "SCENE_ROUND_EDIT.h"
SCENE_ROUND_EDIT::SCENE_ROUND_EDIT(){
}

SCENE_ROUND_EDIT::~SCENE_ROUND_EDIT() {
	SAFE_DELETE(EditToPlaySwitchingButtonUi);
	SAFE_DELETE(ProcessNodeManager);
}

void SCENE_ROUND_EDIT::create(SCENE_ROUND* sceneRound, UI* uiRoot, COMMON_DATA* commonData) {
	SceneRound = sceneRound;
	C = commonData->c();
	Font = commonData->staticFont();
	Image2dShader = commonData->image2dShader();
	DEBUG_STR* ds = DEBUG_STR::instance();
	GRAPHIC* g = GRAPHIC::instance();

	//プロセスノードのマネージャーを生成
	ProcessNodeManager = new PROCESS_NODE_MANAGER(C, Font, Image2dShader);
	UI* processNodeManagerUi = ProcessNodeManager->rootUi();
	processNodeManagerUi->setIsReleaseDisable(true);
	uiRoot->addChilds(processNodeManagerUi);
	{
		DRAWER::IMAGE2D* drawer = DRAWER::IMAGE2D::instance(C->texture("editToPlaySwitchingIcon"), VECTOR2(1792.0f, 184.0f), VECTOR2::one());
		EditToPlaySwitchingButtonUi = UI_FACTORY::instance(drawer);
		EditToPlaySwitchingButtonUi->setPushFunc([this]() {this->SceneRound->startPlay();});
		EditToPlaySwitchingButtonUi->setIsReleaseDisable(true);
		UI_FUNC_ATTACHER::OverlapColorChange(EditToPlaySwitchingButtonUi, drawer, COLOR(1.0f, 0.7f, 0.7f, 1.0f));
		uiRoot->addChilds(EditToPlaySwitchingButtonUi);
	}
	//サウンド情報
	SoundBgm = C->sound("bgm_edit");
}

void SCENE_ROUND_EDIT::update(){
}

void SCENE_ROUND_EDIT::draw(){
	ProcessNodeManager->draw();
	ProcessNodeManager->rootUi()->setIsDisable(true);
	SceneRound->uiDraw();
	ProcessNodeManager->rootUi()->setIsDisable(false);
}

void SCENE_ROUND_EDIT::onEnter(){
	ProcessNodeManager->rootUi()->setIsDisable(false);
	EditToPlaySwitchingButtonUi->setIsDisable(false);
	SOUND_MANAGER::instance()->setNextBgm(SoundBgm);
}

void SCENE_ROUND_EDIT::onExit(){
	ProcessNodeManager->rootUi()->setIsDisable(true);
	EditToPlaySwitchingButtonUi->setIsDisable(true);
}

void SCENE_ROUND_EDIT::setModuleScroll(ROBOT_PROCESSOR* robotProcessor){
	ProcessNodeManager->setModuleScroll(robotProcessor);
}
