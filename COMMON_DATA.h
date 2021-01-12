#pragma once
#include "SAVE_DATA.h"
#include "STAGE_DATA.h"
#include "SETTING.h"
class CONTAINER;
class STATIC_FONT;
class IMAGE_2D;
class SOFT_SHADOW;
class COMMON_DATA{
public:
	COMMON_DATA();
	~COMMON_DATA();
    void create();
    CONTAINER* c() {return C;}
    STATIC_FONT* staticFont() { return StaticFont; }
    SAVE_DATA* saveData() { return &SaveData; }
    IMAGE_2D* image2dShader(){ return Image2dShader; }
    SOFT_SHADOW* softShadowShader() { return SoftShadowShader; }
    STAGE_DATA* stageData() { return &StageData; }
    SETTING* setting() { return &Setting; }
private:
    CONTAINER* C = nullptr;
    STATIC_FONT* StaticFont = nullptr;
    IMAGE_2D* Image2dShader = nullptr;
    SOFT_SHADOW* SoftShadowShader = nullptr;
    SAVE_DATA SaveData;
    STAGE_DATA StageData;
    SETTING Setting;
};
