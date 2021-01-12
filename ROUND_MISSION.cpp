#include <stdio.h>
#include "../Library/STRING_TREE.h"
#include "ROUND_MISSION.h"
ROUND_MISSION::ROUND_MISSION() {

}

ROUND_MISSION::~ROUND_MISSION() {
}

void ROUND_MISSION::create(const STRING_TREE& dataTree, STATIC_FONT* font){
	Font = font;
	MissionData.RoundType = dataTree.atw("roundType")->data();
	MissionData.TimeLimit = dataTree.atw("timeLimit")->toInt();
	MissionData.Goal = dataTree.atw("goal")->toInt();
	MissionData.ClearTime = dataTree.atw("clearTime")->toInt();
	MissionData.Item = dataTree.atw("item")->toInt();
	MissionData.Destroy = dataTree.atw("destroy")->toInt();
	MissionData.Carry = dataTree.atw("carry")->toInt();
	if (MissionData.Goal <= 0)goal();
}

void ROUND_MISSION::update() {
	TimerCnt++;
	if (MissionData.TimeLimit > 0) {
		TimeLimitColorBlink = abs(cosf((min(MissionData.TimeLimit - TimerCnt, TimeLimitColorBlinkStartFrame) - TimeLimitColorBlinkStartFrame) * TimeLimitColorBlinkInterval));
	}
}

void ROUND_MISSION::draw(SHADER* shader){
	char s[256] = {};
	float size = 64.0f;
	int width = 20;
	float x = 32.0f;
	float y = 32.0f;
	if (MissionData.TimeLimit > 0) {
		sprintf_s(s,sizeof(s), "残り時間:%dフレーム", MissionData.TimeLimit - TimerCnt);
		Font->adjustDraw_Over(shader, s,10, VECTOR2(x, y), VECTOR2(size, size), COLOR(1.0f, TimeLimitColorBlink, TimeLimitColorBlink, 1.0f));
	}
	else {
		Font->adjustDraw_Over(shader, "残り時間:制限なし", 12, VECTOR2(x, y), VECTOR2(size, size),COLOR(1.0f, TimeLimitColorBlink, TimeLimitColorBlink,1.0f));
	}

	x += 408.0f;
	Font->adjustDraw_Over(shader, "目標", width, VECTOR2(x, y), VECTOR2(size, size));

	y += 64.0f;
	float CurrentInfoShiftX = 680.0f;
	if (MissionData.ClearTime > 0) {
		sprintf_s(s, sizeof(s), ":%dフレーム生き残る", MissionData.ClearTime);
		Font->adjustDraw_Over(shader, s, width, VECTOR2(x, y), VECTOR2(size, size));
		if (MissionData.ClearTime - TimerCnt> 0) {
			sprintf_s(s, sizeof(s), "あと%dフレーム", MissionData.ClearTime - TimerCnt);
		}
		else{
			sprintf_s(s, sizeof(s), "達成");
		}
		Font->adjustDraw_Over(shader, s, width, VECTOR2(x+ CurrentInfoShiftX, y), VECTOR2(size, size));
		y += 64.0f;
	}
	if (MissionData.Goal > 0) {
		sprintf_s(s, sizeof(s), ":目標地点に到達");
		Font->adjustDraw_Over(shader, s, width, VECTOR2(x, y), VECTOR2(size, size));
		if (IsGoal) {
			Font->adjustDraw_Over(shader, "達成", width, VECTOR2(x + CurrentInfoShiftX, y), VECTOR2(size, size));
		}
		y += 64.0f;
	}
	if (MissionData.Destroy > 0) {
		sprintf_s(s, sizeof(s), ":ターゲットを%d個破壊する", MissionData.Destroy);
		Font->adjustDraw_Over(shader, s, width, VECTOR2(x, y), VECTOR2(size, size));
		if (MissionData.Destroy <= DestroyTargetCnt) {
			Font->adjustDraw_Over(shader, "達成", width, VECTOR2(x + CurrentInfoShiftX, y), VECTOR2(size, size));
		}
		else{
			sprintf_s(s, sizeof(s), "あと%d個", MissionData.Destroy - DestroyTargetCnt);
			Font->adjustDraw_Over(shader, s, width, VECTOR2(x + CurrentInfoShiftX, y), VECTOR2(size, size));
		}
		y += 64.0f;
	}
	if (MissionData.Item > 0) {
		sprintf_s(s, sizeof(s), ":アイテムを%d個回収する", MissionData.Item);
		Font->adjustDraw_Over(shader, s, width, VECTOR2(x, y), VECTOR2(size, size));
		if (MissionData.Item <= GetItemCnt) {
			Font->adjustDraw_Over(shader, "達成", width, VECTOR2(x + CurrentInfoShiftX, y), VECTOR2(size, size));
		}
		else{
			sprintf_s(s, sizeof(s), "あと%d個", MissionData.Item - GetItemCnt);
			Font->adjustDraw_Over(shader, s, width, VECTOR2(x + CurrentInfoShiftX, y), VECTOR2(size, size));
		}
		y += 64.0f;
	}
	if (MissionData.Carry > 0) {
		sprintf_s(s, sizeof(s), ":%d個輸送する", MissionData.Carry);
		Font->adjustDraw_Over(shader, s, width, VECTOR2(x, y), VECTOR2(size, size));
		if (MissionData.Carry <= CarryCnt) {
			Font->adjustDraw_Over(shader, "達成", width, VECTOR2(x + CurrentInfoShiftX, y), VECTOR2(size, size));
		}
		else{
			sprintf_s(s, sizeof(s), "あと%d個", MissionData.Carry - CarryCnt);
			Font->adjustDraw_Over(shader, s, width, VECTOR2(x + CurrentInfoShiftX, y), VECTOR2(size, size));
		}
		y += 64.0f;
	}
}

void ROUND_MISSION::reset(){
	TimerCnt = 0;
	IsGoal = false;
	GetItemCnt = 0;
	DestroyTargetCnt = 0;
	CarryCnt = 0;
	IsDeadRobot = false;
	if (MissionData.Goal <= 0)goal();
}

void ROUND_MISSION::goal(){
	IsGoal = true;
}

void ROUND_MISSION::getItem(){
	GetItemCnt++;
}

void ROUND_MISSION::destroyTarget(){
	DestroyTargetCnt++;
}

void ROUND_MISSION::carry(){
	CarryCnt++;
}

void ROUND_MISSION::deadRobot(){
	IsDeadRobot = true;
}

bool ROUND_MISSION::isClear(){
	return  (IsGoal &&
		TimerCnt >= MissionData.ClearTime &&
		GetItemCnt >= MissionData.Item &&
		DestroyTargetCnt >= MissionData.Destroy &&
		CarryCnt >= MissionData.Carry);
}

bool ROUND_MISSION::isFail() {
	if (IsDeadRobot) {
		return true;
	}
	if (MissionData.TimeLimit > 0) {
		return TimerCnt >= MissionData.TimeLimit;
	}
	return false;
}
