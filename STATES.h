#pragma once
#include<string>
#include<unordered_map>
#include "../Library/common.h"
class STATE_BASE;
class STATES {
public:
	STATES();
	~STATES();
	void update();
	void change(const char* name);
	void regist(STATE_BASE* state);
private:
	std::unordered_map<std::string,STATE_BASE*> States;
	STATE_BASE* CurrentState = 0;
};