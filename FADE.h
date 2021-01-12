#pragma once
#include"../Library/COLOR.h"
#include"../Library/TEXTURE.h"
#include"../Library/VECTOR2.h"
class SHADER;
class FADE {
public:
    FADE(class CONTAINER* c);
    ~FADE();
    void create(CONTAINER* c);
    void inTrigger();
    void outTrigger();
    void draw(SHADER* shader);
    int outEndFlag();
    int inEndFlag();
    void setSpeed(float speed);
private:
    enum class STATE {
        IN_TRIGGER, IN_NOW, IN_END,
        OUT_TRIGGER, OUT_NOW, OUT_END
    };
    STATE State;
    TEXTURE Texture;
    VECTOR2 Pos;
    COLOR Color;
    float Speed;//フェードスピード
};