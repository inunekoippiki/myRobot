#pragma once
#include "UI_ANNOTATION_MANAGER.h"
class UI;
//UIに設定された。functionを動かすためのクラス
class UI_MANAGER{
public:
	UI_MANAGER();
	~UI_MANAGER();
	void setRootUi(UI* rootUi);
	void update();
	//uiが削除されたら呼ばれる
	void uiDelete(UI* ui);
private:
	UI* RootUi = nullptr;
	UI* OverlapUi = nullptr;
	UI* ChoiceUi = nullptr;
	UI* DownUi = nullptr;
};

