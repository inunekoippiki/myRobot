#pragma once
#include <unordered_map>
#include <stack>
#include "ROBOT_COMPILER.h"
#include "UI_ANNOTATION.h"
#include "OUTPUT_MODULE_LIST.h"
#include "INPUT_MODULE_LIST.h"
class OUTPUT_MODULE_VALUE;
class INPUT_MODULE_VALUE;
class PROCESS_NODE;
class PROCESS_NODE_JUMP_BACK;
class PROCESS_NODE_START;
class ROBOT_PROCESSOR{
public:
	ROBOT_PROCESSOR();
	~ROBOT_PROCESSOR();
	//�o�̓��W���[�����X�g��K�p
	void createOutputModuleList(OUTPUT_MODULE_LIST&& outputModuleList);
	//���̓��W���[�����X�g��K�p
	void createInputModuleList(INPUT_MODULE_LIST&& inputModuleList);
	//�o�̓��W���[�����X�g�ɒǉ�
	void addOutputModule(const std::string& s,const OUTPUT_MODULE_DATA& data);
	//���̓��W���[�����X�g�ɒǉ�
	void addInputModule(const std::string& s, const INPUT_MODULE_DATA& data);
	//�m�[�h�����s���邽�߂̏���
	void startCompile(const std::vector<PROCESS_NODE*>& processNodeList);
	//�J�n�m�[�h���Z�b�g����
	void setProcessNodeStart(PROCESS_NODE_START* processNodeStart);
	//�J�n�m�[�h��Ԃ��B������nullptr
	PROCESS_NODE_START* processNodeStart() { return ProcessNodeStart; }
	auto& outputModuleList(){ return OutputModuleList; }
	auto& inputModuleList() { return InputModuleList; }
	auto& jumpPointList() { return JumpPointList; }
	auto& variableList() { return VariableList; }
	//�A�E�g�v�b�g���W���[���̒l��Ԃ�
	double outputModule(const std::string& s);
	//�C���v�b�g���W���[���ɒl�𑗂�
	void inputModule(const std::string& s,double value);
	//�ϐ���Ԃ�
	double variable(const std::string& s);
	//�ϐ���������
	void setVariable(const std::string& s, double value);
	//���s����
	void stepStart();
	//�O�̃t���[���̑���������s���n�߂�
	void stepIn();
	//1�t���[���Ɏ��s�ł���v���Z�X�������Z�B����ȏゾ��true��Ԃ�
	bool stepCnt();
	//�t���[������b�ɂ���
	double waitFrameTime();
	//�ҋ@�m�[�h�̑҂����ԃ^�C�}�[��i�߂�
	void addTime();
	//�ҋ@�m�[�h�̑҂����ԃ^�C�}�[�����Z�b�g����
	void resetTime();
	//1�t���[���̎��s�̏I���
	void oneFrameProcessEnd(PROCESS_NODE* processNode);
	//�W�����v�o�b�N�ɓ��鎞
	void JumpBackIn(PROCESS_NODE_JUMP_BACK* processNode);
	//���̃m�[�h���Ȃ��Ƃ��A�W�����v�o�b�N�̒���������W�����v�o�b�N�̓�����܂Ŗ߂�
	void JumpBackReturn();
	//���s�I���
	void ProcessEnd();

	const ROBOT_COMPILER* robotCompiler()const { return &RobotCompiler; }
	const auto& jumpBackPointStack() {return JumpBackPointStack; }
private:
	//��t���[���Ɏ��s�����v���Z�X��
	int OneFrameStepCnt = 0;
	//�ҋ@�m�[�h�p�̃^�C�}�[
	int WaitFrameCnt = 0;
	//���݂̃m�[�h
	PROCESS_NODE* CurrentProcessNode = nullptr;
	//�J�n�m�[�h
	PROCESS_NODE_START* ProcessNodeStart = nullptr;
	using JUMP_BACK_POINT_STACK = std::stack<PROCESS_NODE_JUMP_BACK*, std::vector<PROCESS_NODE_JUMP_BACK*>>;
	//�W�����v�o�b�N�ɓ��鎞�ςރX�^�b�N
	JUMP_BACK_POINT_STACK JumpBackPointStack;
	//�o�̓��W���[�����X�g
	OUTPUT_MODULE_LIST OutputModuleList;
	//���̓��W���[�����X�g
	INPUT_MODULE_LIST InputModuleList;
	//�W�����v�|�C���g���X�g
	std::unordered_map<std::string, PROCESS_NODE*> JumpPointList;
	//�ϐ����X�g
	std::unordered_map<std::string, double> VariableList;
	//UI�̃m�[�h��񂩂���s����������
	ROBOT_COMPILER RobotCompiler;
	//�W�����v�o�b�N���̎��߂�ׂ��m�[�h��Ԃ��B�����łȂ�������nullptr��Ԃ�
	PROCESS_NODE_JUMP_BACK* jumpBackOut();
};

