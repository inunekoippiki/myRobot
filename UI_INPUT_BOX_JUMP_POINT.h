#pragma once
#include "../Library/STATIC_FONT.h"
#include "DRAWER_STATIC_FONT.h"
#include "UI_INPUT_BOX.h"
class PROCESS_NODE;
class UI;
class CONTAINER;
class PROCESS_NODE_MANAGER;
class UI_INPUT_BOX_JUMP_POINT {
public:
	using INPUT_TYPE = UI_INPUT_BOX::INPUT_TYPE;
	UI_INPUT_BOX_JUMP_POINT(CONTAINER* c, STATIC_FONT* font, PROCESS_NODE_MANAGER* processNodeManager);
	~UI_INPUT_BOX_JUMP_POINT();
	UI_INPUT_BOX* uiInputBox() { return &UiInputBox; }
	UI* rootUi() { return UiInputBox.rootUi(); }
	UI* keyInputUi() { return UiInputBox.keyInputUi(); }
	UI* pulldownInputUi() { return UiInputBox.pulldownInputUi(); }
	UI* inputBoxUi() { return UiInputBox.inputBoxUi(); }
	void setString(const std::string& s);
	std::string string()const { return  UiInputBox.inputBoxUiDrawer()->string(); }
	DRAWER::STATIC_FONT* inputBoxUiDrawer() { return UiInputBox.inputBoxUiDrawer(); }
	void setEnable();
	void setDisable();
private:
	bool IsDisable = false;
	PROCESS_NODE_MANAGER* ProcessNodeManager = nullptr;
	UI_INPUT_BOX UiInputBox;
};

