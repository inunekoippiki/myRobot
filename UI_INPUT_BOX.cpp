#include "../Library/CONTAINER.h"
#include "UI.h"
#include "PROCESS_NODE.h"
#include "UI_FACTORY.h"
#include "UI_FUNC_ATTACHER.h"
#include "UI_INPUT_BOX.h"
UI_INPUT_BOX::UI_INPUT_BOX():
	Size(24.0f){
}
UI_INPUT_BOX::UI_INPUT_BOX(UI* rootUi, UI* keyInputUi, UI* pulldownInputUi, UI* inputBoxUi, DRAWER::STATIC_FONT* inputBoxUiDrawer, INPUT_TYPE inputType) :
	Size(24.0f),
	RootUi(rootUi),
	KeyInputUi(keyInputUi),
	PulldownInputUi(pulldownInputUi),
	InputBoxUi(inputBoxUi),
	InputBoxUiDrawer(inputBoxUiDrawer),
	InputType(inputType) {

}

UI_INPUT_BOX::UI_INPUT_BOX(CONTAINER* c, STATIC_FONT* font,INPUT_TYPE inputType) :
	Size(24.0f) {
	createInputBox(c, font, inputType);
}

UI_INPUT_BOX::~UI_INPUT_BOX() {
	delete RootUi;
}

void UI_INPUT_BOX::createInputBox(CONTAINER* c, STATIC_FONT* font, INPUT_TYPE inputType){
	createRootUi(c->texture("processNodeInputBox"));
	RootUi->child()->reserve(3);
	InputBoxUi = new UI;
	InputBoxUiDrawer = DRAWER::STATIC_FONT::instance("", font, VECTOR2(0.0f, 0.0f), VECTOR2(Size, Size), DRAWER::STATIC_FONT::drawMethodAdjustDraw_Over());
	InputBoxUiDrawer->setMaxWidth(12);
	InputBoxUi->create(InputBoxUiDrawer);
	RootUi->addChilds(InputBoxUi);
	InputType = inputType;


	switch (inputType) {
	case UI_INPUT_BOX::INPUT_TYPE::NONE:
		break;
	case UI_INPUT_BOX::INPUT_TYPE::KEY:
		createKeyInputUi(font, VECTOR2(192.0f - Size, 0.0f));
		break;
	case UI_INPUT_BOX::INPUT_TYPE::PULLDOWN:
		createPulldownInputUi(font, VECTOR2(192.0f - Size, 0.0f));
		break;
	case UI_INPUT_BOX::INPUT_TYPE::KEY_PULLDOWN:
		createKeyInputUi(font, VECTOR2(192.0f - Size*2.0f, 0.0f));
		createPulldownInputUi(font, VECTOR2(192.0f - Size*1.0f, 0.0f));
		break;
	}
}

void UI_INPUT_BOX::createInputBox(TEXTURE* inputBoxTexture, int stringMaxWidth, STATIC_FONT* font){
	createRootUi(inputBoxTexture);
	RootUi->child()->reserve(2);
	InputBoxUi = new UI;
	InputBoxUiDrawer = DRAWER::STATIC_FONT::instance("", font, VECTOR2(0.0f, 0.0f), VECTOR2(Size, Size), DRAWER::STATIC_FONT::drawMethodAdjustDraw_Over());
	InputBoxUiDrawer->setMaxWidth(stringMaxWidth);
	InputBoxUi->create(InputBoxUiDrawer);
	RootUi->addChilds(InputBoxUi);
	createPulldownInputUi(font, VECTOR2(Size * stringMaxWidth * 0.5f, 0.0f));
}

void UI_INPUT_BOX::createSmallInputBox(CONTAINER* c, STATIC_FONT* font){
	createRootUi(c->texture("inputBoxSmallStringBack"));
	RootUi->child()->reserve(2);
	InputBoxUi = new UI;
	InputBoxUiDrawer = DRAWER::STATIC_FONT::instance("", font, VECTOR2(0.0f, 0.0f), VECTOR2(Size, Size), DRAWER::STATIC_FONT::drawMethodAdjustDraw_Over());
	InputBoxUiDrawer->setMaxWidth(2);
	InputBoxUi->create(InputBoxUiDrawer);
	RootUi->addChilds(InputBoxUi);
	createPulldownInputUi(font, VECTOR2(Size, 0.0f));
}

void UI_INPUT_BOX::setString(const std::string& s){
	InputBoxUiDrawer->setString(s);
}

void UI_INPUT_BOX::createRootUi(TEXTURE* texture){
	RootUi = UI_FACTORY::instance(texture, VECTOR2(), VECTOR2::one());
	RootUi->setIsChildCollisionRestrict(true);
	RootUi->setIsReleaseDisable(true);
}

void UI_INPUT_BOX::createKeyInputUi(STATIC_FONT* font, const VECTOR2& pos){
	KeyInputUi = new UI;
	DRAWER::STATIC_FONT* drawer = DRAWER::STATIC_FONT::instance("”", font, pos, VECTOR2(Size, Size), DRAWER::STATIC_FONT::drawMethodDefault());
	KeyInputUi->create(drawer);
	UI_FUNC_ATTACHER::OverlapColorChange(KeyInputUi, drawer);
	RootUi->addChilds(KeyInputUi);
}

void UI_INPUT_BOX::createPulldownInputUi(STATIC_FONT* font, const VECTOR2& pos){
	PulldownInputUi = new UI;
	DRAWER::STATIC_FONT* drawer = DRAWER::STATIC_FONT::instance("¥", font, pos, VECTOR2(Size, Size), DRAWER::STATIC_FONT::drawMethodDefault());
	PulldownInputUi->create(drawer);
	UI_FUNC_ATTACHER::OverlapColorChange(PulldownInputUi, drawer);
	RootUi->addChilds(PulldownInputUi);
}
