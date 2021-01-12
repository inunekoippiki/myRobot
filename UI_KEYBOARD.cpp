#include "../Library/GRAPHIC.h"
#include "../Library/WINDOW.h"
#include "../Library/MB_LIB.h"
#include "../Library/VECTOR2.h"
#include "../Library/CONTAINER.h"
#include "../Library/common.h"
#include "UI.h"
#include "UI_FACTORY.h"
#include "UI_FUNC_ATTACHER.h"
#include "DRAWER_EMPTY.h"
#include "UI_KEYBOARD.h"
UI_KEYBOARD::UI_KEYBOARD(CONTAINER* c, STATIC_FONT* font) {
	TEXTURE* keyBackTexture = c->texture("keyboradKeyBack");
	BackOffseet = VECTOR2(1.0f, 1.0f);
	Size = 64;
	//���[�gUI
	{
		RootUi = UI_FACTORY::instanceEmpty();
		RootUi->setIsReleaseDisable(true);
		RootUi->setIsUnconditionalCollisionHit(true);
	}
	{
		BackUi = UI_FACTORY::instance(c->texture("keyboradKanaBack"), VECTOR2(254.0f, 79.0f), VECTOR2::one());
		RootUi->addChilds(BackUi);
	}
	//������\������UI
	{
		InputStringUi = UI_FACTORY::instance(c->texture("keyborad20ByteBack"),VECTOR2(235.0f, 28.0f), VECTOR2::one());
		InputStringUiDrawer = DRAWER::STATIC_FONT::instance("", font, VECTOR2(), VECTOR2(Size, Size), DRAWER::STATIC_FONT::drawMethodDefault());
		InputStringUiDrawer->setDrawMethod(DRAWER::STATIC_FONT::drawMethodAdjustDraw_Over());
		InputStringUiDrawer->setMaxWidth(20);
		UI* ui = UI_FACTORY::instance(InputStringUiDrawer);
		ui->setIsCollisionDisable(true);
		InputStringUi->addChilds(ui);
		BackUi->addChilds(InputStringUi);
	}
	//�m��{�^��
	{
		EnterKeyUi = instanceButtonUi(c->texture("keyboradDoubleBack"), font, VECTOR2(876.0f, 28.0f), Size, "�m��");
		BackUi->addChilds(EnterKeyUi);
	}
	//�o�b�N�X�y�[�X�{�^��
	{
		BackSpaceKeyUi = instanceButtonUi(c->texture("keyborad9ByteBack"), font, VECTOR2(1005.0f, 28.0f), Size, "BackSpace");
		BackSpaceKeyUi->setPushFunc([this]() {this->inputStringBackSpace();});
		BackUi->addChilds(BackSpaceKeyUi);
	}
	//Qwerty�L�[�{�[�h�؂�ւ�
	{
		RootQwertyKeyUi = UI_FACTORY::instanceEmpty();
		//�������L�[�{�[�h�̐e
		QwertyKeyUi = UI_FACTORY::instanceEmpty();
		RootQwertyKeyUi->addChilds(QwertyKeyUi);
		//�啶���L�[�{�[�h�̐e
		QwertyKeyShiftUi = UI_FACTORY::instanceEmpty();
		RootQwertyKeyUi->addChilds(QwertyKeyShiftUi);
		BackUi->addChilds(RootQwertyKeyUi);
	}
	//���ȕ����L�[�{�[�h�؂�ւ�
	{
		RootKanaKeyUi = UI_FACTORY::instanceEmpty();
		//�Ђ炪�ȃL�[�{�[�h�̐e
		KanaKeyUi = UI_FACTORY::instanceEmpty();
		RootKanaKeyUi->addChilds(KanaKeyUi);
		//�J�^�J�i�L�[�{�[�h�̐e
		KatakanaKeyUi = UI_FACTORY::instanceEmpty();
		RootKanaKeyUi->addChilds(KatakanaKeyUi);
		BackUi->addChilds(RootKanaKeyUi);
		RootKanaKeyUi->setIsDisable(true);
	}

	//Qwerty�L�[�{�[�h
	{
		const char* key =
			"1234567890-^\\"
			"qwertyuiop@["
			"asdfghjkl;:]"
			"zxcvbnm,./\\";
		const char* shiftKey =
			"!\"#$%&'()0=~|"
			"QWERTYUIOP`{"
			"ASDFGHJKL+*}"
			"ZXCVBNM<>?_";

		int lp[] = { 13,12,12,11 };
		VECTOR2 pos[4] = { VECTOR2(153,125)/*�I�t�Z�b�g*/ };
		for (int i = 0;i < sizeof(pos) / sizeof(*pos);i++) {
			pos[i].x = pos[0].x + 30 * i;
			pos[i].y = pos[0].y + Size * i;
		}
		char cm[2] = { 0 };
		int idx = 0;
		for (int idxY = 0;idxY < sizeof(lp) / sizeof(*lp);idxY++) {
			for (int idxX = 0;idxX < lp[idxY];idxX++) {
				cm[0] = *(key + idx);
				QwertyKey[idx] = createKeyboardUi(cm, font, pos[idxY] + VECTOR2((float)Size * idxX,0.0f), VECTOR2(16.0f,0.0f), Size, keyBackTexture);
				QwertyKeyUi->addChilds(QwertyKey[idx]);
				cm[0] = *(shiftKey + idx);
				QwertyKeyShift[idx] = createKeyboardUi(cm, font, pos[idxY] + VECTOR2((float)Size * idxX,0.0f), VECTOR2(16.0f, 0.0f), Size, keyBackTexture);
				QwertyKeyShiftUi->addChilds(QwertyKeyShift[idx]);
				idx++;
			}
		}
		{
			UI* ui = instanceButtonUi(c->texture("keyborad8ByteBack"), font, VECTOR2(74.0f, pos[3].y + Size), Size, "���ȕ���");
			ui->setPushFunc([this]() {this->RootQwertyKeyUi->setIsDisable(true);this->RootKanaKeyUi->setIsDisable(false);});
			RootQwertyKeyUi->addChilds(ui);
		}
		{
			UI* ui = instanceButtonUi(c->texture("keyborad5ByteBack"), font, VECTOR2(74.0f, pos[3].y), Size, "SHIFT");
			ui->setPushFunc([this]() {this->QwertyKeyUi->setIsDisable(true);this->QwertyKeyShiftUi->setIsDisable(false);});
			QwertyKeyUi->addChilds(ui);
		}
		{
			UI* ui = instanceButtonUi(c->texture("keyborad5ByteBack"), font, VECTOR2(74.0f, pos[3].y), Size, "shift");
			ui->setPushFunc([this]() {this->QwertyKeyUi->setIsDisable(false);this->QwertyKeyShiftUi->setIsDisable(true);});
			QwertyKeyShiftUi->addChilds(ui);
		}
		QwertyKeyShiftUi->setIsDisable(true);
	}
	//�Ђ炪�ȃL�[�{�[�h
	{
		const char* kana =
			"����������"
			"����������"
			"����������"
			"�����Ă�"
			"�Ȃɂʂ˂�"
			"�͂Ђӂւ�"
			"�܂݂ނ߂�"
			"�₢�䂦��"
			"������"
			"�킢������"
			"����������"
			"����������"
			"�����Âł�"
			"�΂тԂׂ�"
			"�ς҂Ղ؂�"
			"����������"
			"������["
			"�I�H���h�f"
			"�������`��"
			"���{�|���^";
		const char* katakana =
			"�A�C�E�G�I"
			"�J�L�N�P�R"
			"�T�V�X�Z�\"
			"�^�`�c�e�g"
			"�i�j�k�l�m"
			"�n�q�t�w�z"
			"�}�~������"
			"���C���G��"
			"����������"
			"���C���G��"
			"�K�M�O�Q�S"
			"�U�W�Y�[�]"
			"�_�a�d�f�h"
			"�o�r�u�x�{"
			"�p�s�v�y�|"
			"�@�B�D�F�H"
			"�������b�["
			"�����E�Q��"
			"�i�o�u�O�b"
			"�j�p�v�M�D";
		char c[3] = { 0 };
		int idx = 0;
		VECTOR2 offset = VECTOR2(264, 125);
		for (int i = 0;i < 10;i++) {
			for (int i2 = 0;i2 < 5;i2++) {
				c[0] = *kana++;
				c[1] = *kana++;
				KanaKey[idx] = createKeyboardUi(c, font, VECTOR2(Size * i2, i * Size) + offset, VECTOR2(), Size, keyBackTexture);
				KanaKeyUi->addChilds(KanaKey[idx]);
				c[0] = *katakana++;
				c[1] = *katakana++;
				KatakanaKey[idx] = createKeyboardUi(c, font, VECTOR2(Size * i2, i * Size) + offset, VECTOR2(), Size,  keyBackTexture);
				KatakanaKeyUi->addChilds(KatakanaKey[idx]);

				c[0] = *(kana + 98);
				c[1] = *(kana + 99);
				KanaKey[idx] = createKeyboardUi(c, font, VECTOR2(Size * i2 + 6 * Size, i * Size) + offset, VECTOR2(), Size, keyBackTexture);
				KanaKeyUi->addChilds(KanaKey[idx]);
				c[0] = *(katakana + 98);
				c[1] = *(katakana + 99);
				KatakanaKey[idx] = createKeyboardUi(c, font, VECTOR2(Size * i2 + 6 * Size, i * Size) + offset,VECTOR2(), Size, keyBackTexture);
				KatakanaKeyUi->addChilds(KatakanaKey[idx]);

				idx++;
			}
		}
	}

	{
		UI* ui = instanceButtonUi(c->texture("keyboradDoubleBack"), font, VECTOR2(74.0f, Size * 6.0f), Size, "�p��");
		ui->setPushFunc([this]() {this->RootQwertyKeyUi->setIsDisable(false);this->RootKanaKeyUi->setIsDisable(true);});
		RootKanaKeyUi->addChilds(ui);
	}
	{
		UI* ui = instanceButtonUi(c->texture("keyboradDoubleBack"), font, VECTOR2(74.0f, Size * 5.0f), Size, "�J�i");
		ui->setPushFunc([this]() {this->KanaKeyUi->setIsDisable(true);this->KatakanaKeyUi->setIsDisable(false);});
		KanaKeyUi->addChilds(ui);
	}
	{
		UI* ui = instanceButtonUi(c->texture("keyboradDoubleBack"), font, VECTOR2(74.0f, Size * 5.0f), Size, "����");
		ui->setPushFunc([this]() {this->KanaKeyUi->setIsDisable(false);this->KatakanaKeyUi->setIsDisable(true);});
		KatakanaKeyUi->addChilds(ui);
	}
	KatakanaKeyUi->setIsDisable(true);
}

