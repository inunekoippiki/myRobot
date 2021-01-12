#include "STAGE_DATA.h"
const std::string STAGE_DATA::MapDataFolderPath = "Assets/stageData/mapData/";
const std::string STAGE_DATA::MissionDataFolderPath = "Assets/stageData/missionData/";

STAGE_DATA::STAGE_DATA():
	StageData(STRING_TREE::loadFile("Assets/stageData/stageData.txt")) {
}

STAGE_DATA::~STAGE_DATA() {
}

std::string STAGE_DATA::mapFileName(int idx)const {
	STRING_TREE* data = StageData.atw(idx);
	return MapDataFolderPath+ data->atw("stageFile")->data()+".txt";
}

std::string STAGE_DATA::missionFileName(int idx)const {
	STRING_TREE* data = StageData.atw(idx);
	return MissionDataFolderPath+ data->atw("missionFile")->data()+".txt";
}

bool STAGE_DATA::isExistRound(int idx) const{
	STRING_TREE* data = StageData.at(idx);
	return (data!=nullptr);
}

std::string STAGE_DATA::mapDataFolderPath() {
	return MapDataFolderPath;
}

std::string STAGE_DATA::missionDataFolderPath() {
	return MissionDataFolderPath;
}
