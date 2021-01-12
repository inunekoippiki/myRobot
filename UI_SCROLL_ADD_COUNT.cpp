#include "PROCESS_NODE_MANAGER.h"
#include "UI.h"
#include "UI_SCROLL_ADD_COUNT.h"

UI_SCROLL_ADD_COUNT::UI_SCROLL_ADD_COUNT(){
}

UI_SCROLL_ADD_COUNT::~UI_SCROLL_ADD_COUNT() {
}

void UI_SCROLL_ADD_COUNT::draw(SHADER* shader){
	UiScroll.draw(shader);
}

void UI_SCROLL_ADD_COUNT::create(CONTAINER* c, int maxStepNum){
	UiScroll.create(c, maxStepNum);
}

void UI_SCROLL_ADD_COUNT::create(UI* rootUi, UI* seekBarBackUi, UI* seekBarUi, UI* listBackUi, UI* scrollUpUi, UI* scrollDownUi, std::vector<UI*>&& listUi, int maxStepNum){
	UiScroll.create(rootUi,  seekBarBackUi, seekBarUi,  listBackUi, scrollUpUi,  scrollDownUi, std::move(listUi), maxStepNum);
}

void UI_SCROLL_ADD_COUNT::add(const std::string& s, PROCESS_NODE_MANAGER* processNodeManager){
	if (AddConuter.contains(s)) {
		AddConuter[s].first++;
	}
	else{
		UI* ui = processNodeManager->instanceUiScrollListNode(s.c_str());
		AddConuter.insert({ s,{1,ui} });
		UiScroll.add(ui);
	}
}

void UI_SCROLL_ADD_COUNT::remove(const std::string& s){
	if (!AddConuter.empty()&& AddConuter.contains(s)) {
		auto &i = AddConuter[s].first;
		i--;
		if (i <= 0) {
			UI* ui = AddConuter[s].second;
			UiScroll.remove(ui);
			AddConuter.erase(s);
			delete ui;
		}
	}
}

void UI_SCROLL_ADD_COUNT::update(){
	UiScroll.update();
}

void UI_SCROLL_ADD_COUNT::scrollUpdate(int stepNum){
	UiScroll.scrollUpdate(stepNum);
}
