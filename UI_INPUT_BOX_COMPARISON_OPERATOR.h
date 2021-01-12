#pragma once
#include "../Library/STATIC_FONT.h"
#include "DRAWER_STATIC_FONT.h"
#include "UI_INPUT_BOX.h"
class PROCESS_NODE;
class UI;
class CONTAINER;
class PROCESS_NODE_MANAGER;
class UI_INPUT_BOX_COMPARISON_OPERATOR {
public:
	using OPERATION_FUNC = bool (UI_INPUT_BOX_COMPARISON_OPERATOR::*)(double, double);
	using INPUT_TYPE = UI_INPUT_BOX::INPUT_TYPE;
	UI_INPUT_BOX_COMPARISON_OPERATOR(CONTAINER* c, STATIC_FONT* font);
	~UI_INPUT_BOX_COMPARISON_OPERATOR();
	UI_INPUT_BOX* uiInputBox(){ return &UiInputBox; }
	UI* rootUi() { return UiInputBox.rootUi(); }
	UI* keyInputUi() { return UiInputBox.keyInputUi(); }
	UI* pulldownInputUi() { return UiInputBox.pulldownInputUi(); }
	UI* inputBoxUi() { return UiInputBox.inputBoxUi(); }
	//‚±‚ÌInputBox‚Ì”äŠr‰‰ŽZŽq‚Å”äŠr
	bool variableOperation(double a, double b);
	void setString(const std::string& s);
	std::string string() { return  UiInputBox.inputBoxUiDrawer()->string(); }
	DRAWER::STATIC_FONT* inputBoxUiDrawer() { return UiInputBox.inputBoxUiDrawer(); }
private:
	bool variableOperation_a_Less_b(double a, double b);
	bool variableOperation_a_Greater_b(double a, double b);
	bool variableOperation_a_LessEqual_b(double a, double b);
	bool variableOperation_a_GreaterEqual_b(double a, double b);
	bool variableOperation_a_Same_b(double a, double b);
	bool variableOperation_a_NotSame_b(double a, double b);
	bool variableOperation_Null(double a, double b);
	OPERATION_FUNC OperationFunc = &UI_INPUT_BOX_COMPARISON_OPERATOR::variableOperation_Null;
	UI_INPUT_BOX UiInputBox;
};

