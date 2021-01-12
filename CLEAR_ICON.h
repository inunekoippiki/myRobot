#pragma once
#include "UI.h"
class CONTAINER;
class CLEAR_ICON{
public:
	CLEAR_ICON();
	~CLEAR_ICON();
	void create(CONTAINER* c);
	UI* rootUi() {return &ClearIconUi;};
	void start();
	void update();
	void exit();
private:
	UI ClearIconUi;
	int ClearIconUiMorphTimer = 0;
	int ClearIconUiMorphTime = 0;
};

