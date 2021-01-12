#include "../Library/CONTAINER.h"
#include "UI.h"
#include "PROCESS_NODE.h"
#include "UI_FACTORY.h"
#include "UI_INPUT_BOX_COMPARISON_OPERATOR.h"
UI_INPUT_BOX_COMPARISON_OPERATOR::UI_INPUT_BOX_COMPARISON_OPERATOR(CONTAINER* c, STATIC_FONT* font) {
	UiInputBox.createInputBox(c->texture("processNodeInputBoxIf"), 4, font);
}

UI_INPUT_BOX_COMPARISON_OPERATOR::~UI_INPUT_BOX_COMPARISON_OPERATOR() {

}

bool UI_INPUT_BOX_COMPARISON_OPERATOR::variableOperation(double a, double b) {
	return (this->*OperationFunc)(a, b);
}

void UI_INPUT_BOX_COMPARISON_OPERATOR::setString(const std::string& s) {
	if (!s.empty()) {
		if (s == "=="||s=="=" || s == "ÅÅ" || s == "ÅÅÅÅ") {
			OperationFunc = &UI_INPUT_BOX_COMPARISON_OPERATOR::variableOperation_a_Same_b;
		}
		else
		if (s == "<" || s == "ÅÉ") {
			OperationFunc = &UI_INPUT_BOX_COMPARISON_OPERATOR::variableOperation_a_Less_b;
		}
		else
		if (s == ">" || s == "ÅÑ") {
			OperationFunc = &UI_INPUT_BOX_COMPARISON_OPERATOR::variableOperation_a_Greater_b;
		}
		else
		if (s == "<=" || s == "ÅÉÅÅ") {
			OperationFunc = &UI_INPUT_BOX_COMPARISON_OPERATOR::variableOperation_a_LessEqual_b;
		}
		else
		if (s == ">=" || s == "ÅÑÅÅ") {
			OperationFunc = &UI_INPUT_BOX_COMPARISON_OPERATOR::variableOperation_a_GreaterEqual_b;
		}
		else
		if (s == "!=" || s == "ÅIÅÅ") {
			OperationFunc = &UI_INPUT_BOX_COMPARISON_OPERATOR::variableOperation_a_NotSame_b;
		}
		else {
			OperationFunc = &UI_INPUT_BOX_COMPARISON_OPERATOR::variableOperation_Null;
		}
	}
	else {
		OperationFunc = &UI_INPUT_BOX_COMPARISON_OPERATOR::variableOperation_Null;
	}
	UiInputBox.inputBoxUiDrawer()->setString(s);
}

bool UI_INPUT_BOX_COMPARISON_OPERATOR::variableOperation_a_Less_b(double a, double b) {
	return a < b;
}

bool UI_INPUT_BOX_COMPARISON_OPERATOR::variableOperation_a_Greater_b(double a, double b) {
	return a > b;
}

bool UI_INPUT_BOX_COMPARISON_OPERATOR::variableOperation_a_LessEqual_b(double a, double b) {
	return a <= b;
}

bool UI_INPUT_BOX_COMPARISON_OPERATOR::variableOperation_a_GreaterEqual_b(double a, double b) {
	return a >= b;
}

bool UI_INPUT_BOX_COMPARISON_OPERATOR::variableOperation_a_Same_b(double a, double b) {
	return a == b;
}

bool UI_INPUT_BOX_COMPARISON_OPERATOR::variableOperation_a_NotSame_b(double a, double b) {
	return a != b;
}

bool UI_INPUT_BOX_COMPARISON_OPERATOR::variableOperation_Null(double a, double b) {
	return false;
}
