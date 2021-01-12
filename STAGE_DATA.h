#pragma once
#include <string>
#include "../Library/STRING_TREE.h"
class STAGE_DATA{
public:
	STAGE_DATA();
	~STAGE_DATA();
	std::string mapFileName(int idx)const;
	std::string missionFileName(int idx)const;
	bool isExistRound(int idx)const;
	static std::string mapDataFolderPath();
	static std::string missionDataFolderPath();
private:
	STRING_TREE StageData;
	static const std::string MapDataFolderPath;
	static const std::string MissionDataFolderPath;

};

