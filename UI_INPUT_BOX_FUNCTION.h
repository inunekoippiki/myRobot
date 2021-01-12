#pragma once
#include <unordered_map>
#include "../Library/STATIC_FONT.h"
#include "DRAWER_STATIC_FONT.h"
#include "UI_INPUT_BOX.h"
class PROCESS_NODE;
class UI;
class CONTAINER;
class PROCESS_NODE_MANAGER;
class UI_INPUT_BOX_FUNCTION {
public:
	using OPERATION_FUNC = double (UI_INPUT_BOX_FUNCTION::*)(double);
	using INPUT_TYPE = UI_INPUT_BOX::INPUT_TYPE;
	UI_INPUT_BOX_FUNCTION(CONTAINER* c, STATIC_FONT* font);
	~UI_INPUT_BOX_FUNCTION();
	UI_INPUT_BOX* uiInputBox() { return &UiInputBox; }
	UI* rootUi() { return UiInputBox.rootUi(); }
	UI* keyInputUi() { return UiInputBox.keyInputUi(); }
	UI* pulldownInputUi() { return UiInputBox.pulldownInputUi(); }
	UI* inputBoxUi() { return UiInputBox.inputBoxUi(); }
	//‚±‚ÌInputBox‚Ì”äŠr‰‰ŽZŽq‚Å”äŠr
	double variableOperation(double a);
	void setString(const std::string& s);
	std::string string() { return  UiInputBox.inputBoxUiDrawer()->string(); }
	DRAWER::STATIC_FONT* inputBoxUiDrawer() { return UiInputBox.inputBoxUiDrawer(); }
private:
	double variableOperation_abs(double a);
	double variableOperation_sqrt(double a);
	double variableOperation_sin(double a);
	double variableOperation_cos(double a);
	double variableOperation_tan(double a);
	double variableOperation_asin(double a);
	double variableOperation_acos(double a);
	double variableOperation_atan(double a);
	double variableOperation_log(double a);
	double variableOperation_log10(double a);
	double variableOperation_exp(double a);
	double variableOperation_exp2(double a);
	double variableOperation_rand(double a);
	double variableOperation_cbrt(double a);
	double variableOperation_round(double a);
	double variableOperation_Null(double a);
	OPERATION_FUNC OperationFunc = &UI_INPUT_BOX_FUNCTION::variableOperation_Null;
	UI_INPUT_BOX UiInputBox;
	static std::unordered_map<std::string, OPERATION_FUNC> VariableOperationDispatchTable;
};

