#pragma once
#include "../Library/VECTOR2.h"
class TEXTURE;
class CONTAINER;
class SHADER;
//���W����\������N���X
class AXIS_DISP{
public:
	AXIS_DISP();
	~AXIS_DISP();
	void create(CONTAINER* c);
	//�\���ʒu��ݒ肷��
	void setPos(const VECTOR2& pos);
	//�J�����̉�]�s��Ŏ��̌������X�V
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

