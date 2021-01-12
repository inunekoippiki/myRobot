#pragma once
#include <string>
#include "ROBOT_COMPILER_ERROR.h"
class PROCESS_NODE;
class PROCESS_NODE_START;
class PROCESS_NODE_JUMP_POINT;
class ROBOT_PROCESSOR;
class UI_INPUT_BOX_VARIABLE;
class ROBOT_COMPILER {
public:
	ROBOT_COMPILER(ROBOT_PROCESSOR* robotProcessor);
	~ROBOT_COMPILER();
	void compileStart(const std::vector<PROCESS_NODE*>& processNodeList);
	void compileEnd();
	void setProcessNodeStart(PROCESS_NODE_START* processNodeStart);
	void addJumpPoint(const std::string& s, PROCESS_NODE_JUMP_POINT* jumpPoint);
	void addVariable(const UI_INPUT_BOX_VARIABLE& variable);
	void checkOutputModule(const std::string& s);
	void checkInputModule(const std::string& s);
	//�W�����v�|�C���g���Ō�ɏƍ����邽�߂ɃW�����v�|�C���g�����v�b�V�����Ă���
	void checkJumpPoint(const std::string& s);
	//�G���[�̏��Ȃ�
	const ROBOT_COMPILER_ERROR* error() const{ return &Error; }
private:
	//���p��
	ROBOT_PROCESSOR* RobotProcessor = nullptr;
	//�W�����v�|�C���g�ƍ��p
	std::vector<std::string> JumpList;
	//�ϊ������ۂ̃G���[�̏��Ȃ�
	ROBOT_COMPILER_ERROR Error;
};

