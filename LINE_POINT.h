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
	//UIの位置を直接更新
	void setUiPos(const VECTOR2& pos);
	//制御点の位置を設定
	void setPos(const VECTOR2& pos);
	//制御点を動かす
	void move(const VECTOR2& v);
	//非表示表示
	void setIsDisable(bool isDisable);
private:
	VECTOR2 uiPos()const;
	void onDown();
	void onDragUpdate();
	void onDragEnd();
	PROCESS_NODE_MANAGER* ProcessNodeManager = nullptr;
	//利用元
	NODE_LINE* NodeLine = nullptr;
	//UI
	UI* RootUi = nullptr;
	//何番目の制御点か
	int PointIdx = 0;
	//前の位置一時保存用
	VECTOR2 OldPos;
};
