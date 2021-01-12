#pragma once
#include "UI.h"
class CONTAINER;
class FAILED_ICON{
public:
	FAILED_ICON();
	~FAILED_ICON();
	void create(CONTAINER* c);
	UI* rootUi() { return &FailedIconUi; };
	void start();
	void update();
	void exit();
private:
	UI FailedIconUi;
	VECTOR2 FailedIconUiVelo;
};

