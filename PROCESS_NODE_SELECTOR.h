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
	//collisionの範囲内のノードを選択
	void select(COLLISION2D* collision);
	//collisionの範囲内のノードを選択
	void select(const VECTOR2& localSt, const VECTOR2& localEd);
	//selectListのノードを選択
	void select(const std::vector<PROCESS_NODE*>& selectList);
	//前の選択がoldSelectListに入る
	void select(const std::vector<PROCESS_NODE*>& selectList, std::vector<PROCESS_NODE*>& oldSelectList);
	//新たに選択した際の更新
	void selectUpdate();
	//選択状態のオーバーレイの描画位置を更新する
	void drawerUpdate();
	//選択状態の線を更新
	void updateLine();
	//選択しているノードを削除する(trueで削除するものがない)
	bool removeSelectProcessNode();
	//選択しているノードの位置をx軸で揃える
	void AlignPosXSelectProcessNode();
	//選択しているノードの位置をy軸で揃える
	void AlignPosYSelectProcessNode();
	//選択状態のノードデータを文字列データにして保存
	void CopySelectProcessNode();
	//コピーされていた文字列データでノードを追加
	void processNodePaste();
	//ペースト（データ指定）
	void processNodePaste(const std::string& Data);
	//vは移動量
	void moveSelectProcessNode(const VECTOR2& v);
	//選択中のノードのリスト
	std::vector<PROCESS_NODE*>* selectList() { return &SelectList; }

private:
	//各ノードはBackの線しか持っていないので、Frontの線は前のノードから更新しないといけない。
	//選択中のBackノードの全てと検索してupdateされていないコネクターノードを探して更新する。
	void selectProcessNodeFrontLineUpdate(PROCESS_NODE_CONNECTOR_IN* nodeConnectorIn);
	//参照オブジェクト
	CONTAINER* Container = nullptr;
	STATIC_FONT* Font = nullptr;
	DRAWER::DRAWERS_SHADER* ProcessNodeSelectField = nullptr;
	DRAWER::DRAWERS_SHADER* ProcessNodeSelectRangeField = nullptr;
	PROCESS_NODE_MANAGER* ProcessNodeManager = nullptr;
	PROCESS_NODE_WINDOW* ProcessNodeWindow = nullptr;
	//マウスを押下した時の座標(ノードのレイヤーのローカル座標)
	VECTOR2 MouseDownWindowLocalPos;
	//マウスをドラッグ中の座標(ノードのレイヤーのローカル座標)
	VECTOR2 MouseWindowLocalPos;
	//選択範囲表示用
	DRAWER::IMAGE2D* SelectRangeDrawer = nullptr;
	//選択中のノードハイライト用
	std::vector <DRAWER::IMAGE2D*> SelectProcessNodeOverlay;
	//選択中のノードのリスト
	std::vector<PROCESS_NODE*> SelectList;
	//コピー中のデータ
	std::string CopyDataString;
};

