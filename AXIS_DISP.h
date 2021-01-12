#pragma once
#include "../Library/VECTOR2.h"
class TEXTURE;
class CONTAINER;
class SHADER;
//座標軸を表示するクラス
class AXIS_DISP{
public:
	AXIS_DISP();
	~AXIS_DISP();
	void create(CONTAINER* c);
	//表示位置を設定する
	void setPos(const VECTOR2& pos);
	//カメラの回転行列で軸の向きを更新
	void update(const MATRIX& rotateMatrix);
	void draw(SHADER* shader);
private:
	VECTOR2 Pos;
	TEXTURE* AxisXTexture = nullptr;
	TEXTURE* AxisYTexture = nullptr;
	TEXTURE* AxisZTexture = nullptr;
	TEXTURE* XTexture = nullptr;
	TEXTURE* YTexture = nullptr;
	TEXTURE* ZTexture = nullptr;
	MATRIX RotateMatrix;
	float LineLendth = 0.0f;
};

