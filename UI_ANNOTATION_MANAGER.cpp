#include "../Library/INDEV.h"
#include "../Library/GRAPHIC.h"
#include "../Library/STRING_TREE.h"
#include "../Library/STRING_TREE_SL.h"
#include "../Library/STATIC_FONT.h"
#include "../Library/CONTAINER.h"
#include "COMMON_DATA.h"
#include "COLLISION2D_POINT.h"
#include "INPUT_COMMON.h"
#include "UI.h"
#include "UI_ANNOTATION_MANAGER.h"
UI_ANNOTATION_MANAGER::UI_ANNOTATION_MANAGER(){
}

UI_ANNOTATION_MANAGER::~UI_ANNOTATION_MANAGER() {
}

void UI_ANNOTATION_MANAGER::init(COMMON_DATA* commonData){
	Font = commonData->staticFont();
	AnnotationFrame = 25;
	AnnotationFontSize = 32;
	StringOffsetPos = VECTOR2(8.0f, 8.0f);
	AnnotationBack.setTexture(commonData->c()->texture("uiAnnotationBack"));
}

void UI_ANNOTATION_MANAGER::setRootUi(UI* rootUi){
	RootUi = rootUi;
}

void UI_ANNOTATION_MANAGER::setOverlapAnnotation(const UI_ANNOTATION& overlapAnnotation){
	OverlapAnnotation = overlapAnnotation;
}

void UI_ANNOTATION_MANAGER::update(){
	INDEV* indev = INDEV::instance();
	//マウスが動いていない時間をカウント
	if (INPUT_COMMON::MouseRelativeValue(indev).isZero()) {
		NotMovingMouseFrameCnt++;
	}
	else {
		NotMovingMouseFrameCnt = 0;
	}
	//マウスが一定時間動かなかったら重なっているUIの説明を表示
	if (NotMovingMouseFrameCnt > AnnotationFrame) {
		UI* overlapUi = nullptr;
		COLLISION2D_POINT mousePoint;
		mousePoint.setPos(INPUT_COMMON::MousePosition(indev));
		RootUi->OverlapUi(&mousePoint, overlapUi);
		if (overlapUi != nullptr) {
			setOverlapAnnotation(*overlapUi->annotation());
		}
		else{
			setOverlapAnnotation(UI_ANNOTATION());
		}
	}
	else {
		setOverlapAnnotation(UI_ANNOTATION());
	}
}

void UI_ANNOTATION_MANAGER::draw(SHADER* shader){
	GRAPHIC* g = GRAPHIC::instance();
	if (!OverlapAnnotation.isEmpty()) {
		INDEV* indev = INDEV::instance();
		VECTOR2 mousePos = INPUT_COMMON::MousePosition(indev);
		if (mousePos.x + AnnotationBack.actualWh().x > g->baseWidth()) {
			mousePos.x = g->baseWidth() - AnnotationBack.actualWh().x;
		}
		if (mousePos.y + AnnotationBack.actualWh().y > g->baseHeight()) {
			mousePos.y = g->baseHeight() - AnnotationBack.actualWh().y;
		}
		AnnotationBack.setPos(mousePos);
		AnnotationBack.draw(shader);
		Font->draw(shader, OverlapAnnotation.annotationString().c_str(), mousePos+StringOffsetPos, VECTOR2(AnnotationFontSize, AnnotationFontSize));
	}
}

