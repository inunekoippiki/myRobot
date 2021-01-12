#pragma once
#include <string>
#include <unordered_map>
#include "UI_SCROLL.h"
class CONTAINER;
class UI;
class SHADER;
//ìØÇ∂çÄñ⁄ÇÇ‹Ç∆ÇﬂÇÈÉXÉNÉçÅ[Éã
class UI_SCROLL_ADD_COUNT{
public:
	UI_SCROLL_ADD_COUNT();
	~UI_SCROLL_ADD_COUNT();
	void draw(SHADER* shader);
	void create(CONTAINER* c, int maxStepNum);
	void create(
		UI* rootUi,
		UI* seekBarBackUi,
		UI* seekBarUi,
		UI* listBackUi,
		UI* scrollUpUi,
		UI* scrollDownUi,
		std::vector<UI*>&& listUi,
		int maxStepNum);
	void add(const std::string& s, PROCESS_NODE_MANAGER* processNodeManager);
	void remove(const std::string& s);
	void update();
	void scrollUpdate(int stepNum);
	UI* rootUi() { return UiScroll.rootUi(); }
	UI* seekBarBackUi() { return UiScroll.seekBarBackUi(); }
	UI* seekBarUi() { return UiScroll.seekBarUi(); }
	UI* listBackUi() { return UiScroll.listBackUi(); }
	UI* scrollUpUi() { return UiScroll.scrollUpUi(); }
	UI* scrollDownUi() { return UiScroll.scrollDownUi(); }
	std::vector<UI*>* listUi() { return UiScroll.listUi(); }
	int stepNum()const { return UiScroll.stepNum(); }
	UI_SCROLL* uiScroll() { return &UiScroll; }
private:
	std::unordered_map<std::string,std::pair<int,UI*>> AddConuter;
	UI_SCROLL UiScroll;
};
