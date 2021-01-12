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
	//各ラウンドデータが入ったデータ
	STRING_TREE* dataTree() { return &DataTree; }
	//すべてのステージの数を返す
	int stageCnt();
	//そのステージが開放されているかを返す
	bool isOpenStage(int idx)const;
	//そのステージがクリアされているかを返す
	bool isClearStage(int idx)const;
	//そのステージを開放する
	void openStage(int idx);
	//そのステージをクリア済みにする
	void clearStage(int idx);
	//ディレクトリにセーブデータを保存する
	void saveDirectory();
	//データを全て初期化
	void allInit();
private:
	//配列にそのインデックスのステージが無かったら追加する
	void addStageData(int idx);

	std::vector<SAVE_DATA_STAGE_FORMAT> SaveData;
	STRING_TREE DataTree;
	static const std::string SaveDataFilePath;
};

