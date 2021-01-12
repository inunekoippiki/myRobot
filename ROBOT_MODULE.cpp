#include "../Library/STRING_TREE.h"
#include "../Library/MB_LIB.h"
#include "UI_ANNOTATION.h"
#include "ROBOT_MODULE.h"
ROBOT_MODULE::ROBOT_MODULE(STRING_TREE* stringTree) {
	create(stringTree);
}

ROBOT_MODULE::ROBOT_MODULE(const std::string& fileName){
	STRING_TREE tree(STRING_TREE::loadFile(fileName));
	create(&tree);
}

ROBOT_MODULE::~ROBOT_MODULE() {
}

UI_ANNOTATION ROBOT_MODULE::uiAnnotation(const std::string& tag){
	return ModuleList.at(tag).second;
}


void ROBOT_MODULE::create(STRING_TREE* stringTree){
	STRING_TREE* rootTree = stringTree->atw("root");
	for (auto& i : rootTree->childs()) {
		UI_ANNOTATION uiAnnotation;
		uiAnnotation.setAnnotationString(MB_LIB::replaceText(i->atw("annotation")->data(), "\\n", "\n"));
		ModuleList.insert({ i->atw("tag")->data(), { 0.0f,uiAnnotation } });
	}
}
