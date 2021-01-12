#pragma once
#include <vector>
#include "../Library/VECTOR2.h"
class STRING_TREE;
class PROCESS_NODE_WINDOW_OPERATOR{
public:
	PROCESS_NODE_WINDOW_OPERATOR();
	~PROCESS_NODE_WINDOW_OPERATOR();
	void create(STRING_TREE* windowOperatorData);
	//ズームレベルをデフォルトに戻す
	void resetZoomLevel();
	//デフォルトのズームレベル倍率を返す
	float zoomInitValueZoom();
	//一段回ズームする
	float zoomIn();
	//一段回ズームアウトする
	float zoomOut();
	//今のズームレベルでのスクロール量補正
	VECTOR2 moveAmount(const VECTOR2& move);
private:
	//デフォルトのズームレベル
	int DefaultZoomLevel = 0;
	//現在のズームレベル
	int ZoomLevel = 0;
	//ズーム倍率のリスト
	std::vector<float> ZoomList;
	//スクロールスピード
	float ScrollSpeed = 0.0f;
};

