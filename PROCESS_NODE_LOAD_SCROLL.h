#pragma once
#include "UI.h"
#include "UI_SCROLL.h"
class STATIC_FONT;
class PROCESS_NODE_MANAGER;
class PROCESS_NODE_LINER;
namespace DRAWER {
	class STATIC_FONT;
}
class SOUND;
class PROCESS_NODE_LOAD_SCROLL {
public:
	//���[�h�f�[�^�̈ꍀ�ڂ̃N���X
	class SCROLL_NODE {
	public:
		SCROLL_NODE(const std::string& s, CONTAINER* c, STATIC_FONT* font, PROCESS_NODE_LOAD_SCROLL* processNodeLoad);
		~SCROLL_NODE();
		UI* rootUi() { return &RootUi; }
		void changeString(const std::string& s);
		std::string drawerString();
	private:
		UI RootUi;
		UI StringUi;
		UI DeleteIcon;
		UI DeleteIconOver;
		int DeleteFrame = 0;
		int DeleteFrameCnt = 0;
		DRAWER::STATIC_FONT* Drawer = nullptr;
	};

	PROCESS_NODE_LOAD_SCROLL(CONTAINER* c, STATIC_FONT* font, PROCESS_NODE_MANAGER* processNodeManager);
	~PROCESS_NODE_LOAD_SCROLL();
	UI_SCROLL* uiScroll() { return&UiScroll; }
	void create(PROCESS_NODE_MANAGER* processNodeManager);
	//�X�N���[���m�[�h�̓��e�̍X�V
	void SaveDataListScrollUpdate();
	//�݌v�f�[�^���폜����
	void deleteSaveData(const std::string& fileName);
	//stringTree�̐݌v�f�[�^��ǂ�Ńm�[�h��ǉ�����
	void load(const std::string& data);
	//�I���I��
	void endScrollDisp();
private:
	PROCESS_NODE_MANAGER* ProcessNodeManager = nullptr;
	CONTAINER* C = nullptr;
	STATIC_FONT* Font = nullptr;
	//�Z�[�u�f�[�^�Ǎ��X�N���[��
	UI_SCROLL UiScroll;
	std::vector<SCROLL_NODE*> NodeList;
	//��
	SOUND* SoundSaveDataDelete = nullptr;
	SOUND* SoundSaveDataLoad = nullptr;
private:
	//�݌v�f�[�^�̃t�H���_�p�X�萔
	static const std::string DesignDataSavePath;
};

