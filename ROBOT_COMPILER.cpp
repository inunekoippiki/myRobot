#include "ROBOT_PROCESSOR.h"
#include "PROCESS_NODE_JUMP_POINT.h"
#include "UI_INPUT_BOX_VARIABLE.h"
#include "ROBOT_COMPILER.h"
ROBOT_COMPILER::ROBOT_COMPILER(ROBOT_PROCESSOR* robotProcessor):
	RobotProcessor(robotProcessor) {
}

ROBOT_COMPILER::~ROBOT_COMPILER() {
}

void ROBOT_COMPILER::compileStart(const std::vector<PROCESS_NODE*>& processNodeList){
	JumpList.clear();
	Error.clear();
	for (auto& i : processNodeList) {
		i->compile(this);
	}
	compileEnd();
}

void ROBOT_COMPILER::compileEnd(){
	if (RobotProcessor->processNodeStart() == nullptr) {//�X�^�[�g�m�[�h�����݂��Ȃ�
		//�G���[
		Error.noneStartNode();
	}
	for (auto& i : JumpList) {
		if (!RobotProcessor->jumpPointList().contains(i)) {//�W�����v�|�C���g�����݂��Ȃ�
			//�G���[
			Error.noneJumpPoint();
		}
	}
}


void ROBOT_COMPILER::setProcessNodeStart(PROCESS_NODE_START* processNodeStart){
	if (RobotProcessor->processNodeStart() == nullptr) {
		RobotProcessor->setProcessNodeStart(processNodeStart);
	}
	else {//2�ȏ�̂̃X�^�[�g�m�[�h������
		//�G���[
		Error.duplecateStartNode();
	}
}

void ROBOT_COMPILER::addJumpPoint(const std::string& s, PROCESS_NODE_JUMP_POINT* jumpPoint){
	if (!RobotProcessor->jumpPointList().contains(s)) {
		RobotProcessor->jumpPointList().insert({ s,jumpPoint });
	}
	else{//�����̃W�����v�|�C���g������
		//�G���[
		Error.duplecateJumpPoint();
	}
}

void ROBOT_COMPILER::addVariable(const UI_INPUT_BOX_VARIABLE& variable){
	if (variable.isNumber()) {
		//�萔�͂��̒l�����̂܂ܖ��O�ɂȂ����ϐ��Ƃ��Ĉ���
		RobotProcessor->variableList().insert({ variable.string(),variable.number() });
	}
	else {
		RobotProcessor->variableList().insert({ variable.string(),0.0f });
	}
}

void ROBOT_COMPILER::checkOutputModule(const std::string& s){
	if (!RobotProcessor->outputModuleList().list()->contains(s)) {//�o�̓��W���[�������݂��Ȃ�
		//�G���[
		Error.noneOutputModule();
	}
}

void ROBOT_COMPILER::checkInputModule(const std::string& s){
	if (!RobotProcessor->inputModuleList().list()->contains(s)) {//���̓��W���[�������݂��Ȃ�
		//�G���[
		Error.noneInputModule();
	}
}

void ROBOT_COMPILER::checkJumpPoint(const std::string& s){
	JumpList.push_back(s);
}

