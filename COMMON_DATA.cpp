#include"../Library/common.h"
#include"../Library/CONTAINER.h"
#include "../Library/IMAGE_2D.h"
#include "../Library/SOFT_SHADOW.h"
#include "../Library/STATIC_FONT.h"
#include "LOAD_DISP.h"
#include "SOUND_MANAGER.h"
#include "COMMON_DATA.h"
COMMON_DATA::COMMON_DATA() {
}

COMMON_DATA::~COMMON_DATA() {
    SAFE_DELETE(Image2dShader);
    SAFE_DELETE(SoftShadowShader);
    SAFE_DELETE(StaticFont);
    SAFE_DELETE(C);
}

void COMMON_DATA::create(){
    C = new CONTAINER(CONTAINER::LOAD_FROM_FILE_THREAD, "Assets/COMMON/Assets.txt");
    LOAD_DISP loadDisp{ C };
    loadDisp.startProc();
    StaticFont = new STATIC_FONT(C->data("staticFontSize"), C->data("staticFontFileName"), C->data("staticFontName"), "");
    Image2dShader = new IMAGE_2D();
    SoftShadowShader = new SOFT_SHADOW(2048, 2048);
    Setting.create(C);
    Setting.load(C);
    SOUND_MANAGER::instance()->load(&Setting);
}
