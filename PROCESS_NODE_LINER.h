#pragma once
#include "../Library/VECTOR2.h"
#include "NODE_LINE.h"
class PROCESS_NODE;
class PROCESS_NODE_MANAGER;
class PROCESS_NODE_CONNECTOR_OUT;
class PROCESS_NODE_CONNECTOR_IN;
namespace DRAWER {
	class DRAWER_SHADER;
}
class SOUND;
//�v���Z�X�m�[�h�̃R�l�N�^�[���q����
class PROCESS_NODE_LINER{
public:
	PROCESS_NODE_LINER();
	~PROCESS_NODE_LINER();
	void create(PROCESS_NODE_MANAGER* processNodeManager, CONTAINER* c, DRAWER::DRAWERS_SHADER* drawers);
	//�w��̃R�l�N�^�[��I��
	void overlapConnectorIn(PROCESS_NODE_CONNECTOR_IN* connectorIn);
	//�w��̃R�l�N�^�[��I���I��
	void overlapEndConnectorIn(PROCESS_NODE_CONNECTOR_IN* connectorIn);
	//�}�E�X�h���b�O��
	void mouseDragUpdate(const VECTOR2& pos);
	//�ڑ��J�n�R�l�N�^�[��ݒ�
	void selectProcessNode(PROCESS_NODE_CONNECTOR_OUT* connectorOut);
	//�ڑ��I��
	void selectReleaseProcessNode();
	//�ڑ��m��
	void decisionProcessNode(PROCESS_NODE_CONNECTOR_IN* connectorIn);
	//�R�l�N�^���m��ڑ�����
	void connect(PROCESS_NODE_CONNECTOR_OUT* connectorOut,PROCESS_NODE_CONNECTOR_IN* connectorIn);
	//processNode�Ɍq�����Ă���ڑ���S�Đ؂�
	void disconnect(PROCESS_NODE* processNode);
	//connectorIn�Ɍq�����Ă���ڑ���S�Đ؂�
	void disconnect(PROCESS_NODE_CONNECTOR_IN* connectorIn);
	//connectorOut�Ɍq�����Ă���ڑ���S�Đ؂�
	void disconnect(PROCESS_NODE_CONNECTOR_OUT* connectorOut);

private:
	PROCESS_NODE_MANAGER* ProcessNodeManager = nullptr;
	//���q�����̕\��
	NODE_LINE NodeLine;
	//����������̃}�E�X���W
	VECTOR2 MousePos;
	//��������OUT�R�l�N�^�[
	PROCESS_NODE_CONNECTOR_OUT* SelectedConnectOut = nullptr;
	//�q�����Ƃ���IN�R�l�N�^�[
	PROCESS_NODE_CONNECTOR_IN* SelectedConnectIn = nullptr;
	//��
	SOUND* SoundLineConnect = nullptr;
};

