#pragma once
#include <array>
#include "../Library/VECTOR2.h"
class UI;
class NODE_LINE;
//NODE_LINE‚ðˆêŽž“I‚É•Û‘¶‚·‚éƒNƒ‰ƒX
class NODE_LINE_DATA{
public:
	NODE_LINE_DATA();
	NODE_LINE_DATA(NODE_LINE* nodeLine);
	NODE_LINE_DATA& operator=(const NODE_LINE_DATA& rhs) {
		Num = rhs.Num;
		Points = rhs.Points;
		return *this;
	}
	NODE_LINE_DATA& operator=(NODE_LINE_DATA&& rhs) {
		Num = rhs.Num;
		Points = rhs.Points;
		return *this;
	}
	void set(NODE_LINE* nodeLine);
	~NODE_LINE_DATA();
private:
	size_t Num = 0;
	std::array<VECTOR2, 6> Points;
};

