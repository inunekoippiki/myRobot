#pragma once
#include "UI.h"
/*
roundType{arrival}
timeRimit{6000}
clearTime{3000}
item{5}
destroy{3}
carry{2}
*/
#include "DRAWER_STATIC_FONT.h"
class STRING_TREE;
class ROUND_MISSION{
public:
	ROUND_MISSION();
	~ROUND_MISSION();
	void create(const STRING_TREE& dataTree,STATIC_FONT* font);
	void update();
	void draw(SHADER* shader);
	void reset();
	void goal();
	void getItem();
	void destroyTarget();
	void carry();
	void deadRobot();

	bool isClear();
	bool isFail();
private:
	STATIC_FONT* Font = nullptr;
	float TimeLimitColorBlinkInterval = 0.04f;
	int TimeLimitColorBlinkStartFrame = 600;
	float TimeLimitColorBlink = 0.0f;
	int TimerCnt = 0;
	bool IsGoal = false;
	bool IsDeadRobot = false;
	int GetItemCnt = 0;
	int DestroyTargetCnt = 0;
	int CarryCnt = 0;

	struct MISSION_DATA{
		std::string RoundType;
		int TimeLimit = 0;
		int ClearTime = 0;
		int Goal = 0;
		int Item = 0;
		int Destroy = 0;
		int Carry = 0;
	};
	MISSION_DATA MissionData;
};

