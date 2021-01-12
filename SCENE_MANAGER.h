#pragma once
#include <stack>
#include "SAVE_DATA.h"
#include "STAGE_DATA.h"
#include "SETTING.h"
#include "FADE.h"
#include "COMMON_DATA.h"
class SCENE;
class STATIC_FONT;
class SCENE_MANAGER {
public:
    SCENE_MANAGER();
    ~SCENE_MANAGER();
    void create();
    void proc();
    void setNextScene(SCENE* gameState);
    void pushNextScene(SCENE* gameState);
    void backScene();
    FADE* fade() { return Fade; }
    COMMON_DATA* commonData() { return &CommonData; }
private:
    std::stack<SCENE*> CurrentScene;
    FADE* Fade = nullptr;
    COMMON_DATA CommonData;
};
