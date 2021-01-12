#include "../Library/GRAPHIC.h"
#include "../Library/CONTAINER.h"
#include "SOUND_MANAGER.h"
#include "DRAWER_STATIC_FONT.h"
#include "UI_FACTORY.h"
#include "UI_FUNC_ATTACHER.h"
#include "ROBOT_COMPILER_ERROR.h"
#include "SCENE_ROUND.h"
#include "ERROR_POPUP.h"
ERROR_POPUP::ERROR_POPUP() {
}

ERROR_POPUP::~ERROR_POPUP() {
	delete ErrorPopup;
}

void ERROR_POPUP::create(CONTAINER* c, STATIC_FONT* font, SCENE_ROUND* sceneRound){
	C = c;
	Font = font;
	SceneRound = sceneRound;
	ErrorPopup =UI_FACTORY::instanceEmpty();
	ErrorPopup->setIsReleaseDisable(true);

	SoundError = c->sound("error");
}

void ERROR_POPUP::errorPopupDisp(ERROR_TYPE errorList){
	struct VISITOR {
		void operator()(ROBOT_COMPILER_ERROR::NONE_OUTPUT_MODULE_NODE error) {
		};
		void operator()(ROBOT_COMPILER_ERROR::NONE_INPUT_MODULE_NODE error) {
		};
		void operator()(ROBOT_COMPILER_ERROR::NONE_START_NODE error) {
			ErrorPopup->errorPopupDisp("！開始ノードがない。", "開始ノードは必ず1つ\n存在しなければなりません");
		};
		void operator()(ROBOT_COMPILER_ERROR::DUPLECATE_START_NODE error) {
			ErrorPopup->errorPopupDisp("！開始ノードが複数ある。", "開始ノードは一つしか\n存在できません");
		};
		void operator()(ROBOT_COMPILER_ERROR::NONE_JUMP_POINT error) {
		};
		void operator()(ROBOT_COMPILER_ERROR::DUPLECATE_JUMP_POINT error) {
		};
		ERROR_POPUP* ErrorPopup = nullptr;
	};
	for (auto& i : *errorList) {
		std::visit(VISITOR{ this }, i);
	}
}

void ERROR_POPUP::errorPopupDisp(const char* s, const char* details) {
	GRAPHIC* g = GRAPHIC::instance();
	TEXTURE* uiTexture = C->texture("errorPopupBack");
	UI* ui = UI_FACTORY::instance(uiTexture, g->baseWh() * 0.5f - uiTexture->wh() * 0.5f, VECTOR2::one());

	UI* uiString = UI_FACTORY::instance(DRAWER::STATIC_FONT::instance(s, Font, VECTOR2(64.0f, 64.0f), VECTOR2(64.0f, 64.0f), COLOR(1.0f, 0.0f, 0.0f, 1.0f)));
	UI* uiDetails = UI_FACTORY::instance(DRAWER::STATIC_FONT::instance(details, Font, VECTOR2(64.0f, 128.0f), VECTOR2(50.0f, 50.0f)));
	DRAWER::IMAGE2D* helpDrawer = DRAWER::IMAGE2D::instance(C->texture("helpIcon"), uiTexture->wh() * VECTOR2(1.0f, 0.0f) + C->texture("helpIcon")->wh() * VECTOR2(-1.0f, 0.0f), VECTOR2::one());
	UI* uiHelpButton = UI_FACTORY::instance(helpDrawer);
	uiHelpButton->setPushFunc([this]() {SceneRound->onClickHelpButton();});
	UI_FUNC_ATTACHER::OverlapColorChange(uiHelpButton, helpDrawer);
	ui->setIsUnconditionalCollisionHit(true);
	ui->addChilds(uiString);
	ui->addChilds(uiDetails);
	ui->addChilds(uiHelpButton);

	//クリックすると消える
	ui->setPushFunc([this, ui]() {onClick(ui);});
	ErrorPopup->addChilds(ui);
	ErrorPopupFront = ui;
	SOUND_MANAGER::instance()->playSound(SoundError);
}

void ERROR_POPUP::onClick(UI* ui) {
	ErrorPopupFront = ui->parent();
	ErrorPopupFront->removeChilds(ui);
	SAFE_DELETE(ui);
}
