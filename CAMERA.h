#pragma once
#include "../Library/MATRIX.h"
#include "../Library/VECTOR3.h"
class SHADER;
class CAMERA{
public:
	CAMERA();
	virtual ~CAMERA();
	virtual void update() = 0;
	void shaderUpdate(SHADER* shader);
	VECTOR3 pos()const;
	//���[���h���W���X�N���[�����W�ɕϊ�
	VECTOR2 worldToScreenPoint(VECTOR3 point, float& out_z);
	//���[���h���W���X�N���[�����W�ɕϊ�
	VECTOR2 worldToScreenPoint(const VECTOR3& point);
	//�X�N���[�����W�����[���h���W�ɕϊ�
	VECTOR3 screenToWorldPoint(const VECTOR2& point, float z);
protected:
	MATRIX View;
	MATRIX Proj;
	VECTOR3 Pos;
private:
};

