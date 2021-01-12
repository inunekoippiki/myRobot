#pragma once
//ロボットに値を設定するためのインターフェース
class INPUT_MODULE_VALUE {
public:
	virtual ~INPUT_MODULE_VALUE() {};
	virtual void inputValue(double value) = 0;
private:

};
