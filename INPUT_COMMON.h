#pragma once
#include "../Library/SINGLETON.h"
class INDEV;
class VECTOR2;
class VECTOR3;
class INPUT_COMMON{
public:
	//マウスポインタのx移動量
	static float MouseRelativeValueX(INDEV* in);
	//マウスポインタのy移動量
	static float MouseRelativeValueY(INDEV* in);
	//マウスポインタの移動量
	static VECTOR2 MouseRelativeValue(INDEV* in);
	//マウスポインタのx座標
	static float MousePositionX(INDEV* in);
	//マウスポインタのy座標
	static float MousePositionY(INDEV* in);
	//マウスポインタの座標
	static VECTOR2 MousePosition(INDEV* in);

	static VECTOR3 Debug3dObjectMove(INDEV* in);
};

