#include "PROCESS_NODE.h"
#include "PROCESS_NODE_START.h"
#include "INPUT_MODULE_VALUE.h"
#include "OUTPUT_MODULE_VALUE.h"
#include "PROCESS_NODE_JUMP_BACK.h"
#include "ROBOT_PROCESSOR.h"
ROBOT_PROCESSOR::ROBOT_PROCESSOR():
	RobotCompiler(this){
}

ROBOT_PROCESSOR::~ROBOT_PROCESSOR() {
	
}

void ROBOT_PROCESSOR::createOutputModuleList(OUTPUT_MODULE_LIST&& outputModuleList){
	OutputModuleList = outputModuleList;
}

void ROBOT_PROCESSOR::createInputModuleList(INPUT_MODULE_LIST&& inputModuleList){
	InputModuleList = inputModuleList;
}

void ROBOT_PROCESSOR::addOutputModule(const std::string& s, const OUTPUT_MODULE_DATA& data){
	OutputModuleList.list()->insert({ s,data });
}

void ROBOT_PROCESSOR::addInputModule(const std::string& s, const INPUT_MODULE_DATA& data){
	InputModuleList.list()->insert({ s,data });
}

void ROBOT_PROCESSOR::startCompile(const std::vector<PROCESS_NODE*>& processNodeList){
	ProcessNodeStart = nullptr;
	JumpPointList.clear();
	VariableList.clear();
	RobotCompiler.compileStart(processNodeList);
}

//開始ノードをセットする
void ROBOT_PROCESSOR::setProcessNodeStart(PROCESS_NODE_START* processNodeStart) { 
	ProcessNodeStart = processNodeStart; 
}

double ROBOT_PROCESSOR::outputModule(const std::string& s){
	auto& list = *OutputModuleList.list();
	return list[s].Module->outputValue();
}

void ROBOT_PROCESSOR::inputModule(const std::string& s, double value){
	auto& list = *InputModuleList.list();
	list[s].Module->inputValue(value);
}

double ROBOT_PROCESSOR::variable(const std::string& s){
	return VariableList.at(s);
}

void ROBOT_PROCESSOR::setVariable(const std::string& s, double value){
	VariableList.at(s) = value;
}

void ROBOT_PROCESSOR::stepStart(){
	JumpBackPointStack = JUMP_BACK_POINT_STACK();
	OneFrameStepCnt = 0;
	WaitFrameCnt = 0;
	ProcessNodeStart->nextStep(this);
}

void ROBOT_PROCESSOR::stepIn(){
	if (CurrentProcessNode != nullptr) {
		CurrentProcessNode->nextStep(this);
	}
}

bool ROBOT_PROCESSOR::stepCnt(){
	OneFrameStepCnt++;
	if (OneFrameStepCnt > 500) {
		return true;
	}
	return false;
}

double ROBOT_PROCESSOR::waitFrameTime() { 
	return WaitFrameCnt / 60.0; 
}

void ROBOT_PROCESSOR::addTime(){
	WaitFrameCnt++;
}

void ROBOT_PROCESSOR::resetTime(){
	WaitFrameCnt = 0;
}

void ROBOT_PROCESSOR::oneFrameProcessEnd(PROCESS_NODE* processNode){
	CurrentProcessNode = processNode;
	OneFrameStepCnt = 0;
}

void ROBOT_PROCESSOR::JumpBackIn(PROCESS_NODE_JUMP_BACK* processNode){
	JumpBackPointStack.push(processNode);
}

void ROBOT_PROCESSOR::JumpBackReturn(){
	PROCESS_NODE_JUMP_BACK* nextNode = jumpBackOut();
	if (nextNode != nullptr) {
		nextNode->ReturnedStep(this);
	}
	else {
		ProcessEnd();
	}
}

PROCESS_NODE_JUMP_BACK* ROBOT_PROCESSOR::jumpBackOut(){
	if (!JumpBackPointStack.empty()) {
		PROCESS_NODE_JUMP_BACK* node = JumpBackPointStack.top();
		JumpBackPointStack.pop();
		return node;
	}
	return nullptr;
}

void ROBOT_PROCESSOR::ProcessEnd(){
	CurrentProcessNode = nullptr;
}
