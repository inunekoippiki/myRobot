#pragma once
#include "UI_ANNOTATION_MANAGER.h"
class UI;
//UI‚Éİ’è‚³‚ê‚½Bfunction‚ğ“®‚©‚·‚½‚ß‚ÌƒNƒ‰ƒX
class UI_MANAGER{
public:
	UI_MANAGER();
	~UI_MANAGER();
	void setRootUi(UI* rootUi);
	void update();
	//ui‚ªíœ‚³‚ê‚½‚çŒÄ‚Î‚ê‚é
	void uiDelete(UI* ui);
private:
	UI* RootUi = nullptr;
	UI* OverlapUi = nullptr;
	UI* ChoiceUi = nullptr;
	UI* DownUi = nullptr;
};

