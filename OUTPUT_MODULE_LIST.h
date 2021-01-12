#pragma once
#include <string>
#include <unordered_map>
#include "UI_ANNOTATION.h"
class OUTPUT_MODULE_VALUE;
struct OUTPUT_MODULE_DATA {
	OUTPUT_MODULE_VALUE* Module = nullptr;
	UI_ANNOTATION Annotation;
};
class OUTPUT_MODULE_LIST{
public:
	using LIST = std::unordered_map < std::string, OUTPUT_MODULE_DATA>;
	OUTPUT_MODULE_LIST();
	OUTPUT_MODULE_LIST(LIST&& list);
	~OUTPUT_MODULE_LIST();
	LIST* list() { return &List; }
private:
	LIST List;
};

