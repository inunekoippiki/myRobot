#include "../Library/STRING_TREE.h"
#include "PROCESS_NODE_WINDOW_OPERATOR.h"
PROCESS_NODE_WINDOW_OPERATOR::PROCESS_NODE_WINDOW_OPERATOR() {

}

PROCESS_NODE_WINDOW_OPERATOR::~PROCESS_NODE_WINDOW_OPERATOR() {
}

void PROCESS_NODE_WINDOW_OPERATOR::create(STRING_TREE* windowOperatorData){
	DefaultZoomLevel = windowOperatorData->atw("initZoomLevel")->toInt();
	ZoomLevel = DefaultZoomLevel;
	STRING_TREE* zoomListTree = windowOperatorData->atw("zoomList");
	ZoomList.reserve(zoomListTree->childs().size());
	for (auto i : zoomListTree->childs()) {
		ZoomList.push_back(i->toFloat());
	}
	ScrollSpeed = windowOperatorData->atw("scrollSpeed")->toFloat();
}

void PROCESS_NODE_WINDOW_OPERATOR::resetZoomLevel(){
	ZoomLevel = DefaultZoomLevel;
}

float PROCESS_NODE_WINDOW_OPERATOR::zoomInitValueZoom(){
	return ZoomList[DefaultZoomLevel];
}

float PROCESS_NODE_WINDOW_OPERATOR::zoomIn(){
	float old = ZoomList[ZoomLevel];
	ZoomLevel++;
	ZoomLevel = min(ZoomLevel, (int)ZoomList.size() - 1);
	return  ZoomList[ZoomLevel] - old;
}

float PROCESS_NODE_WINDOW_OPERATOR::zoomOut(){
	float old = ZoomList[ZoomLevel];
	ZoomLevel--;
	ZoomLevel = max(ZoomLevel, 0);
	return  ZoomList[ZoomLevel]-old;
}


VECTOR2 PROCESS_NODE_WINDOW_OPERATOR::moveAmount(const VECTOR2& move){
	return move * ScrollSpeed;
}
