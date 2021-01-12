#include "UI_CHECK.h"
UI_CHECK::UI_CHECK() {
}

UI_CHECK::~UI_CHECK() {
	delete RootUi;
}

void UI_CHECK::create(UI* rootUi, UI* backUi, UI* checkUi){
	RootUi = rootUi;
	BackUi = backUi;
	CheckUi = checkUi;
	RootUi->setIsReleaseDisable(true);
	RootUi->addChilds(BackUi);
	BackUi->addChilds(CheckUi);
	BackUi->setPushFunc([this]() {onClick();});
	CheckUi->setIsCollisionDisable(true);
}

void UI_CHECK::setCheck(bool isCheck){
	IsCheck = isCheck;
	CheckUi->setIsDisable(!IsCheck);
}

void UI_CHECK::onClick(){
	IsCheck = !IsCheck;
	CheckUi->setIsDisable(!IsCheck);
}
