#include "../Library/INDEV.h"
#include "COLLISION2D_POINT.h"
#include "UI.h"
#include "INPUT_COMMON.h"
#include "UI_MANAGER.h"

UI_MANAGER::UI_MANAGER(){
}

UI_MANAGER::~UI_MANAGER() {
}

void UI_MANAGER::setRootUi(UI* rootUi){
	RootUi = rootUi;
}


/*
void DeleteUpdate();
UI* OverlapUi();
void setUiManager();

void downFunc();
void upFunc();
void pushFunc();
void dragUpdate() ;
void dragEndFunc();
void overlapIn();
void overlapUpdate();
void overlapOut();
void idelUpdate() ;
*/

void UI_MANAGER::update() {
	INDEV* indev = INDEV::instance();
	COLLISION2D_POINT mousePoint;
	mousePoint.setPos(INPUT_COMMON::MousePosition(indev));

	RootUi->DeleteUpdate();
	RootUi->OverlapUi(&mousePoint, OverlapUi);
	//funcが実行されるごとにそのuiごと消える可能性があるため毎回nullチェックが入ってる
	if (OverlapUi != nullptr) {
		OverlapUi->setUiManager(this);
		OverlapUi->overlapUpdate();
	}
	if (OverlapUi != ChoiceUi) {
		if (OverlapUi != nullptr) {
			OverlapUi->overlapIn();
		}
		if (ChoiceUi != nullptr) {
			ChoiceUi->overlapOut();
		}
		if (ChoiceUi != nullptr) {
			ChoiceUi->setUiManager(nullptr);
		}
		ChoiceUi = OverlapUi;
		if (ChoiceUi != nullptr) { 
			ChoiceUi->setUiManager(this);
		}
	}
	if (indev->isTrigger(MOUSE_LBUTTON)) {
		if (OverlapUi != nullptr) {
			OverlapUi->downFunc();
		}
		if (DownUi != nullptr) {
			DownUi->setUiManager(nullptr);
		}
		DownUi = OverlapUi;
		if (DownUi != nullptr) {
			DownUi->setUiManager(this);
		}
	}
	if (DownUi != nullptr) {
		DownUi->dragUpdate();
	}
	if (indev->isUp(MOUSE_LBUTTON)) {
		if (OverlapUi != nullptr) {
			if (DownUi == OverlapUi) {
				OverlapUi->pushFunc();
			}
			if (OverlapUi != nullptr) {
				OverlapUi->upFunc();
			}
		}
		if (DownUi != nullptr) {
			DownUi->dragEndFunc();
		}
		if (DownUi != nullptr) {
			DownUi->setUiManager(nullptr);
		}
		DownUi = nullptr;
	}
	if (OverlapUi != nullptr) {
		OverlapUi->setUiManager(nullptr);
	}
	OverlapUi = nullptr;
}

void UI_MANAGER::uiDelete(UI* ui){
	if (DownUi == ui) { DownUi = nullptr; }
	if (ChoiceUi == ui) { ChoiceUi = nullptr; }
	if (OverlapUi == ui) { OverlapUi = nullptr; }
}
