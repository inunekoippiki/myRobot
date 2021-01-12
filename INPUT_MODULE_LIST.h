#pragma once
#include <string>
#include <unordered_map>
#include "UI_ANNOTATION.h"
class INPUT_MODULE_VALUE;
struct INPUT_MODULE_DATA {
	INPUT_MODULE_VALUE* Module = nullptr;
	UI_ANNOTATION Annotation;
};
class INPUT_MODULE_LIST{
public:
	using LIST = std::unordered_map < std::string, INPUT_MODULE_DATA>;
	INPUT_MODULE_LIST();
	INPUT_MODULE_LIST(LIST&& list);
	~INPUT_MODULE_LIST();
	LIST* list(){ return &List; }
private:
	LIST List;
};

