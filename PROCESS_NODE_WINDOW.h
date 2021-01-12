#pragma once
#include "UI.h"
class PROCESS_NODE_WINDOW_OPERATOR;
class PROCESS_NODE_SELECTOR;
class PROCESS_NODE_MANAGER;

class PROCESS_NODE_WINDOW {
public:
	PROCESS_NODE_WINDOW();
	~PROCESS_NODE_WINDOW();
	void create(
		CONTAINER* c,
		STRING_TREE* rootST,
		PROCESS_NODE_SELECTOR* processNodeSelector,
		PROCESS_NODE_MANAGER* processNodeManager);
	//�E�B���h�E����֘A��UI
	UI* cameraOperationUi() { return CameraOperationUi; }
	//�v���Z�X�m�[�h�����郌�C���[
	UI* processNodeListUi() { return ProcessNodeListUi; }
	//����_�����郌�C���[
	UI* processNodeLinePointListUi() {return ProcessNodeLinePointListUi;}
private:
	//�E�B���h�E�ŉ���
	void onDownWindow();
	//�E�B���h�E�h���b�O��
	void onDragWindow();
	//�E�B���h�E���痣����
	void onUpWindow();
	//Scroll�̐^�񒆂�����������
	void onDownCameraButton();
	//Scroll�̐^�񒆃h���b�O��
	void onDragCameraButton();

	//�m�[�h���m���q�����̍X�V
	void addProcessNodeLineUpdate();
	//�{����ύX����
	void designWindowZoom(float scaleAmount, const VECTOR2& localCenter);
	//�{�����グ��
	void designWindowZoomIn();
	//�{����������
	void designWindowZoomOut();
	//�X�N���[��������
	void designWindowMove(const VECTOR2& moveAmount);
	//�}�E�X���[�ɂ���Ƃ����̕����ɃX�N���[��������
	void autoDesignWindowMove();

	//�Q�ƃI�u�W�F�N�g
	PROCESS_NODE_MANAGER* ProcessNodeManager = nullptr;
	PROCESS_NODE_SELECTOR* ProcessNodeSelector = nullptr;
	//�E�B���h�E����p
	PROCESS_NODE_WINDOW_OPERATOR ProcessNodeWindowOperator;
	VECTOR2 MouseDownPos;
	//�v���Z�X�m�[�h�����郌�C���[
	UI* ProcessNodeListUi = nullptr;
	//�v���Z�X�m�[�h���Ȃ����̐���_�����郌�C���[
	UI* ProcessNodeLinePointListUi = nullptr;

	//�e
	UI* CameraOperationUi = nullptr;

	//�e�{�^��UI
	UI* CameraScrollCenterUi = nullptr;
	UI* CameraScrollUpUi = nullptr;
	UI* CameraScrollDownUi = nullptr;
	UI* CameraScrollLeftUi = nullptr;
	UI* CameraScrollRightUi = nullptr;
	UI* CameraZoomInUi = nullptr;
	UI* CameraZoomOutUi = nullptr;
};

