#pragma once
#include <array>
#include "UI.h"
class PROCESS_NODE_ADD{
public:
	PROCESS_NODE_ADD();
	~PROCESS_NODE_ADD();
	void create(
		CONTAINER* c,
		STATIC_FONT* font,
		STRING_TREE* data, 
		PROCESS_NODE_MANAGER* processNodeManager, 
		DRAWER::DRAWERS_SHADER* processNodeLineDrawers,
		PROCESS_NODE_LINER* processNodeLiner);
	UI* rootUi() { return ProceeNodeAddBar; }
	void draw(SHADER* shader);
private:
	//���Âꂩ�̃v���Z�X�m�[�h�ǉ��{�^����������
	void onClickAddProcessButton(PROCESS_NODE* processNode);
	//�v���Z�X�m�[�h���C���X�^���X���ĕԂ�
	template<class T>
	T* processNodeInstance() {
		return new T(Container, Font, ProcessNodeLineDrawers, ProcessNodeLiner, ProcessNodeManager);
	}
	//�Q�ƃI�u�W�F�N�g
	PROCESS_NODE_MANAGER* ProcessNodeManager = nullptr;
	CONTAINER* Container = nullptr;
	STATIC_FONT* Font = nullptr;
	DRAWER::DRAWERS_SHADER* ProcessNodeLineDrawers = nullptr;
	PROCESS_NODE_LINER* ProcessNodeLiner = nullptr;
	//�e�{�^��UI�̘g
	UI* ProceeNodeAddBar = nullptr;
	//�e�{�^��UI
	std::array<UI*, 11> ProcessNodeAddButtonUi = {};
	//��
	SOUND* SoundProcessNodeAdd = nullptr;
};

