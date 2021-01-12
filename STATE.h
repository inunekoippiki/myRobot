#pragma once
#include "STATE_BASE.h"
template <typename T>
class STATE:public STATE_BASE {
public:
	ENTITY_STATE(T* owner)
		:Owner(owner){
		States=owner->states();
	}
	virtual void onEnter() = 0;
	virtual void update() = 0;
	virtual void onExit() = 0;
	virtual const char* name()const = 0;
	T* owner() { return Owner; }
private:
	T* Owner = 0;
};