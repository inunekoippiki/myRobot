#pragma once
#include "../Library/VECTOR2.h"
#include <vector>
#include <variant>
class ROBOT_COMPILER_ERROR{
public:
	struct NONE_OUTPUT_MODULE_NODE {
	};
	struct NONE_INPUT_MODULE_NODE {
	};
	struct NONE_START_NODE {
	};
	struct DUPLECATE_START_NODE {
	};
	struct NONE_JUMP_POINT {
	};
	struct DUPLECATE_JUMP_POINT {
	};

	ROBOT_COMPILER_ERROR();
	~ROBOT_COMPILER_ERROR();
	void noneOutputModule();
	void noneInputModule();
	void noneStartNode();
	void duplecateStartNode();
	void noneJumpPoint();
	void duplecateJumpPoint();

	//エラー情報をクリア
	void clear();
	//エラーがなかったらtrue
	bool isNotError()const;
	const auto* errorList()const { return &ErrorList; }
private:
	std::vector<
		std::variant<
		NONE_OUTPUT_MODULE_NODE, 
		NONE_INPUT_MODULE_NODE, 
		NONE_START_NODE, 
		DUPLECATE_START_NODE, 
		NONE_JUMP_POINT, 
		DUPLECATE_JUMP_POINT
		>
	> ErrorList;
};

