#include "ROBOT_COMPILER_ERROR.h"
ROBOT_COMPILER_ERROR::ROBOT_COMPILER_ERROR() {
	ErrorList.reserve(256);
}

ROBOT_COMPILER_ERROR::~ROBOT_COMPILER_ERROR() {
}

void ROBOT_COMPILER_ERROR::noneOutputModule(){
	ErrorList.push_back(NONE_OUTPUT_MODULE_NODE());
}

void ROBOT_COMPILER_ERROR::noneInputModule(){
	ErrorList.push_back(NONE_INPUT_MODULE_NODE());
}

void ROBOT_COMPILER_ERROR::noneStartNode(){
	ErrorList.push_back(NONE_START_NODE());
}

void ROBOT_COMPILER_ERROR::duplecateStartNode(){
	ErrorList.push_back(DUPLECATE_START_NODE());
}

void ROBOT_COMPILER_ERROR::noneJumpPoint(){
	ErrorList.push_back(NONE_JUMP_POINT());
}

void ROBOT_COMPILER_ERROR::duplecateJumpPoint(){
	ErrorList.push_back(DUPLECATE_JUMP_POINT());
}

void ROBOT_COMPILER_ERROR::clear(){
	ErrorList.clear();
}

bool ROBOT_COMPILER_ERROR::isNotError()const {
	struct VISITOR_IS_ERROR {
		bool operator()(const NONE_OUTPUT_MODULE_NODE& node) { return false; }
		bool operator()(const NONE_INPUT_MODULE_NODE& node) { return false; }
		bool operator()(const NONE_START_NODE& node) { return true; }
		bool operator()(const DUPLECATE_START_NODE& node) { return true; }
		bool operator()(const NONE_JUMP_POINT& node) { return false; }
		bool operator()(const DUPLECATE_JUMP_POINT& node) { return false; }
	};
	for (auto i : ErrorList) {
		if (std::visit(VISITOR_IS_ERROR(), i)) {
			return false;
		}
	}
	return true;
}
