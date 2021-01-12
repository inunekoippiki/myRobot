#pragma once
//ロボットから値を取得するためのインターフェース
class OUTPUT_MODULE_VALUE {
public:
	virtual ~OUTPUT_MODULE_VALUE() {};
	virtual double outputValue() = 0;
private:

};
