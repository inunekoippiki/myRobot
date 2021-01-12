#pragma once
#include "../Library/VECTOR2.h"
#include "DRAWER_IMAGE2D.h"
#include "UI_ANNOTATION.h"
class UI;
class STATIC_FONT;
class COMMON_DATA;
class SHADER;
class CONTAINER;
//UIに一定時間かざすと出てくる説明のマネージャー
class UI_ANNOTATION_MANAGER {
public:
	UI_ANNOTATION_MANAGER();
	~UI_ANNOTATION_MANAGER();
	void init(COMMON_DATA* commonData);
	void setRootUi(UI* rootUi);
	void setOverlapAnnotation(const UI_ANNOTATION& overlapAnnotation);
	void update();
	void draw(SHADER* shader);
private:
	UI* RootUi = nullptr;
	STATIC_FONT* Font = nullptr;
	DRAWER::IMAGE2D AnnotationBack;
	UI_ANNOTATION OverlapAnnotation;
	int AnnotationFrame = 0;
	int NotMovingMouseFrameCnt = 0;
	int AnnotationFontSize = 0;
	VECTOR2 StringOffsetPos;
};

