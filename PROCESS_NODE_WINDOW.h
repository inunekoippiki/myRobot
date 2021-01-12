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
	//ウィンドウ操作関連のUI
	UI* cameraOperationUi() { return CameraOperationUi; }
	//プロセスノードが入るレイヤー
	UI* processNodeListUi() { return ProcessNodeListUi; }
	//制御点が入るレイヤー
	UI* processNodeLinePointListUi() {return ProcessNodeLinePointListUi;}
private:
	//ウィンドウで押下
	void onDownWindow();
	//ウィンドウドラッグ中
	void onDragWindow();
	//ウィンドウから離した
	void onUpWindow();
	//Scrollの真ん中を押下した時
	void onDownCameraButton();
	//Scrollの真ん中ドラッグ中
	void onDragCameraButton();

	//ノード同士を繋ぐ線の更新
	void addProcessNodeLineUpdate();
	//倍率を変更する
	void designWindowZoom(float scaleAmount, const VECTOR2& localCenter);
	//倍率を上げる
	void designWindowZoomIn();
	//倍率を下げる
	void designWindowZoomOut();
	//スクロールさせる
	void designWindowMove(const VECTOR2& moveAmount);
	//マウスが端にあるときその方向にスクロールさせる
	void autoDesignWindowMove();

	//参照オブジェクト
	PROCESS_NODE_MANAGER* ProcessNodeManager = nullptr;
	PROCESS_NODE_SELECTOR* ProcessNodeSelector = nullptr;
	//ウィンドウ操作用
	PROCESS_NODE_WINDOW_OPERATOR ProcessNodeWindowOperator;
	VECTOR2 MouseDownPos;
	//プロセスノードが入るレイヤー
	UI* ProcessNodeListUi = nullptr;
	//プロセスノードをつなぐ線の制御点が入るレイヤー
	UI* ProcessNodeLinePointListUi = nullptr;

	//親
	UI* CameraOperationUi = nullptr;

	//各ボタンUI
	UI* CameraScrollCenterUi = nullptr;
	UI* CameraScrollUpUi = nullptr;
	UI* CameraScrollDownUi = nullptr;
	UI* CameraScrollLeftUi = nullptr;
	UI* CameraScrollRightUi = nullptr;
	UI* CameraZoomInUi = nullptr;
	UI* CameraZoomOutUi = nullptr;
};

