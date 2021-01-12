#pragma once
class STATES;
class STATE_BASE{
public:
	STATE_BASE() {};
	~STATE_BASE() {};
	virtual void onEnter() = 0;
	virtual void update() = 0;
	virtual void onExit() = 0;
	virtual const char* name()const = 0;
	STATES* states() { return States; };
protected:
	STATES* States = 0;
};
