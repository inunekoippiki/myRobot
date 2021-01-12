#pragma once
#include <utility>
#include <string>
#include "UI.h"
#include "PROCESS_NODE_FUNC_SET.h"
#include "PROCESS_NODE_FRAME.h"
class CONTAINER;
class STATIC_FONT;
class STRING_TREE;
class PROCESS_NODE_LINER;
class PROCESS_NODE_CONNECTOR_IN;
class PROCESS_NODE_CONNECTOR_OUT;
class NODE_LINE;
class PROCESS_NODE_MANAGER;
class ROBOT_PROCESSOR;
class ROBOT_COMPILER;
class UI_SCROLL;

class PROCESS_NODE {
public:
	PROCESS_NODE();
	virtual ~PROCESS_NODE() {};
	UI* rootUi();
	//�O�̃R�l�N�^�[�m�[�h��Ԃ�(����)
	virtual std::pair<PROCESS_NODE_CONNECTOR_IN**, int> allNodeConnectorIn() = 0;
	//���̃R�l�N�^�[�m�[�h��Ԃ�(����)
	virtual std::pair<PROCESS_NODE_CONNECTOR_OUT**, int> allNodeConnectorOut() = 0;
	//�Z�[�u�p�̃f�[�^�������Ԃ�
	virtual std::string saveDataString() = 0;
	//�Z�[�u�p�̃f�[�^�����񂩂�ǂݍ���
	virtual void loadFromSaveString(const STRING_TREE& data) = 0;
	//���s�̑O�̏����BROBOT_COMPILER����ăf�[�^���쐬����
	virtual void compile(ROBOT_COMPILER* robotCompiler) = 0;
	//���s
	virtual void nextStep(ROBOT_PROCESSOR* robotProcessor) = 0;
	//����������
	virtual void setEnable() = 0;
	//�񊈐�������
	virtual void setDisable() = 0;

	//�m�[�h�Ɍq�����Ă�����X�V
	static void lineUpdate(PROCESS_NODE* processNode);
	//PROCESS�m�[�h�������̐���_�𐧌�_�p�̃��C���[UI�ɒǉ�����
	static void addLinePointUiToRootUi(PROCESS_NODE* processNode, UI* linePointRootUi);
	//PROCESS�m�[�h�������̐���_�𐧌�_�p�̃��C���[UI����폜����
	static void removeLinePointUiToRootUi(PROCESS_NODE* processNode);
	//�q�����Ă����R�l�N�^�[�Ɏ��g�����������Ƃ�ʒm
	static void disconnect(PROCESS_NODE* processNode);


protected:
	static UI* instanceNodeTypeNameUi(const char* name, STATIC_FONT* font);
	template<class INPUT_OBJ>
	static void startScrollInput(UI* ui, UI_SCROLL* scroll, PROCESS_NODE_MANAGER* processNodeManager, INPUT_OBJ* inputObj) {
		auto callback = PROCESS_NODE_FUNC_SET::inputObjSetStringFunc(inputObj, processNodeManager);
		PROCESS_NODE_FUNC_SET::startScrollInputAnyCallback(ui, scroll, processNodeManager, callback);
	};
	template<class INPUT_OBJ>
	static void startKeyboardInput(UI* ui, PROCESS_NODE_MANAGER* processNodeManager, INPUT_OBJ* inputObj) {
		auto callback = PROCESS_NODE_FUNC_SET::inputObjSetStringFunc(inputObj, processNodeManager);
		PROCESS_NODE_FUNC_SET::startKeyboardInputAnyCallback(ui, processNodeManager, callback);
	}

	PROCESS_NODE_FRAME Frame ;
private:
};

