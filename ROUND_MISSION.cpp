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
		sprintf_s(s,sizeof(s), "�c�莞��:%d�t���[��", MissionData.TimeLimit - TimerCnt);
		Font->adjustDraw_Over(shader, s,10, VECTOR2(x, y), VECTOR2(size, size), COLOR(1.0f, TimeLimitColorBlink, TimeLimitColorBlink, 1.0f));
	}
	else {
		Font->adjustDraw_Over(shader, "�c�莞��:�����Ȃ�", 12, VECTOR2(x, y), VECTOR2(size, size),COLOR(1.0f, TimeLimitColorBlink, TimeLimitColorBlink,1.0f));
	}

	x += 408.0f;
	Font->adjustDraw_Over(shader, "�ڕW", width, VECTOR2(x, y), VECTOR2(size, size));

	y += 64.0f;
	float CurrentInfoShiftX = 680.0f;
	if (MissionData.ClearTime > 0) {
		sprintf_s(s, sizeof(s), ":%d�t���[�������c��", MissionData.ClearTime);
		Font->adjustDraw_Over(shader, s, width, VECTOR2(x, y), VECTOR2(size, size));
		if (MissionData.ClearTime - TimerCnt> 0) {
			sprintf_s(s, sizeof(s), "����%d�t���[��", MissionData.ClearTime - TimerCnt);
		}
		else{
			sprintf_s(s, sizeof(s), "�B��");
		}
		Font->adjustDraw_Over(shader, s, width, VECTOR2(x+ CurrentInfoShiftX, y), VECTOR2(size, size));
		y += 64.0f;
	}
	if (MissionData.Goal > 0) {
		sprintf_s(s, sizeof(s), ":�ڕW�n�_�ɓ��B");
		Font->adjustDraw_Over(shader, s, width, VECTOR2(x, y), VECTOR2(size, size));
		if (IsGoal) {
			Font->adjustDraw_Over(shader, "�B��", width, VECTOR2(x + CurrentInfoShiftX, y), VECTOR2(size, size));
		}
		y += 64.0f;
	}
	if (MissionData.Destroy > 0) {
		sprintf_s(s, sizeof(s), ":�^�[�Q�b�g��%d�j�󂷂�", MissionData.Destroy);
		Font->adjustDraw_Over(shader, s, width, VECTOR2(x, y), VECTOR2(size, size));
		if (MissionData.Destroy <= DestroyTargetCnt) {
			Font->adjustDraw_Over(shader, "�B��", width, VECTOR2(x + CurrentInfoShiftX, y), VECTOR2(size, size));
		}
		else{
			sprintf_s(s, sizeof(s), "����%d��", MissionData.Destroy - DestroyTargetCnt);
			Font->adjustDraw_Over(shader, s, width, VECTOR2(x + CurrentInfoShiftX, y), VECTOR2(size, size));
		}
		y += 64.0f;
	}
	if (MissionData.Item > 0) {
		sprintf_s(s, sizeof(s), ":�A�C�e����%d�������", MissionData.Item);
		Font->adjustDraw_Over(shader, s, width, VECTOR2(x, y), VECTOR2(size, size));
		if (MissionData.Item <= GetItemCnt) {
			Font->adjustDraw_Over(shader, "�B��", width, VECTOR2(x + CurrentInfoShiftX, y), VECTOR2(size, size));
		}
		else{
			sprintf_s(s, sizeof(s), "����%d��", MissionData.Item - GetItemCnt);
			Font->adjustDraw_Over(shader, s, width, VECTOR2(x + CurrentInfoShiftX, y), VECTOR2(size, size));
		}
		y += 64.0f;
	}
	if (MissionData.Carry > 0) {
		sprintf_s(s, sizeof(s), ":%d�A������", MissionData.Carry);
		Font->adjustDraw_Over(shader, s, width, VECTOR2(x, y), VECTOR2(size, size));
		if (MissionData.Carry <= CarryCnt) {
			Font->adjustDraw_Over(shader, "�B��", width, VECTOR2(x + CurrentInfoShiftX, y), VECTOR2(size, size));
		}
		else{
			sprintf_s(s, sizeof(s), "����%d��", MissionData.Carry - CarryCnt);
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
