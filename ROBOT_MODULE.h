#pragma once
#include <unordered_map>
#include "UI_ANNOTATION.h"
class STRING_TREE;
//ƒ‚ƒWƒ…[ƒ‹‚Ìî•ñ‚ğ•Û‚·‚é
class ROBOT_MODULE{
public:
	ROBOT_MODULE(STRING_TREE* stringTree);
	ROBOT_MODULE(const std::string& fileName);
	~ROBOT_MODULE();
	UI_ANNOTATION uiAnnotation(const std::string& tag);
private:
	void create(STRING_TREE* stringTree);
	std::unordered_map<std::string, std::pair<double, UI_ANNOTATION>> ModuleList;
};

