#include "../Library/GRAPHIC.h"
#include "../Library/CONTAINER.h"
#include "../Library/SHADER.h"
#include "FADE.h"
FADE::FADE(CONTAINER* c){
    create(c);
}
FADE::~FADE(){
}
void FADE::create(CONTAINER* c){
    const char* filename = c->data("fadeFilename");
    Texture.create(filename);
    Speed = c->data("fadeSpeed");
    Color = COLOR(
        c->data("fadeColorR"),
        c->data("fadeColorG"),
        c->data("fadeColorB")
    );
    State = STATE::OUT_END;

}
void FADE::inTrigger(){
    if (State == STATE::OUT_END) {
        State = STATE::IN_TRIGGER;
    }
}
void FADE::outTrigger(){
    if (State == STATE::IN_END) {
        State = STATE::OUT_TRIGGER;
    }
}
void FADE::draw(SHADER* shader){
    GRAPHIC* g = GRAPHIC::instance();
    switch (State) {
    case STATE::IN_TRIGGER:
        Color.a = 1.0f;
        Texture.draw(shader, Pos, Color);
        State = STATE::IN_NOW;
        break;
    case STATE::IN_NOW:
        Texture.draw(shader, Pos, Color);
        Color.a -= Speed;
        if (Color.a < 0.0) {
            Color.a = 0.0f;
            State = STATE::IN_END;
        }
        break;
    case STATE::IN_END:
        break;
    case STATE::OUT_TRIGGER:
        Color.a = 0.0f;
        State = STATE::OUT_NOW;
        break;
    case STATE::OUT_NOW:
        Texture.draw(shader, Pos, Color);
        Color.a += Speed;
        if (Color.a >= 1.0f) {
            Color.a = 1.0f;
            State = STATE::OUT_END;
        }
        break;
    case STATE::OUT_END:
        break;
    }
}
int FADE::inEndFlag(){
    return (State == STATE::IN_END);
}
int FADE::outEndFlag(){
    return (State == STATE::OUT_END);
}
void FADE::setSpeed(float speed){
    Speed = speed;
}

