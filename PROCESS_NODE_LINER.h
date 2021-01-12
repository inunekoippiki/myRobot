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
//プロセスノードのコネクターを繋げる
class PROCESS_NODE_LINER{
public:
	PROCESS_NODE_LINER();
	~PROCESS_NODE_LINER();
	void create(PROCESS_NODE_MANAGER* processNodeManager, CONTAINER* c, DRAWER::DRAWERS_SHADER* drawers);
	//指定のコネクターを選択中
	void overlapConnectorIn(PROCESS_NODE_CONNECTOR_IN* connectorIn);
	//指定のコネクターを選択終了
	void overlapEndConnectorIn(PROCESS_NODE_CONNECTOR_IN* connectorIn);
	//マウスドラッグ中
	void mouseDragUpdate(const VECTOR2& pos);
	//接続開始コネクターを設定
	void selectProcessNode(PROCESS_NODE_CONNECTOR_OUT* connectorOut);
	//接続終了
	void selectReleaseProcessNode();
	//接続確定
	void decisionProcessNode(PROCESS_NODE_CONNECTOR_IN* connectorIn);
	//コネクタ同士を接続する
	void connect(PROCESS_NODE_CONNECTOR_OUT* connectorOut,PROCESS_NODE_CONNECTOR_IN* connectorIn);
	//processNodeに繋がっている接続を全て切る
	void disconnect(PROCESS_NODE* processNode);
	//connectorInに繋がっている接続を全て切る
	void disconnect(PROCESS_NODE_CONNECTOR_IN* connectorIn);
	//connectorOutに繋がっている接続を全て切る
	void disconnect(PROCESS_NODE_CONNECTOR_OUT* connectorOut);

private:
	PROCESS_NODE_MANAGER* ProcessNodeManager = nullptr;
	//線繋ぎ中の表示
	NODE_LINE NodeLine;
	//押下した後のマウス座標
	VECTOR2 MousePos;
	//押下したOUTコネクター
	PROCESS_NODE_CONNECTOR_OUT* SelectedConnectOut = nullptr;
	//繋ごうとしたINコネクター
	PROCESS_NODE_CONNECTOR_IN* SelectedConnectIn = nullptr;
	//音
	SOUND* SoundLineConnect = nullptr;
};

