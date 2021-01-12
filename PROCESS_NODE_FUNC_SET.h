#pragma once
#include "../Library/INDEV.h"
#include "INPUT_COMMON.h"
#include "PROCESS_NODE_MANAGER.h"
#include "PROCESS_NODE_COMMAND/FACTORY.h"
class UI;
class UI_INPUT_BOX;
class UI_SCROLL;
namespace PROCESS_NODE_FUNC_SET {
	//uiが押されたら入力用キーボード表示する機能を付ける
	template<typename T>
	void startKeyboardInputAnyCallback(UI* ui, PROCESS_NODE_MANAGER* processNodeManager, T callback) {
		static_assert(sizeof(T) < 38, "callbackSize38byteOver");
		ui->setPushFunc([processNodeManager, callback]() {
			processNodeManager->startKeyboardInput(callback);}
		);
	};

	//uiが押されたら入力用スクロール表示する機能を付ける
	template <typename T>
	void startScrollInputAnyCallback(UI* ui, UI_SCROLL* scroll, PROCESS_NODE_MANAGER* processNodeManager, T callback) {
		static_assert(sizeof(T) < 38, "callbackSize38byteOver");
		ui->setPushFunc([processNodeManager, scroll, callback]() {
			processNodeManager->startScrollInput(scroll, INPUT_COMMON::MousePosition(INDEV::instance()), callback);}
		);
	}
	//uiが押されたらコマンドを介して入力ボックスに入力する
	template<class INPUT_OBJ>
	auto inputObjSetStringFunc(INPUT_OBJ* inputObj, PROCESS_NODE_MANAGER* processNodeManager) {
		return [inputObj, processNodeManager](const std::string& s) {
			auto command = PROCESS_NODE_COMMAND::instanceInput(inputObj, s);
			processNodeManager->commandStream()->push(command);
			command->execute();
		};
	}
}