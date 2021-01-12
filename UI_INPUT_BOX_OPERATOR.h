#pragma once
#include "../Library/STATIC_FONT.h"
#include "DRAWER_STATIC_FONT.h"
#include "UI_INPUT_BOX.h"
class PROCESS_NODE;
class UI;
class CONTAINER;
class PROCESS_NODE_MANAGER;
class UI_INPUT_BOX_OPERATOR {
public:
	using OPERATION_FUNC = double (UI_INPUT_BOX_OPERATOR::*)(double, double);
	using INPUT_TYPE = UI_INPUT_BOX::INPUT_TYPE;
	UI_INPUT_BOX_OPERATOR(CONTAINER* c, STATIC_FONT* font);
	~UI_INPUT_BOX_OPERATOR();
	UI_INPUT_BOX* uiInputBox() { return &UiInputBox; }
	UI* rootUi() { return UiInputBox.rootUi(); }
	UI* keyInputUi() { return UiInputBox.keyInputUi(); }
	UI* pulldownInputUi() { return UiInputBox.pulldownInputUi(); }
	UI* inputBoxUi() { return UiInputBox.inputBoxUi(); }
	//‚±‚ÌInputBox‚Ì‰‰ŽZŽq‚ÅŒvŽZ
	double variableOperation(double a, double b);
	void setString(const std::string& s);
	std::string string() { return  UiInputBox.inputBoxUiDrawer()->string(); }
	DRAWER::STATIC_FONT* inputBoxUiDrawer() { return UiInputBox.inputBoxUiDrawer(); }
private:
	double variableOperation_a_Plus_b(double a, double b);
	double variableOperation_a_Minus_b(double a, double b);
	double variableOperation_a_Multiply_b(double a, double b);
	double variableOperation_a_Divide_b(double a, double b);
	double variableOperation_a_Modulo_b(double a, double b);
	double variableOperation_Null(double a, double b);
	OPERATION_FUNC OperationFunc = &UI_INPUT_BOX_OPERATOR::variableOperation_Null;
	UI_INPUT_BOX UiInputBox;
};

