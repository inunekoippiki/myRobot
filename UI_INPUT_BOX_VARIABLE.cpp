#include "../Library/CONTAINER.h"
#include "UI.h"
#include "PROCESS_NODE.h"
#include "PROCESS_NODE_MANAGER.h"
#include "UI_FACTORY.h"
#include "UI_INPUT_BOX_VARIABLE.h"
UI_INPUT_BOX_VARIABLE::UI_INPUT_BOX_VARIABLE(
	CONTAINER* c,
	STATIC_FONT* font, 
	INPUT_TYPE inputType, 
	PROCESS_NODE_MANAGER* processNodeManager) :
	ProcessNodeManager(processNodeManager) {
	UiInputBox.createInputBox(c, font, inputType);
}

UI_INPUT_BOX_VARIABLE::~UI_INPUT_BOX_VARIABLE() {
	if (!string().empty() && !IsNumber) {
		ProcessNodeManager->removeVeriable(string());
	}
}

void UI_INPUT_BOX_VARIABLE::setString(const std::string& s) {
	//�O�ɃX�N���[���ɓo�^���Ă��������
	if (!string().empty() && !IsNumber) { 
		ProcessNodeManager->removeVeriable(string()); 
	}
	//�����񂪋󔒂łȂ������l��������X�N���[���ɂ��Ȃ�
	if (!s.empty()&&strchr("-+0123456789", s.front()) != nullptr) {
		IsNumber = true;
		Number = atof(s.c_str());
		std::string sfix = std::to_string(Number);
		//double�𕶎���ɕϊ������ۂ̖��ʂ�.00000������
		if (strchr(sfix.c_str(), '.') != nullptr) {
			for (auto i = sfix.rbegin();i < sfix.rend();i++) {
				if (*i == '0') {
					sfix.pop_back();
				}
				else {
					break;
				}
			}
		}
		if (sfix.back() == '.') {
			sfix.pop_back();
		}
		UiInputBox.inputBoxUiDrawer()->setString(sfix);
	}
	else{//�����񂾂�����
		IsNumber = false;
		UiInputBox.inputBoxUiDrawer()->setString(s);
		if (!s.empty()) {//�����񂪋󔒂łȂ�������X�N���[���ɒǉ�
			ProcessNodeManager->addVariable(s);
		}
	}
}

void UI_INPUT_BOX_VARIABLE::setEnable(){
	if (!string().empty() && !IsNumber&& IsDisable) {
		ProcessNodeManager->addVariable(string());
		IsDisable = false;
	}
}

void UI_INPUT_BOX_VARIABLE::setDisable(){
	if (!string().empty() && !IsNumber&& !IsDisable) {
		ProcessNodeManager->removeVeriable(string());
		IsDisable = true;
	}
}

