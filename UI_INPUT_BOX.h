#pragma once
#include "../Library/STATIC_FONT.h"
#include "DRAWER_STATIC_FONT.h"
class PROCESS_NODE;
class UI;
class CONTAINER;
class UI_INPUT_BOX{
public:
	enum class INPUT_TYPE {
		NONE, KEY, PULLDOWN, KEY_PULLDOWN
	};
	UI_INPUT_BOX();
	UI_INPUT_BOX(
		UI* rootUi, 
		UI* keyInputUi,
		UI* pulldownInputUi,
		UI* inputBoxUi,
		DRAWER::STATIC_FONT* inputBoxUiDrawer,
		INPUT_TYPE inputType
	);

	UI_INPUT_BOX(CONTAINER* c, STATIC_FONT* font, INPUT_TYPE inputType);
	~UI_INPUT_BOX();
	void createInputBox(CONTAINER* c, STATIC_FONT* font,INPUT_TYPE inputType);
	void createInputBox(TEXTURE* inputBoxTexture, int stringMaxWidth, STATIC_FONT* font);
	void createSmallInputBox(CONTAINER* c, STATIC_FONT* font);
	UI* rootUi() { return RootUi; }
	UI* keyInputUi() { return KeyInputUi; }
	UI* pulldownInputUi() { return PulldownInputUi; }
	UI* inputBoxUi() { return InputBoxUi; }
	void setString(const std::string& s);
	std::string string() { return InputBoxUiDrawer->string(); }
	DRAWER::STATIC_FONT* inputBoxUiDrawer() const{ return InputBoxUiDrawer; }
private:
	void createRootUi(TEXTURE* texture);
	void createKeyInputUi(STATIC_FONT* font,const VECTOR2& pos);
	void createPulldownInputUi(STATIC_FONT* font, const VECTOR2& pos);
	float Size = 0.0f;
	INPUT_TYPE InputType = INPUT_TYPE::NONE;
	UI* RootUi = nullptr;
	UI* KeyInputUi = nullptr;
	UI* PulldownInputUi = nullptr;
	UI* InputBoxUi = nullptr;
	DRAWER::STATIC_FONT* InputBoxUiDrawer = nullptr;
};

