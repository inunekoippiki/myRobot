#pragma once
#include <string>
class UI_ANNOTATION{
public:
	UI_ANNOTATION();
	~UI_ANNOTATION();
	void setAnnotationString(const std::string& annotationString) { AnnotationString = annotationString; }
	std::string annotationString() { return AnnotationString; }
	bool isEmpty() {return AnnotationString.empty();}
private:
	std::string AnnotationString;
};

