#pragma once
#include<vector>
class SCENE_MANAGER;
class COMMON_DATA;
class CONTAINER;
class STATIC_FONT;
class IMAGE_2D;
class SOFT_SHADOW;
class SCENE {
public:
    SCENE() {};
    virtual ~SCENE() {};
    virtual void proc() = 0;
protected:
    static COMMON_DATA* commonData();
    static CONTAINER* c();
    static STATIC_FONT* font();
    static IMAGE_2D* image2d();
    static SOFT_SHADOW* softShadow();
private:
    friend SCENE_MANAGER;
    static COMMON_DATA* CommonData;
    static CONTAINER* C;
    static STATIC_FONT* Font;
    static IMAGE_2D* Image2d;
    static SOFT_SHADOW* SoftShadow;
};

