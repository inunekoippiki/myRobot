#pragma once
#include "INPUT_MODULE_VALUE.h"
//���{�b�g�ɈقȂ鐔�l�^��ݒ肷�邽��
//���Ǔ����Ă���̂�double�Ȃ̂Ŕ͈͂��L���Ɗۂ߂���
template<class T>
class INPUT_MODULE_SIMPLE:public INPUT_MODULE_VALUE {
public:
	INPUT_MODULE_SIMPLE(T* value):Value(value){};
	~INPUT_MODULE_SIMPLE() {};
	void inputValue(double value) override { *Value = static_cast<T>(value); }
private:
	T* Value = nullptr;
};
