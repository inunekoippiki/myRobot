#pragma once
#include "INPUT_MODULE_VALUE.h"
//ロボットに異なる数値型を設定するため
//結局入ってくるのはdoubleなので範囲が広いと丸められる
template<class T>
class INPUT_MODULE_SIMPLE:public INPUT_MODULE_VALUE {
public:
	INPUT_MODULE_SIMPLE(T* value):Value(value){};
	~INPUT_MODULE_SIMPLE() {};
	void inputValue(double value) override { *Value = static_cast<T>(value); }
private:
	T* Value = nullptr;
};
