#include "../Library/INDEV.h"
#include "../Library/CONTAINER.h"
#include "UI.h"
#include "UI_FACTORY.h"
#include "DRAWER_ARROW.h"
#include "DRAWER.h"
#include "DRAWERS_SHADER.h"
#include "INPUT_COMMON.h"
#include "PROCESS_NODE_MANAGER.h"
#include "NODE_LINE.h"
NODE_LINE::NODE_LINE(){
}


NODE_LINE::~NODE_LINE() {
	Drawer->Delete();
}

void NODE_LINE::create(DRAWER::DRAWERS_SHADER* drawers, CONTAINER* c, PROCESS_NODE_MANAGER* processNodeManager) {
	ProcessNodeManager = processNodeManager;
	Drawer = new DRAWER::ARROW(&Points, &Num);
	Drawer->setTexture(c->texture("oneDot"));
	Drawer->setTextureEnd(c->texture("arrow"));
	drawers->add(Drawer);
	for (int i = 0;i < LinePoint.size();i++) {
		LinePoint[i].create(c, i + 1, Points[i + 1], this, processNodeManager);
	}
}

void NODE_LINE::noneLine(){
	Num = 0;
	for (int i = 0;i < LinePoint.size();i++) {
		LinePoint[i].setIsDisable(true);
	}
}

void NODE_LINE::pointsUpdate(const VECTOR2& s, const VECTOR2& e){
	Points[0] = s;
	if (e.x - s.x > 0.0f) {
		float w = (e.x - s.x) * 0.5f;
		Points[1] = s;
		Points[2] = e;
		Points[1].x += w;
		Points[2].x -= w;
		Points[1].y = s.y;
		Points[2].y = e.y;
		Points[3] = e;
		Num = 4;
	}
	else{
		float bendLength = BendLength * ProcessNodeManager->processNodeListUi()->scale().x;
		Points[5] = e;
		Points[1] = s;
		Points[1].x += bendLength;
		Points[4] = e;
		Points[4].x -= bendLength;
		Points[2] = Points[1];
		Points[3] = Points[4];
		float w = (Points[4].y - Points[1].y) * 0.5f;
		Points[2].y += w;
		Points[3].y -= w;
		Num = 6;
	}
	linePointUpdate();
}

void NODE_LINE::pointsUpdate(int movePointIdx, const VECTOR2& p){
	if (Num == 4) {
		switch (movePointIdx){
		case 1:
			Points[movePointIdx].x = p.x;
			Points[movePointIdx + 1].x = p.x;
			break;
		case 2:
			Points[movePointIdx].x = p.x;
			Points[movePointIdx - 1].x = p.x;
			break;
		default:
			break;
		}
	}
	else{
		switch (movePointIdx) {
		case 1:
			Points[movePointIdx].x = p.x;
			Points[movePointIdx + 1].x = p.x;
			break;
		case 2:
			Points[movePointIdx] = p;
			Points[movePointIdx + 1].y = p.y;
			Points[movePointIdx - 1].x = p.x;
			break;
		case 3:
			Points[movePointIdx] = p;
			Points[movePointIdx + 1].x = p.x;
			Points[movePointIdx - 1].y = p.y;
			break;
		case 4:
			Points[movePointIdx].x = p.x;
			Points[movePointIdx - 1].x = p.x;
			break;
		default:
			break;
		}
	}
}

void NODE_LINE::pointsUpdate(const VECTOR2& s, const VECTOR2& e, float w, float h){
	Points[0] = s;
	if (e.x - s.x > 0.0f) {
		float xLen = (e.x - s.x);
		Points[1] = s;
		Points[2] = e;
		Points[1].x += xLen * w;
		Points[2].x -= xLen *(1.0f-w);
		Points[1].y = s.y;
		Points[2].y = e.y;
		Points[3] = e;
		Num = 4;
	}
	else {
		float bendLength = BendLength * ProcessNodeManager->processNodeListUi()->scale().x;
		Points[5] = e;
		Points[1] = s;
		Points[1].x += bendLength;
		Points[4] = e;
		Points[4].x -= bendLength;
		Points[2] = Points[1];
		Points[3] = Points[4];
		float yLen = (Points[4].y - Points[1].y);
		Points[2].y += yLen *h ;
		Points[3].y -= yLen* (1.0f-h);
		Num = 6;
	}
	linePointUpdate();
}


void NODE_LINE::pointsUpdate(int num,const std::array<VECTOR2, 6>& localPoints){
	Num = num;
	UI* layer = ProcessNodeManager->processNodeListUi();
	for (int i = 0;i < num;i++) {
		Points[i] = layer->localPosToWorldPos(localPoints[i]);
	}
	if (Num == 0) {
		noneLine();
	}
	else {
		linePointUpdate();
	}
}

void NODE_LINE::movePoints(const VECTOR2& s, const VECTOR2& e){
	VECTOR2 v = s - Points[0];
	for (int i = 0;i < Num;i++) {
		Points[i] += v;
	}
	linePointUpdate();
}

void NODE_LINE::rescalePoints(const VECTOR2& s, const VECTOR2& e) {
	float sx = (s.x - e.x) / (Points[0].x - Points[Num - 1].x);
	for (int i = 1;i < Num;i++) {
		float v = Points[i].x - Points[0].x;
		Points[i].x = s.x + v * sx;
	}
	Points[0].x = s.x;
	float sy = (s.y - e.y) / (Points[0].y - Points[Num - 1].y);
	for (int i = 1;i < Num;i++) {
		float v = Points[i].y - Points[0].y;
		if (Points[0].y - Points[Num - 1].y==0.0f) {
			Points[i].y = s.y;
		}
		else{
			Points[i].y = s.y + v * sy;
		}
	}
	Points[0].y = s.y;
	linePointUpdate();
}

void NODE_LINE::linePointUpdate(){
	for (int i = 0;i < LinePoint.size();i++) {
		if(i < Num - 2) {
			LinePoint[i].setUiPos(Points[i+1]);
			LinePoint[i].setIsDisable(false);
		}
		else{
			LinePoint[i].setIsDisable(true);
		}
	}
}

void NODE_LINE::setLineWidth(float lineWidth){
	Drawer->setLineWidth(lineWidth);
}

void NODE_LINE::setLinePointParent(UI* linePointParentUi){
	//以前属していた親から離脱
	if (LinePointParentUi != nullptr) {
		for (auto& i : LinePoint) {
			LinePointParentUi->removeChilds(i.rootUi());
		}
	}
	LinePointParentUi=linePointParentUi;
	//新しい親に属す
	if (LinePointParentUi != nullptr) {
		for (auto& i : LinePoint) {
			LinePointParentUi->addChilds(i.rootUi());
		}
	}
}

//ワールド座標に変換した点を返す
std::array<VECTOR2, 6> NODE_LINE::localPoints() {
	std::array<VECTOR2, 6> p;
	UI* layer = ProcessNodeManager->processNodeListUi();
	for (int i = 0;i < Num;i++) {
		p[i] = layer->worldPosToLocalPos(Points[i]);
	}
	return p;
}



