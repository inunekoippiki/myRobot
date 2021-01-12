#include <fstream>
#include "../Library/common.h"
#include "SAVE_DATA.h"
const std::string SAVE_DATA::SaveDataFilePath = "saveData/round.txt";
SAVE_DATA::SAVE_DATA() :
	DataTree(STRING_TREE::loadFile(SaveDataFilePath)) {
	SaveData.reserve(DataTree.childs().size());
	for (int i = 0;i < DataTree.childs().size();i++) {
		SaveData.push_back(SAVE_DATA_STAGE_FORMAT{
			DataTree.atw(i)->atw("isOpen")->toInt(),
			DataTree.atw(i)->atw("isClear")->toInt() });
	}
}

SAVE_DATA::~SAVE_DATA() {
}

int SAVE_DATA::stageCnt(){
	return (int)SaveData.size();
}

bool SAVE_DATA::isOpenStage(int idx)const{
	if (SaveData.size() < idx) {
		return false;
	}
	return SaveData[idx].IsOpen;
}

bool SAVE_DATA::isClearStage(int idx)const {
	if (SaveData.size() < idx) {
		return false;
	}
	return SaveData[idx].IsClear;
}

void SAVE_DATA::openStage(int idx) {
	//配列にそのインデックスのステージが無かったら追加する
	addStageData(idx);
	//開放する
	SaveData[idx].IsOpen = 1;
}

void SAVE_DATA::clearStage(int idx) {
	//配列にそのインデックスのステージが無かったら追加する
	addStageData(idx);
	//開放する
	SaveData[idx].IsClear = 1;
}

void SAVE_DATA::saveDirectory(){
	std::ofstream ofs(SaveDataFilePath);
	if (!ofs.is_open()) {
		WARNING(true, "ENTITY_MANAGER", (SaveDataFilePath + "が読み込めません").c_str());
	}
	for (auto& i : SaveData) {
		ofs << "{isOpen{" + std::to_string(i.IsOpen) + "}isClear{" + std::to_string(i.IsClear) + "}}\n";
	}
	ofs.close();
}

void SAVE_DATA::allInit(){
	for (auto& i : SaveData) {
		i.IsClear = 0;
		i.IsOpen = 0;
	}
	//1ステージは開放
	SaveData[0].IsOpen = 1;
}

void SAVE_DATA::addStageData(int idx){
	//配列にそのインデックスのステージが無かったら追加する
	if (SaveData.size() < idx) {
		SaveData.reserve(idx);
		for (int i = 0;i < idx - SaveData.size();i++) {
			SaveData.push_back(SAVE_DATA_STAGE_FORMAT());
		}
	}
}
