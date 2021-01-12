#include "UI_INPUT_BOX_VARIABLE_TIME.h"

UI_INPUT_BOX_VARIABLE_TIME::UI_INPUT_BOX_VARIABLE_TIME(
	CONTAINER* c, 
	STATIC_FONT* font,
	INPUT_TYPE inputType, 
	PROCESS_NODE_MANAGER* processNodeManager):
	UiInputBoxVariable(c,font,inputType,processNodeManager){
}

UI_INPUT_BOX_VARIABLE_TIME::~UI_INPUT_BOX_VARIABLE_TIME(){
}

UI_INPUT_BOX* UI_INPUT_BOX_VARIABLE_TIME::uiInputBox() { 
	return UiInputBoxVariable.uiInputBox();
}

UI* UI_INPUT_BOX_VARIABLE_TIME::rootUi() {
	return UiInputBoxVariable.rootUi();
}

UI* UI_INPUT_BOX_VARIABLE_TIME::keyInputUi() {
	return UiInputBoxVariable.keyInputUi();
}
UI* UI_INPUT_BOX_VARIABLE_TIME::pulldownInputUi() { 
	return UiInputBoxVariable.pulldownInputUi(); 
}

UI* UI_INPUT_BOX_VARIABLE_TIME::inputBoxUi() { 
	return UiInputBoxVariable.inputBoxUi();
}

bool UI_INPUT_BOX_VARIABLE_TIME::isNumber() const {
	return UiInputBoxVariable.isNumber();
}

double UI_INPUT_BOX_VARIABLE_TIME::number() const {
	return UiInputBoxVariable.number(); 
}

void UI_INPUT_BOX_VARIABLE_TIME::setString(const std::string& s){
	if (strchr("-+0123456789", s.front())) {
		double time = atof(s.c_str());
		constexpr double oneFrameTime = 1.0 / 60.0;
		int frame = (int)(time / oneFrameTime);
		UiInputBoxVariable.setString(std::to_string(frame * oneFrameTime));
	}
	else {
		UiInputBoxVariable.setString(s);
	}
}

std::string UI_INPUT_BOX_VARIABLE_TIME::string() const {
	return  UiInputBoxVariable.string();
}

DRAWER::STATIC_FONT* UI_INPUT_BOX_VARIABLE_TIME::inputBoxUiDrawer() {
	return UiInputBoxVariable.inputBoxUiDrawer();
}

void UI_INPUT_BOX_VARIABLE_TIME::setEnable(){
	UiInputBoxVariable.setEnable();
}

void UI_INPUT_BOX_VARIABLE_TIME::setDisable(){
	UiInputBoxVariable.setDisable();
}
