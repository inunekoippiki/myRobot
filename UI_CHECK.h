#pragma once
#include "UI.h"
//チェックボックスのUI
class UI_CHECK{
public:
	UI_CHECK();
	~UI_CHECK();
	void create(UI* rootUi, UI* backUi, UI* checkUi);
	bool isCheck() { return IsCheck; }
	void setCheck(bool isCheck);
	UI* rootUi() { return RootUi; }
	void onClick();
private:
	bool IsCheck = false;
	UI* RootUi = nullptr;
	UI* BackUi = nullptr;
	UI* CheckUi = nullptr;
};

