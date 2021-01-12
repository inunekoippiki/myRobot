#include "../Library/CONTAINER.h"
#include "UI.h"
#include "PROCESS_NODE.h"
#include "UI_FACTORY.h"
#include "UI_INPUT_BOX_OPERATOR.h"
UI_INPUT_BOX_OPERATOR::UI_INPUT_BOX_OPERATOR(CONTAINER* c, STATIC_FONT* font) {
	UiInputBox.createInputBox(c->texture("processNodeInputBoxCalculation"), 4, font);
}

UI_INPUT_BOX_OPERATOR::~UI_INPUT_BOX_OPERATOR() {
	
}

double UI_INPUT_BOX_OPERATOR::variableOperation(double a, double b){
	return (this->*OperationFunc)(a,b);
}

void UI_INPUT_BOX_OPERATOR::setString(const std::string& s) {
	if (!s.empty()) {
		if (s == "+"||s=="{") {
			OperationFunc = &UI_INPUT_BOX_OPERATOR::variableOperation_a_Plus_b;
		}else
		if (s == "-" || s == "|") {
			OperationFunc = &UI_INPUT_BOX_OPERATOR::variableOperation_a_Minus_b;
		}else
		if (s == "*" || s == "~") {
			OperationFunc = &UI_INPUT_BOX_OPERATOR::variableOperation_a_Multiply_b;
		}else
		if (s == "/" || s == "€") {
			OperationFunc = &UI_INPUT_BOX_OPERATOR::variableOperation_a_Divide_b;
		}else
		if (s == "%" || s == "“") {
			OperationFunc = &UI_INPUT_BOX_OPERATOR::variableOperation_a_Modulo_b;
		}else 
		{
			OperationFunc = &UI_INPUT_BOX_OPERATOR::variableOperation_Null;
		}
	}
	else{
		OperationFunc = &UI_INPUT_BOX_OPERATOR::variableOperation_Null;
	}

	UiInputBox.inputBoxUiDrawer()->setString(s);
}

double UI_INPUT_BOX_OPERATOR::variableOperation_a_Plus_b(double a, double b){
	return a+b;
}

double UI_INPUT_BOX_OPERATOR::variableOperation_a_Minus_b(double a, double b){
	return a-b;
}

double UI_INPUT_BOX_OPERATOR::variableOperation_a_Multiply_b(double a, double b){
	return a*b;
}

double UI_INPUT_BOX_OPERATOR::variableOperation_a_Divide_b(double a, double b){
	return a/b;
}

double UI_INPUT_BOX_OPERATOR::variableOperation_a_Modulo_b(double a, double b){
	return(double)((long long)a % (long long)b);
}

double UI_INPUT_BOX_OPERATOR::variableOperation_Null(double a, double b){
	return 0.0;
}


