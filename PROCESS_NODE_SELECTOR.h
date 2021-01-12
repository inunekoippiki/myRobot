#pragma once
#include <string>
#include <vector>
#include "DRAWER_IMAGE2D.h"
#include "COLLISION2D_RECT.h"
class PROCESS_NODE;
class COLLISION2D;
class CONTAINER;
class STATIC_FONT;
class PROCESS_NODE_WINDOW;
class PROCESS_NODE_MANAGER;
class PROCESS_NODE_CONNECTOR_IN;
namespace DRAWER {
	class DRAWERS_SHADER;
}
class PROCESS_NODE_SELECTOR{
public:
	PROCESS_NODE_SELECTOR(
		CONTAINER* c, 
		STATIC_FONT* font,
		DRAWER::DRAWERS_SHADER* processNodeSelectField,
		DRAWER::DRAWERS_SHADER* processNodeSelectRangeField,
		PROCESS_NODE_MANAGER* processNodeManager,
		PROCESS_NODE_WINDOW* processNodeWindow);
	~PROCESS_NODE_SELECTOR();
	void mouseDown(const VECTOR2& localPos);
	void mouseDragUpdate(const VECTOR2& localPos);
	void mouseUp();
	//collision�͈͓̔��̃m�[�h��I��
	void select(COLLISION2D* collision);
	//collision�͈͓̔��̃m�[�h��I��
	void select(const VECTOR2& localSt, const VECTOR2& localEd);
	//selectList�̃m�[�h��I��
	void select(const std::vector<PROCESS_NODE*>& selectList);
	//�O�̑I����oldSelectList�ɓ���
	void select(const std::vector<PROCESS_NODE*>& selectList, std::vector<PROCESS_NODE*>& oldSelectList);
	//�V���ɑI�������ۂ̍X�V
	void selectUpdate();
	//�I����Ԃ̃I�[�o�[���C�̕`��ʒu���X�V����
	void drawerUpdate();
	//�I����Ԃ̐����X�V
	void updateLine();
	//�I�����Ă���m�[�h���폜����(true�ō폜������̂��Ȃ�)
	bool removeSelectProcessNode();
	//�I�����Ă���m�[�h�̈ʒu��x���ő�����
	void AlignPosXSelectProcessNode();
	//�I�����Ă���m�[�h�̈ʒu��y���ő�����
	void AlignPosYSelectProcessNode();
	//�I����Ԃ̃m�[�h�f�[�^�𕶎���f�[�^�ɂ��ĕۑ�
	void CopySelectProcessNode();
	//�R�s�[����Ă���������f�[�^�Ńm�[�h��ǉ�
	void processNodePaste();
	//�y�[�X�g�i�f�[�^�w��j
	void processNodePaste(const std::string& Data);
	//v�͈ړ���
	void moveSelectProcessNode(const VECTOR2& v);
	//�I�𒆂̃m�[�h�̃��X�g
	std::vector<PROCESS_NODE*>* selectList() { return &SelectList; }

private:
	//�e�m�[�h��Back�̐����������Ă��Ȃ��̂ŁAFront�̐��͑O�̃m�[�h����X�V���Ȃ��Ƃ����Ȃ��B
	//�I�𒆂�Back�m�[�h�̑S�Ăƌ�������update����Ă��Ȃ��R�l�N�^�[�m�[�h��T���čX�V����B
	void selectProcessNodeFrontLineUpdate(PROCESS_NODE_CONNECTOR_IN* nodeConnectorIn);
	//�Q�ƃI�u�W�F�N�g
	CONTAINER* Container = nullptr;
	STATIC_FONT* Font = nullptr;
	DRAWER::DRAWERS_SHADER* ProcessNodeSelectField = nullptr;
	DRAWER::DRAWERS_SHADER* ProcessNodeSelectRangeField = nullptr;
	PROCESS_NODE_MANAGER* ProcessNodeManager = nullptr;
	PROCESS_NODE_WINDOW* ProcessNodeWindow = nullptr;
	//�}�E�X�������������̍��W(�m�[�h�̃��C���[�̃��[�J�����W)
	VECTOR2 MouseDownWindowLocalPos;
	//�}�E�X���h���b�O���̍��W(�m�[�h�̃��C���[�̃��[�J�����W)
	VECTOR2 MouseWindowLocalPos;
	//�I��͈͕\���p
	DRAWER::IMAGE2D* SelectRangeDrawer = nullptr;
	//�I�𒆂̃m�[�h�n�C���C�g�p
	std::vector <DRAWER::IMAGE2D*> SelectProcessNodeOverlay;
	//�I�𒆂̃m�[�h�̃��X�g
	std::vector<PROCESS_NODE*> SelectList;
	//�R�s�[���̃f�[�^
	std::string CopyDataString;
};

