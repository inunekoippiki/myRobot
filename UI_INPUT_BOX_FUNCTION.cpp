#include "../Library/CONTAINER.h"
#include "UI.h"
#include "PROCESS_NODE.h"
#include "UI_FACTORY.h"
#include "UI_INPUT_BOX_FUNCTION.h"

std::unordered_map<std::string, UI_INPUT_BOX_FUNCTION::OPERATION_FUNC> UI_INPUT_BOX_FUNCTION::VariableOperationDispatchTable{
	{"abs", &UI_INPUT_BOX_FUNCTION::variableOperation_abs } ,
	{"sqrt", &UI_INPUT_BOX_FUNCTION::variableOperation_sqrt },
	{"sin", &UI_INPUT_BOX_FUNCTION::variableOperation_sin},
	{"cos", &UI_INPUT_BOX_FUNCTION::variableOperation_cos },
	{"tan", &UI_INPUT_BOX_FUNCTION::variableOperation_tan },
	{"asin", &UI_INPUT_BOX_FUNCTION::variableOperation_asin },
	{"acos", &UI_INPUT_BOX_FUNCTION::variableOperation_acos },
	{"atan", &UI_INPUT_BOX_FUNCTION::variableOperation_atan },
	{"log", &UI_INPUT_BOX_FUNCTION::variableOperation_log },
	{"log10", &UI_INPUT_BOX_FUNCTION::variableOperation_log10 },
	{"exp", &UI_INPUT_BOX_FUNCTION::variableOperation_exp },
	{"exp2", &UI_INPUT_BOX_FUNCTION::variableOperation_exp2 },
	{"rand", &UI_INPUT_BOX_FUNCTION::variableOperation_rand },
	{"cbrt", &UI_INPUT_BOX_FUNCTION::variableOperation_cbrt },
	{"round", &UI_INPUT_BOX_FUNCTION::variableOperation_round }
};
UI_INPUT_BOX_FUNCTION::UI_INPUT_BOX_FUNCTION(CONTAINER* c, STATIC_FONT* font) {
	UiInputBox.createInputBox(c->texture("processNodeInputBoxFunction"), 8, font);
}

UI_INPUT_BOX_FUNCTION::~UI_INPUT_BOX_FUNCTION() {

}

double UI_INPUT_BOX_FUNCTION::variableOperation(double a) {
	return (this->*OperationFunc)(a);
}

void UI_INPUT_BOX_FUNCTION::setString(const std::string& s) {
	if (!s.empty()) {
		if (VariableOperationDispatchTable.contains(s)) {
			OperationFunc = VariableOperationDispatchTable.at(s);
		}
		else{
			OperationFunc = &UI_INPUT_BOX_FUNCTION::variableOperation_Null;
		}
	}
	else {
		OperationFunc = &UI_INPUT_BOX_FUNCTION::variableOperation_Null;
	}
	UiInputBox.inputBoxUiDrawer()->setString(s);
}

double UI_INPUT_BOX_FUNCTION::variableOperation_abs(double a){
	return abs(a);
}

double UI_INPUT_BOX_FUNCTION::variableOperation_sqrt(double a){
	return sqrt(a);
}

double UI_INPUT_BOX_FUNCTION::variableOperation_sin(double a){
	return sin(a);
}

double UI_INPUT_BOX_FUNCTION::variableOperation_cos(double a){
	return cos(a);
}

double UI_INPUT_BOX_FUNCTION::variableOperation_tan(double a){
	return tan(a);
}

double UI_INPUT_BOX_FUNCTION::variableOperation_asin(double a){
	return asin(a);
}

double UI_INPUT_BOX_FUNCTION::variableOperation_acos(double a){
	return acos(a);
}

double UI_INPUT_BOX_FUNCTION::variableOperation_atan(double a){
	return atan(a);
}

double UI_INPUT_BOX_FUNCTION::variableOperation_log(double a){
	return log(a);
}

double UI_INPUT_BOX_FUNCTION::variableOperation_log10(double a){
	return log10(a);
}

double UI_INPUT_BOX_FUNCTION::variableOperation_exp(double a){
	return exp(a);
}

double UI_INPUT_BOX_FUNCTION::variableOperation_exp2(double a){
	return exp2(a);
}

double UI_INPUT_BOX_FUNCTION::variableOperation_rand(double a){
	return ((double)rand() / ((double)RAND_MAX + 1)) * a;
}

double UI_INPUT_BOX_FUNCTION::variableOperation_cbrt(double a){
	return cbrt(a);
}

double UI_INPUT_BOX_FUNCTION::variableOperation_round(double a){
	return round(a);
}

double UI_INPUT_BOX_FUNCTION::variableOperation_Null(double a){
	return 0.0;
}


