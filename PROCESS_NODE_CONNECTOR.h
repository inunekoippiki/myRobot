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
//コネクタの色を変えれるためのタグ
enum class PROCESS_NODE_CONNECTOR_TYPE {
	THEN, ELSE
};
//プロセスノードの入ってくる方のコネクタ。
//繋がっているoutコネクターを保持する
class PROCESS_NODE_CONNECTOR_IN{
public:

	PROCESS_NODE_CONNECTOR_IN(CONTAINER* c, PROCESS_NODE* processNode, PROCESS_NODE_LINER* processNodeLiner);
	PROCESS_NODE_CONNECTOR_IN(PROCESS_NODE_CONNECTOR_TYPE type,CONTAINER* c, PROCESS_NODE* processNode, PROCESS_NODE_LINER* processNodeLiner);
	~PROCESS_NODE_CONNECTOR_IN();
	UI* rootUi() { return RootUi; }
	//利用元ノード
	PROCESS_NODE* processNode() { return ProcessNode; }
	//接続中Outノード
	PROCESS_NODE_CONNECTOR_OUT* connectorFront() { return ConnectorFront; }
	//接続する
	void setConnectorFront(PROCESS_NODE_CONNECTOR_OUT* connectorFront);
private:
	void create(DRAWER::IMAGE2D* drawer);
	PROCESS_NODE_LINER* ProcessNodeLiner = nullptr;
	//利用元
	PROCESS_NODE* ProcessNode = nullptr;
	//UI
	UI* RootUi = nullptr;
	//接続中Outノード
	PROCESS_NODE_CONNECTOR_OUT* ConnectorFront = nullptr;
};

//プロセスノードの出ていく方のコネクタ
//繋がっているinコネクターを保持する
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
	//利用元ノード
	PROCESS_NODE* processNode() { return ProcessNode; }
	//接続中Inノード
	PROCESS_NODE_CONNECTOR_IN* cnnectorNext() { return ConnectorNext; }
	//線
	NODE_LINE* nodeLine() { return NodeLine; }
	//接続する
	void setConnectorNext(PROCESS_NODE_CONNECTOR_IN* connectorNext);
	//線を計算し直す
	void updateLine();
	//線を平行移動
	void moveLine();
	//線のスケール変更
	void rescaleLine();
private:
	void onDown();
	void onDragUpdate();
	void onDragEnd();
	void create(DRAWER::IMAGE2D* drawer, CONTAINER* c, DRAWER::DRAWERS_SHADER* lineDrawers, PROCESS_NODE_MANAGER* processNodeManager);
	PROCESS_NODE_LINER* ProcessNodeLiner = nullptr;
	//利用元ノード
	PROCESS_NODE* ProcessNode = nullptr;
	//UI
	UI* RootUi = nullptr;
	//接続中Inノード
	PROCESS_NODE_CONNECTOR_IN* ConnectorNext = nullptr;
	//線
	NODE_LINE* NodeLine = nullptr;
};
