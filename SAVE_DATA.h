#pragma once
#include "../Library/STRING_TREE.h"
struct SAVE_DATA_STAGE_FORMAT {
	int IsOpen = 0;
	int IsClear = 0;
};
class SAVE_DATA {
public:
	SAVE_DATA();
	~SAVE_DATA();
	//�e���E���h�f�[�^���������f�[�^
	STRING_TREE* dataTree() { return &DataTree; }
	//���ׂẴX�e�[�W�̐���Ԃ�
	int stageCnt();
	//���̃X�e�[�W���J������Ă��邩��Ԃ�
	bool isOpenStage(int idx)const;
	//���̃X�e�[�W���N���A����Ă��邩��Ԃ�
	bool isClearStage(int idx)const;
	//���̃X�e�[�W���J������
	void openStage(int idx);
	//���̃X�e�[�W���N���A�ς݂ɂ���
	void clearStage(int idx);
	//�f�B���N�g���ɃZ�[�u�f�[�^��ۑ�����
	void saveDirectory();
	//�f�[�^��S�ď�����
	void allInit();
private:
	//�z��ɂ��̃C���f�b�N�X�̃X�e�[�W������������ǉ�����
	void addStageData(int idx);

	std::vector<SAVE_DATA_STAGE_FORMAT> SaveData;
	STRING_TREE DataTree;
	static const std::string SaveDataFilePath;
};

