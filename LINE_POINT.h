#pragma once
#include "../Library/VECTOR2.h"
class CONTAINER;
class UI;
class NODE_LINE;
class PROCESS_NODE_MANAGER;
class LINE_POINT {
public:
	LINE_POINT();
	void create(CONTAINER* c, int pointIdx,const VECTOR2& pos, NODE_LINE* nodeLine, PROCESS_NODE_MANAGER* processNodeManager);
	~LINE_POINT();
	UI* rootUi() { return RootUi; }
	//UI�̈ʒu�𒼐ڍX�V
	void setUiPos(const VECTOR2& pos);
	//����_�̈ʒu��ݒ�
	void setPos(const VECTOR2& pos);
	//����_�𓮂���
	void move(const VECTOR2& v);
	//��\���\��
	void setIsDisable(bool isDisable);
private:
	VECTOR2 uiPos()const;
	void onDown();
	void onDragUpdate();
	void onDragEnd();
	PROCESS_NODE_MANAGER* ProcessNodeManager = nullptr;
	//���p��
	NODE_LINE* NodeLine = nullptr;
	//UI
	UI* RootUi = nullptr;
	//���Ԗڂ̐���_��
	int PointIdx = 0;
	//�O�̈ʒu�ꎞ�ۑ��p
	VECTOR2 OldPos;
};
