#pragma once
#include <vector>
#include "../Library/VECTOR2.h"
class STRING_TREE;
class PROCESS_NODE_WINDOW_OPERATOR{
public:
	PROCESS_NODE_WINDOW_OPERATOR();
	~PROCESS_NODE_WINDOW_OPERATOR();
	void create(STRING_TREE* windowOperatorData);
	//�Y�[�����x�����f�t�H���g�ɖ߂�
	void resetZoomLevel();
	//�f�t�H���g�̃Y�[�����x���{����Ԃ�
	float zoomInitValueZoom();
	//��i��Y�[������
	float zoomIn();
	//��i��Y�[���A�E�g����
	float zoomOut();
	//���̃Y�[�����x���ł̃X�N���[���ʕ␳
	VECTOR2 moveAmount(const VECTOR2& move);
private:
	//�f�t�H���g�̃Y�[�����x��
	int DefaultZoomLevel = 0;
	//���݂̃Y�[�����x��
	int ZoomLevel = 0;
	//�Y�[���{���̃��X�g
	std::vector<float> ZoomList;
	//�X�N���[���X�s�[�h
	float ScrollSpeed = 0.0f;
};

