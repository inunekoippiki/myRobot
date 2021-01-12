#pragma once
#include <array>
#include "../Library/TEXTURE.h"
#include "../Library/VECTOR2.h"
#include "LINE_POINT.h"
namespace DRAWER {
	class DRAWERS_SHADER;
	class BASE;
	class ARROW;
}
class DRAWER_ARROW;
class SHADER;
class UI;
class CONTAINER;
class PROCESS_NODE_MANAGER;
class NODE_LINE {
public:
	NODE_LINE();
	~NODE_LINE();
	void create(DRAWER::DRAWERS_SHADER* drawers, CONTAINER* c, PROCESS_NODE_MANAGER* processNodeManager);
	//����_���\���ɂ���
	void noneLine();
	//2�_���琧��_���v�Z���X�V����
	void pointsUpdate(const VECTOR2& s, const VECTOR2& e);
	//1�_���w�肵�Đ���_���X�V����
	void pointsUpdate(int movePointIdx, const VECTOR2& p);
	//2�_���琧��_���v�Z���X�V����(�Ȃ��钷���̊������w��ł���)
	void pointsUpdate(const VECTOR2& s, const VECTOR2& e,float w, float h);//wh�͋Ȃ���Ƃ��̊���
	//�S�Ă̐���_�𒼐ڍX�V����
	void pointsUpdate(int num,const std::array<VECTOR2, 6>& worldPoints);
	//�q�����Ă��鐧��_�𕽍s�ړ�������
	void movePoints(const VECTOR2& s, const VECTOR2& e);
	//����_�̃X�P�[����ύX����
	void rescalePoints(const VECTOR2& s, const VECTOR2& e);
	//����_���X�V����
	void linePointUpdate();
	//����_�̐�
	size_t num() { return Num; }
	//���̎n�_
	VECTOR2 stPoint() { return Points[0]; }
	//���̏I�_
	VECTOR2 edPoint() { return Points[Num - 1]; }
	//���̕\��
	DRAWER::ARROW* drawer() { return Drawer; }
	//�m�[�h�ɏd�Ȃ�Ȃ����߂̋Ȃ��钷����ݒ�
	void setBendLength(float bendLength) { BendLength = bendLength; }
	//��̑�����ݒ�
	void setLineWidth(float lineWidth);
	//����_��UI�̐e��ݒ�
	void setLinePointParent(UI* linePointParentUi);
	//�_��Ԃ�
	const std::array<VECTOR2, 6>& points() { return Points; }
	//���[�J�����W�ɕϊ������_��Ԃ�
	std::array<VECTOR2, 6> localPoints();
private:
	PROCESS_NODE_MANAGER* ProcessNodeManager = nullptr;
	//����_��������e
	UI* LinePointParentUi = nullptr;
	//�_
	std::array<VECTOR2, 6> Points;
	//�L���ȓ_�̐�
	size_t Num = 0;
	//����_
	std::array<LINE_POINT, 4> LinePoint;
	//���̕\��
	DRAWER::ARROW* Drawer = nullptr;
	//�m�[�h�ɔ��Ȃ��悤�ɋȂ��钷��
	float BendLength = 0.0f;
};

