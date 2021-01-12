#include <cmath>
#include "../Library/VECTOR3.h"
#include "../Library/MATRIX.h"
#include "../Library/CONTAINER.h"
#include "../Library/TEXTURE.h"
#include "AXIS_DISP.h"
AXIS_DISP::AXIS_DISP() {
}

AXIS_DISP::~AXIS_DISP() {
}

void AXIS_DISP::create(CONTAINER* c){
	AxisXTexture = c->texture("axisXIcon");
	AxisYTexture = c->texture("axisYIcon");
	AxisZTexture = c->texture("axisZIcon");
	XTexture = c->texture("XIcon");
	YTexture = c->texture("YIcon");
	ZTexture = c->texture("ZIcon");
	LineLendth = 64.0f;
}

void AXIS_DISP::setPos(const VECTOR2& pos){
	Pos = pos;
}

void AXIS_DISP::update(const MATRIX& rotateMatrix){
	RotateMatrix = rotateMatrix;
}

void AXIS_DISP::draw(SHADER* shader){
	VECTOR2 xPos= Pos + (RotateMatrix * (VECTOR3(1.0f, 0.0f, 0.0f))).xy() * LineLendth * -1.0f;
	AxisXTexture->drawLine(shader, Pos, xPos);
	XTexture->draw(shader, xPos,0.0f);

	VECTOR2 yPos= Pos + (RotateMatrix * (VECTOR3(0.0f, 1.0f, 0.0f))).xy() * LineLendth * -1.0f;
	AxisYTexture->drawLine(shader, Pos, yPos);
	YTexture->draw(shader, yPos, 0.0f);

	VECTOR2 zPos= Pos + (RotateMatrix * (VECTOR3(0.0f, 0.0f, 1.0f))).xy() * LineLendth * -1.0f;
	AxisZTexture->drawLine(shader, Pos, zPos);
	ZTexture->draw(shader, zPos, 0.0f);

}
