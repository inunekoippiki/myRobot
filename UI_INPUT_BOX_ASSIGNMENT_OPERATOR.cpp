#include "../Library/CONTAINER.h"
#include "UI.h"
#include "PROCESS_NODE.h"
#include "UI_FACTORY.h"
#include "UI_INPUT_BOX_ASSIGNMENT_OPERATOR.h"
UI_INPUT_BOX_ASSIGNMENT_OPERATOR::UI_INPUT_BOX_ASSIGNMENT_OPERATOR(CONTAINER* c, STATIC_FONT* font) {
	UiInputBox.createInputBox(c->texture("processNodeInputBoxAssignment"),4, font);
}

UI_INPUT_BOX_ASSIGNMENT_OPERATOR::~UI_INPUT_BOX_ASSIGNMENT_OPERATOR() {

}

void UI_INPUT_BOX_ASSIGNMENT_OPERATOR::variableOperation(double& a, double b){
	(this->*OperationFunc)(a, b);
}

void UI_INPUT_BOX_ASSIGNMENT_OPERATOR::setString(const std::string& s) {
	if (!s.empty()) {
		if (s == "="||s=="") {
			OperationFunc = &UI_INPUT_BOX_ASSIGNMENT_OPERATOR::variableOperation_a_Equal_b;
		}
		else
		if (s == "+=" || s == "{") {
			OperationFunc = &UI_INPUT_BOX_ASSIGNMENT_OPERATOR::variableOperation_a_Plus_b;
		}
		else
		if (s == "-=" || s == "|") {
			OperationFunc = &UI_INPUT_BOX_ASSIGNMENT_OPERATOR::variableOperation_a_Minus_b;
		}
		else
		if (s == "*=" || s == "~") {
			OperationFunc = &UI_INPUT_BOX_ASSIGNMENT_OPERATOR::variableOperation_a_Multiply_b;
		}
		else
		if (s == "/=" || s == "€") {
			OperationFunc = &UI_INPUT_BOX_ASSIGNMENT_OPERATOR::variableOperation_a_Divide_b;
		}
		else
		if (s == "%=" || s == "“") {
			OperationFunc = &UI_INPUT_BOX_ASSIGNMENT_OPERATOR::variableOperation_a_Modulo_b;
		}
		else {
			OperationFunc = &UI_INPUT_BOX_ASSIGNMENT_OPERATOR::variableOperation_Null;
		}
	}
	else {
		OperationFunc = &UI_INPUT_BOX_ASSIGNMENT_OPERATOR::variableOperation_Null;
	}
	UiInputBox.inputBoxUiDrawer()->setString(s);
}

void UI_INPUT_BOX_ASSIGNMENT_OPERATOR::variableOperation_a_Equal_b(double& a, double b){
	a = b;
}

void UI_INPUT_BOX_ASSIGNMENT_OPERATOR::variableOperation_a_Plus_b(double& a, double b){
	a += b;
}

void UI_INPUT_BOX_ASSIGNMENT_OPERATOR::variableOperation_a_Minus_b(double& a, double b){
	a -= b;
}

void UI_INPUT_BOX_ASSIGNMENT_OPERATOR::variableOperation_a_Multiply_b(double& a, double b){
	a *= b;
}

void UI_INPUT_BOX_ASSIGNMENT_OPERATOR::variableOperation_a_Divide_b(double& a, double b){
	a /= b;
}

void UI_INPUT_BOX_ASSIGNMENT_OPERATOR::variableOperation_a_Modulo_b(double& a, double b){
	a = (double)((long long)a % (long long)b);
}

void UI_INPUT_BOX_ASSIGNMENT_OPERATOR::variableOperation_Null(double& a, double b){
}

