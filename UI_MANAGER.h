#pragma once
#include "UI_ANNOTATION_MANAGER.h"
class UI;
//UI�ɐݒ肳�ꂽ�Bfunction�𓮂������߂̃N���X
class UI_MANAGER{
public:
	UI_MANAGER();
	~UI_MANAGER();
	void setRootUi(UI* rootUi);
	void update();
	//ui���폜���ꂽ��Ă΂��
	void uiDelete(UI* ui);
private:
	UI* RootUi = nullptr;
	UI* OverlapUi = nullptr;
	UI* ChoiceUi = nullptr;
	UI* DownUi = nullptr;
};

