#pragma once
#include "OUTPUT_MODULE_VALUE.h"
//���{�b�g�ɈقȂ鐔�l�^���擾���邽��
template<class T>
class OUTPUT_MODULE_SIMPLE:public OUTPUT_MODULE_VALUE {
public:
	OUTPUT_MODULE_SIMPLE(T* value) :Value(value) {};
	~OUTPUT_MODULE_SIMPLE() {};
	double outputValue() { return static_cast<double>(*Value); }
private:
	T* Value = nullptr;
};

