#pragma once
#include <array>
#include <string>
#include <functional>
#include "UI.h"
#include "DRAWER_STATIC_FONT.h"
class VECTOR2;
class CONTAINER;
//�L�[�{�[�h��UI
class UI_KEYBOARD {
public:
	UI_KEYBOARD(CONTAINER* c, STATIC_FONT* font);
	~UI_KEYBOARD();
	UI* rootUi() { return RootUi; }
	//�m������������̃R�[���o�b�N��ݒ肷��
	template<class T>
	void setEnterFunc(const T& func) {
		EnterKeyUi->setPushFunc(func);
	}
	//�L�����Z���������̃R�[���o�b�N��ݒ肷��
	template<class T>
	void setCancelFunc(const T& func) {
		RootUi->setPushFunc(func);
	}
	//IMM���猻�ݓ��͂���Ă��镶�����InputString�ɉ����܂�
	void acquisitionInputString();
	//InputString�̕�����S�ď����܂�
	void resetInputString();
	std::string inputString() { return InputString; }
	UI* createKeyboardUi(char c[3], STATIC_FONT* font, const VECTOR2& pos, const VECTOR2& fontPos, int size,TEXTURE* keyBack);
private:
	int Size = 0;
	VECTOR2 BackOffseet;
	//�������InputString�ɉ����܂�
	void inputStringAppend(const char* s);
	//InputString�̌��ꕶ���������܂�
	void inputStringBackSpace();
	std::string InputString;
	UI* RootUi = nullptr;
	UI* BackUi = nullptr;

	UI* RootQwertyKeyUi = nullptr;
	UI* QwertyKeyUi = nullptr;
	UI* QwertyKeyShiftUi = nullptr;
	UI* RootKanaKeyUi = nullptr;
	UI* KanaKeyUi = nullptr;
	UI* KatakanaKeyUi = nullptr;

	UI* InputStringUi = nullptr;
	DRAWER::STATIC_FONT* InputStringUiDrawer = nullptr;
	UI* EnterKeyUi = nullptr;
	UI* BackSpaceKeyUi = nullptr;
	UI* ShiftKeyUi = nullptr;
	std::array <UI*, 48> QwertyKey = { };
	std::array <UI*, 48> QwertyKeyShift = { };
	std::array<UI*, 100> KanaKey = { };
	std::array<UI*, 100> KatakanaKey = { };

	std::array<UI*, 100> KeyUi = { };
	std::array<UI*, 26> AlphaKeyUi = { };
	std::array<UI*, 10> NumberKeyUi = { };
	std::array<UI*, 5> FuncKeyUi = { };
	std::array<UI*, 12>SymbolKeyUi = { };

	UI* instanceButtonUi(TEXTURE* back, STATIC_FONT* font, const VECTOR2& pos, int fontSize, const char* s);
};


