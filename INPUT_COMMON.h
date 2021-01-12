#pragma once
#include "../Library/SINGLETON.h"
class INDEV;
class VECTOR2;
class VECTOR3;
class INPUT_COMMON{
public:
	//�}�E�X�|�C���^��x�ړ���
	static float MouseRelativeValueX(INDEV* in);
	//�}�E�X�|�C���^��y�ړ���
	static float MouseRelativeValueY(INDEV* in);
	//�}�E�X�|�C���^�̈ړ���
	static VECTOR2 MouseRelativeValue(INDEV* in);
	//�}�E�X�|�C���^��x���W
	static float MousePositionX(INDEV* in);
	//�}�E�X�|�C���^��y���W
	static float MousePositionY(INDEV* in);
	//�}�E�X�|�C���^�̍��W
	static VECTOR2 MousePosition(INDEV* in);

	static VECTOR3 Debug3dObjectMove(INDEV* in);
};

