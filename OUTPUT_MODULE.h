#pragma once
//出力モジュールのインターフェース
class OUTPUT_MODULE{
public:
	virtual ~OUTPUT_MODULE() {};
	//値を更新
	virtual void update() = 0;
private:

};
