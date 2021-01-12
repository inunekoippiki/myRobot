#pragma once
#include "UI_INPUT_BOX_VARIABLE.h"
class UI_INPUT_BOX_VARIABLE_TIME {
public:
	using INPUT_TYPE = UI_INPUT_BOX::INPUT_TYPE;
	UI_INPUT_BOX_VARIABLE_TIME(CONTAINER* c, STATIC_FONT* font, INPUT_TYPE inputType, PROCESS_NODE_MANAGER* processNodeManager);
	~UI_INPUT_BOX_VARIABLE_TIME();
	UI_INPUT_BOX* uiInputBox();
	UI* rootUi();
	UI* keyInputUi();
	UI* pulldownInputUi();
	UI* inputBoxUi();
	bool isNumber()const;
	double number() const;
	void setString(const std::string& s);
	std::string string()const;
	DRAWER::STATIC_FONT* inputBoxUiDrawer();
	const UI_INPUT_BOX_VARIABLE& uiInputBoxVariable() const{ return UiInputBoxVariable; }
	void setEnable();
	void setDisable();
private:
	UI_INPUT_BOX_VARIABLE UiInputBoxVariable;
};

