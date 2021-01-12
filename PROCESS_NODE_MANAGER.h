#pragma once
#include <array>
#include <functional>
#include <string>
#include "../Library/VECTOR2.h"
#include "../Library/IMAGE_2D.h"
#include "DRAWERS_SHADER.h"
#include "PROCESS_NODE_LINER.h"
#include "PROCESS_NODE_SELECTOR.h"
#include "UI_SCROLL_ADD_COUNT.h"
#include "UI_SCROLL.h"
#include "ROBOT_COMPILER.h"
#include "ROBOT_PROCESSOR.h"
#include "PROCESS_NODE_WINDOW_OPERATOR.h"
#include "PROCESS_NODE_ADD.h"
#include "PROCESS_NODE_WINDOW.h"
#include "PROCESS_NODE_OPERATOR.h"
#include "PROCESS_NODE_LOAD_SCROLL.h"
#include "PROCESS_NODE_COMMAND_STREAM.h"
class IMAGE_2D;
namespace DRAWER {
	class DRAWERS_LIST;
};
class UI_KEYBOARD;
class UI_SCROLL;
class UI;
class STATIC_FONT;
class CONTAINER;
class PROCESS_NODE;
class SOUND;
class PROCESS_NODE_MANAGER {
public:
	PROCESS_NODE_MANAGER(
		CONTAINER* c,
		STATIC_FONT* font,
		IMAGE_2D* image2dShader);
	~PROCESS_NODE_MANAGER();
	UI* rootUi() { return RootUi; }
	void draw();
	//�L�[�{�[�h��\������B�m�莞��callback(������)���Ăяo��
	void startKeyboardInput(const std::function<void(const std::string&)>& callback);
	//�w��̃X�N���[���I����\������B�m�莞��callback(������)���Ăяo���Bpos�͕\���ʒu
	void startScrollInput(UI_SCROLL* uiScroll, const VECTOR2& pos, const std::function<void(const std::string&)>& callback);
	//�Z�[�u�f�[�^���[�h�p�̃��X�g�X�N���[����\������
	void startSaveDataLoadScroll();
	//�Z�[�u�f�[�^�Z�[�u�p�̃L�[�{�[�h��\������
	void startSaveDataSaveKeyBoard();

	//�v���Z�X�m�[�h��ǉ�
	void addProcessNode(PROCESS_NODE* processNode);
	//�v���Z�X�m�[�h���폜
	void removeProcessNode(PROCESS_NODE* processNode);

	//�Z���N�^�[�őI�����ꂽ�m�[�h���n�C���C�g����e�N�X�`���̈ʒu���X�V����
	void processNodeSelectorUpdate();

	//�ϐ���ǉ�����
	void addVariable(const std::string& s);
	//�ϐ����폜����
	void removeVeriable(const std::string& s);
	//�W�����v�|�C���g��ǉ�����
	void addJumpPoint(const std::string& s);
	//�W�����v�|�C���g���폜����
	void removeJumpPoint(const std::string& s);
	//���{�b�g�̏�񂩂烂�W���[���X�N���[���̓��e���X�V����
	void setModuleScroll(ROBOT_PROCESSOR* RobotProcessor);

	UI_SCROLL* variableScroll() { return VariableScroll.uiScroll(); }
	UI_SCROLL* inputModuleScroll() { return &InputModuleScroll; }
	UI_SCROLL* outputModuleScroll() { return &OutputModuleScroll; }
	UI_SCROLL* jumpPointScroll() { return JumpPointScroll.uiScroll(); }
	UI_SCROLL* comparisonOperatorScroll() { return &ComparisonOperatorScroll; }
	UI_SCROLL* assignmentOperatorScroll() { return &AssignmentOperatorScroll; }
	UI_SCROLL* operatorScroll() { return &OperatorScroll; }
	UI_SCROLL* functionScroll() { return &FunctionScroll; }
	DRAWER::DRAWERS_SHADER* processNodeLineDrawers() { return &ProcessNodeLineDrawers; }
	PROCESS_NODE_LINER* processNodeLiner() { return &ProcessNodeLiner; }
	PROCESS_NODE_COMMAND_STREAM *commandStream() { return &CommandStream; }
	void sendStringFunc(const std::string& str);
	void createUiScroll(UI_SCROLL* uiScroll, STRING_TREE* data, const std::string& scrollName);
	UI* instanceUiScrollListNode(const char* s);
	const std::vector<PROCESS_NODE*>& processNodeList() { return ProcessNodeList; }
	UI* processNodeListUi() { return ProcessNodeWindow.processNodeListUi(); }
	static void createUiScroll(UI_SCROLL* uiScroll,  CONTAINER* c, STATIC_FONT* font, std::vector<UI*>&& listUi);
	static void createUiScroll(UI_SCROLL_ADD_COUNT* uiScrollAddCount,  CONTAINER* c, STATIC_FONT* font, std::vector<UI*>&& listUi);
	static UI* instanceUiScrollListNode(PROCESS_NODE_MANAGER* processNodeManager, CONTAINER* c, STATIC_FONT* font, const char* s);
	static UI* instanceUiScrollListNode(PROCESS_NODE_MANAGER* processNodeManager, CONTAINER* c, STATIC_FONT* font, const char* s, const UI_ANNOTATION& annotation);
private:
	CONTAINER* Container = nullptr;
	STATIC_FONT* Font = nullptr;
	IMAGE_2D* Image2dShader = nullptr;
	DRAWER::DRAWERS_SHADER ProcessNodeLineDrawers;
	DRAWER::DRAWERS_SHADER ProcessNodeSelectField ;
	DRAWER::DRAWERS_SHADER ProcessNodeSelectRangeField;
	DRAWER::DRAWERS_SHADER ProcessNodeSelectLineField;

	UI* RootUi = nullptr;


	PROCESS_NODE_ADD ProcessNodeAdd;
	PROCESS_NODE_WINDOW ProcessNodeWindow;
	PROCESS_NODE_OPERATOR ProcessNodeOperator;
	PROCESS_NODE_LINER ProcessNodeLiner;
	PROCESS_NODE_SELECTOR* ProcessNodeSelector = nullptr;
	PROCESS_NODE_COMMAND_STREAM CommandStream;

	UI* PopupUi = nullptr;
	UI_KEYBOARD* UiKeyboard = nullptr;

	UI_SCROLL_ADD_COUNT VariableScroll;
	std::function<void(const std::string&)> SendStringFunc = nullptr;

	UI_SCROLL InputModuleScroll;//���̓��W���[���I���X�N���[��
	UI_SCROLL OutputModuleScroll;//���̓��W���[���I���X�N���[��
	UI_SCROLL_ADD_COUNT JumpPointScroll;//�W�����v�|�C���g�I���X�N���[��
	UI_SCROLL ComparisonOperatorScroll;//��r���Z�q�I���X�N���[��
	UI_SCROLL AssignmentOperatorScroll;//������Z�q�|�C���g�I���X�N���[��
	UI_SCROLL OperatorScroll;//���Z�q�I���X�N���[��
	UI_SCROLL FunctionScroll;//�֐��I���X�N���[��
	PROCESS_NODE_LOAD_SCROLL SaveDataLoadScroll;
	std::vector<PROCESS_NODE*> ProcessNodeList;
	//��
	SOUND* SoundProcessNodeAdd = nullptr;
	SOUND* SoundButton = nullptr;
	SOUND* SoundProcessSave = nullptr;
	SOUND* SoundProcessLoad = nullptr;
};

