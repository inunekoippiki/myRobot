#pragma once
class TEXTURE;
class UI;
class PROCESS_NODE;
class PROCESS_NODE_MANAGER;
class PROCESS_NODE_FRAME{
public:
	PROCESS_NODE_FRAME();
	~PROCESS_NODE_FRAME();
	void create(PROCESS_NODE* owner, TEXTURE* texture, PROCESS_NODE_MANAGER* processNodeManager);
	UI* rootUi() { return RootUi; }
private:
	void onDown();
	void onDragEnd();
	void onDrag();

	PROCESS_NODE_MANAGER* ProcessNodeManager = nullptr;
	//���p��
	PROCESS_NODE* Owner = nullptr;
	UI* RootUi = nullptr;
	//�O�̈ʒu�ꎞ�ۑ��p
	VECTOR2 OldPos;
};

