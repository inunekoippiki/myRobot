#pragma once
#include <array>
#include "../Library/TEXTURE.h"
#include "../Library/VECTOR2.h"
#include "LINE_POINT.h"
namespace DRAWER {
	class DRAWERS_SHADER;
	class BASE;
	class ARROW;
}
class DRAWER_ARROW;
class SHADER;
class UI;
class CONTAINER;
class PROCESS_NODE_MANAGER;
class NODE_LINE {
public:
	NODE_LINE();
	~NODE_LINE();
	void create(DRAWER::DRAWERS_SHADER* drawers, CONTAINER* c, PROCESS_NODE_MANAGER* processNodeManager);
	//制御点を非表示にする
	void noneLine();
	//2点から制御点を計算し更新する
	void pointsUpdate(const VECTOR2& s, const VECTOR2& e);
	//1点を指定して制御点を更新する
	void pointsUpdate(int movePointIdx, const VECTOR2& p);
	//2点から制御点を計算し更新する(曲げる長さの割合を指定できる)
	void pointsUpdate(const VECTOR2& s, const VECTOR2& e,float w, float h);//whは曲げるときの割合
	//全ての制御点を直接更新する
	void pointsUpdate(int num,const std::array<VECTOR2, 6>& worldPoints);
	//繋がっている制御点を平行移動させる
	void movePoints(const VECTOR2& s, const VECTOR2& e);
	//制御点のスケールを変更する
	void rescalePoints(const VECTOR2& s, const VECTOR2& e);
	//制御点を更新する
	void linePointUpdate();
	//制御点の数
	size_t num() { return Num; }
	//線の始点
	VECTOR2 stPoint() { return Points[0]; }
	//線の終点
	VECTOR2 edPoint() { return Points[Num - 1]; }
	//線の表示
	DRAWER::ARROW* drawer() { return Drawer; }
	//ノードに重ならないための曲げる長さを設定
	void setBendLength(float bendLength) { BendLength = bendLength; }
	//先の太さを設定
	void setLineWidth(float lineWidth);
	//制御点のUIの親を設定
	void setLinePointParent(UI* linePointParentUi);
	//点を返す
	const std::array<VECTOR2, 6>& points() { return Points; }
	//ローカル座標に変換した点を返す
	std::array<VECTOR2, 6> localPoints();
private:
	PROCESS_NODE_MANAGER* ProcessNodeManager = nullptr;
	//制御点が属する親
	UI* LinePointParentUi = nullptr;
	//点
	std::array<VECTOR2, 6> Points;
	//有効な点の数
	size_t Num = 0;
	//制御点
	std::array<LINE_POINT, 4> LinePoint;
	//線の表示
	DRAWER::ARROW* Drawer = nullptr;
	//ノードに被らないように曲げる長さ
	float BendLength = 0.0f;
};

