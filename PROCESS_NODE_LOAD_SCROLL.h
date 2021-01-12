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
	//ロードデータの一項目のクラス
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
	//スクロールノードの内容の更新
	void SaveDataListScrollUpdate();
	//設計データを削除する
	void deleteSaveData(const std::string& fileName);
	//stringTreeの設計データを読んでノードを追加する
	void load(const std::string& data);
	//選択終了
	void endScrollDisp();
private:
	PROCESS_NODE_MANAGER* ProcessNodeManager = nullptr;
	CONTAINER* C = nullptr;
	STATIC_FONT* Font = nullptr;
	//セーブデータ読込スクロール
	UI_SCROLL UiScroll;
	std::vector<SCROLL_NODE*> NodeList;
	//音
	SOUND* SoundSaveDataDelete = nullptr;
	SOUND* SoundSaveDataLoad = nullptr;
private:
	//設計データのフォルダパス定数
	static const std::string DesignDataSavePath;
};

