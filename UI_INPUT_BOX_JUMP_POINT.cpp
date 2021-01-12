#include "../Library/CONTAINER.h"
#include "UI.h"
#include "PROCESS_NODE.h"
#include "PROCESS_NODE_MANAGER.h"
#include "UI_FACTORY.h"
#include "UI_INPUT_BOX_JUMP_POINT.h"
UI_INPUT_BOX_JUMP_POINT::UI_INPUT_BOX_JUMP_POINT(CONTAINER* c, STATIC_FONT* font, PROCESS_NODE_MANAGER* processNodeManager) :
	ProcessNodeManager(processNodeManager) {
	UiInputBox.createInputBox(c, font, INPUT_TYPE::KEY);
}

UI_INPUT_BOX_JUMP_POINT::~UI_INPUT_BOX_JUMP_POINT() {
	if (!string().empty()) {
		ProcessNodeManager->removeJumpPoint(string());
	}
}

void UI_INPUT_BOX_JUMP_POINT::setString(const std::string& s) {
	//�O�ɃX�N���[���ɓo�^���Ă��������
	if (!string().empty()) {
		ProcessNodeManager->removeJumpPoint(string());
	}
	UiInputBox.inputBoxUiDrawer()->setString(s);
	//��������W�����v�|�C���g�X�N���[���ɒǉ�
	if (!s.empty()) {	
		ProcessNodeManager->addJumpPoint(s);
	}
}

void UI_INPUT_BOX_JUMP_POINT::setEnable(){
	if (!string().empty()&& IsDisable) {
		ProcessNodeManager->addJumpPoint(string());
		IsDisable = false;
	}
}

void UI_INPUT_BOX_JUMP_POINT::setDisable(){
	if (!string().empty()&&!IsDisable) {
		ProcessNodeManager->removeJumpPoint(string());
		IsDisable = true;
	}
}

