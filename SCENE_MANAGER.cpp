#include"../Library/common.h"
#include"../Library/CONTAINER.h"
#include "../Library/STATIC_FONT.h"
#include "createAssets.h"
#include "LOAD_DISP.h"
#include "SCENE.h"
#include "SCENE_FACTORY.h"
#include "SOUND_MANAGER.h"
#include "SCENE_MANAGER.h"
SCENE_MANAGER::SCENE_MANAGER(){
}
SCENE_MANAGER::~SCENE_MANAGER(){
    while (!CurrentScene.empty()){
        SAFE_DELETE(CurrentScene.top());
        CurrentScene.pop();
    } 
    SAFE_DELETE(Fade);
}
void SCENE_MANAGER::create(){
    CommonData.create();
    //シーンに共通データをセット
    SCENE::CommonData = &CommonData;
    SCENE::C = CommonData.c();
    SCENE::Font = CommonData.staticFont();
    SCENE::Image2d = CommonData.image2dShader();
    SCENE::SoftShadow = CommonData.softShadowShader();
    Fade = new FADE(CommonData.c());
    //最初のゲームステート
    CurrentScene.push(SCENE_FACTORY::instanceTitle(this));
}
void SCENE_MANAGER::proc(){
    CurrentScene.top()->proc();
    SOUND_MANAGER::instance()->update();
}

void SCENE_MANAGER::setNextScene(SCENE* gameState){
    SAFE_DELETE(CurrentScene.top());
    CurrentScene.pop();
    CurrentScene.push(gameState);
}
void SCENE_MANAGER::pushNextScene(SCENE* gameState){
    CurrentScene.push(gameState);
}
void SCENE_MANAGER::backScene(){
    if (CurrentScene.size()>=2) {
        SAFE_DELETE(CurrentScene.top());
        CurrentScene.pop();
    }
}
    