UI_KEYBOARD::~UI_KEYBOARD() {
	delete RootUi;
}

void UI_KEYBOARD::acquisitionInputString(){
	char szBuf[1024] = {};
	WINDOW* w = WINDOW::instance();
	HIMC hImc = ImmGetContext(w->hostHandle());
	ImmGetCompositionString(hImc, GCS_COMPSTR, szBuf, sizeof(szBuf));
	InputString += szBuf;
}

void UI_KEYBOARD::resetInputString(){
	InputString.clear();
	InputStringUiDrawer->setString(InputString.c_str());
}

UI* UI_KEYBOARD::createKeyboardUi(char c[3], STATIC_FONT* font, const VECTOR2& pos, const VECTOR2& fontPos, int size, TEXTURE* keyBack){
	UI* backUi = UI_FACTORY::instance(keyBack, pos + BackOffseet, VECTOR2::one());
	UI* ui = new UI;
	DRAWER::STATIC_FONT* drawer = DRAWER::STATIC_FONT::instance((const char*)c, font, fontPos, VECTOR2(size, size), DRAWER::STATIC_FONT::drawMethodDefault());
	ui->create(drawer);
	ui->setIsCollisionDisable(true);
	backUi->addChilds(ui);
	unsigned s = (BYTE)c[0] | ((BYTE)c[1] << 8);
	backUi->setPushFunc([s, this]() {this->inputStringAppend((char*)&s);});
	UI_FUNC_ATTACHER::OverlapColorChange(backUi, drawer);
	return backUi;
}

void UI_KEYBOARD::inputStringAppend(const char* s){
	InputString += s;
	InputStringUiDrawer->setString(InputString.c_str());
}

void UI_KEYBOARD::inputStringBackSpace(){
	if (!InputString.empty()) {
		if (MB_LIB::charSize(InputString.data() + InputString.size() - 2) == 2) {
			InputString.pop_back();
		};
		InputString.pop_back();
		InputStringUiDrawer->setString(InputString.c_str());
	}
}

UI* UI_KEYBOARD::instanceButtonUi(TEXTURE* back, STATIC_FONT* font,const VECTOR2& pos,int fontSize, const char* s){
	UI* ui = UI_FACTORY::instance(back, pos + BackOffseet, VECTOR2::one());
	DRAWER::STATIC_FONT* drawer = DRAWER::STATIC_FONT::instance(s, font, VECTOR2(), VECTOR2(fontSize, fontSize), DRAWER::STATIC_FONT::drawMethodDefault());
	UI* fontUi = UI_FACTORY::instance(drawer);
	fontUi->setIsCollisionDisable(true);
	ui->addChilds(fontUi);
	UI_FUNC_ATTACHER::OverlapColorChange(ui, drawer);
	return ui;
}
