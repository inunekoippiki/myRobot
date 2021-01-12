#pragma once
namespace DRAWER {
	class DRAWERS_SHADER;
	class IMAGE2D;
}
class UI;
class PROCESS_NODE;
class CONTAINER;
class NODE_LINE;
class PROCESS_NODE_MANAGER;
class PROCESS_NODE_LINER;
class PROCESS_NODE_CONNECTOR_OUT;
//�R�l�N�^�̐F��ς���邽�߂̃^�O
enum class PROCESS_NODE_CONNECTOR_TYPE {
	THEN, ELSE
};
//�v���Z�X�m�[�h�̓����Ă�����̃R�l�N�^�B
//�q�����Ă���out�R�l�N�^�[��ێ�����
class PROCESS_NODE_CONNECTOR_IN{
public:

	PROCESS_NODE_CONNECTOR_IN(CONTAINER* c, PROCESS_NODE* processNode, PROCESS_NODE_LINER* processNodeLiner);
	PROCESS_NODE_CONNECTOR_IN(PROCESS_NODE_CONNECTOR_TYPE type,CONTAINER* c, PROCESS_NODE* processNode, PROCESS_NODE_LINER* processNodeLiner);
	~PROCESS_NODE_CONNECTOR_IN();
	UI* rootUi() { return RootUi; }
	//���p���m�[�h
	PROCESS_NODE* processNode() { return ProcessNode; }
	//�ڑ���Out�m�[�h
	PROCESS_NODE_CONNECTOR_OUT* connectorFront() { return ConnectorFront; }
	//�ڑ�����
	void setConnectorFront(PROCESS_NODE_CONNECTOR_OUT* connectorFront);
private:
	void create(DRAWER::IMAGE2D* drawer);
	PROCESS_NODE_LINER* ProcessNodeLiner = nullptr;
	//���p��
	PROCESS_NODE* ProcessNode = nullptr;
	//UI
	UI* RootUi = nullptr;
	//�ڑ���Out�m�[�h
	PROCESS_NODE_CONNECTOR_OUT* ConnectorFront = nullptr;
};

//�v���Z�X�m�[�h�̏o�Ă������̃R�l�N�^
//�q�����Ă���in�R�l�N�^�[��ێ�����
class PROCESS_NODE_CONNECTOR_OUT {
public:
	PROCESS_NODE_CONNECTOR_OUT(
		CONTAINER* c,
		PROCESS_NODE* processNode,
		DRAWER::DRAWERS_SHADER* lineDrawers,
		PROCESS_NODE_LINER* processNodeLiner,
		PROCESS_NODE_MANAGER* processNodeManager);
	PROCESS_NODE_CONNECTOR_OUT(
		PROCESS_NODE_CONNECTOR_TYPE type,
		CONTAINER* c, 
		PROCESS_NODE* processNode, 
		DRAWER::DRAWERS_SHADER* lineDrawers,
		PROCESS_NODE_LINER* processNodeLiner, 
		PROCESS_NODE_MANAGER* processNodeManager);
	~PROCESS_NODE_CONNECTOR_OUT();
	UI* rootUi() { return RootUi; }
	//���p���m�[�h
	PROCESS_NODE* processNode() { return ProcessNode; }
	//�ڑ���In�m�[�h
	PROCESS_NODE_CONNECTOR_IN* cnnectorNext() { return ConnectorNext; }
	//��
	NODE_LINE* nodeLine() { return NodeLine; }
	//�ڑ�����
	void setConnectorNext(PROCESS_NODE_CONNECTOR_IN* connectorNext);
	//�����v�Z������
	void updateLine();
	//���𕽍s�ړ�
	void moveLine();
	//���̃X�P�[���ύX
	void rescaleLine();
private:
	void onDown();
	void onDragUpdate();
	void onDragEnd();
	void create(DRAWER::IMAGE2D* drawer, CONTAINER* c, DRAWER::DRAWERS_SHADER* lineDrawers, PROCESS_NODE_MANAGER* processNodeManager);
	PROCESS_NODE_LINER* ProcessNodeLiner = nullptr;
	//���p���m�[�h
	PROCESS_NODE* ProcessNode = nullptr;
	//UI
	UI* RootUi = nullptr;
	//�ڑ���In�m�[�h
	PROCESS_NODE_CONNECTOR_IN* ConnectorNext = nullptr;
	//��
	NODE_LINE* NodeLine = nullptr;
};
