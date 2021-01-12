#include "DRAWER_TREE.h"
#include "DRAWER_FONT.h"
namespace DRAWER {
	void FONT::create(const char* fontFileName, const char* fontName, const char* string, int fontSize){
		if (Font.isRelease()) { Font.releaseAllFont(); }
		Font.addUserFont(fontFileName, fontName);
		Font.create(FONT_SET_1, string, USER_FONT, fontSize);
		Font.releaseUserFont();
		FontSize = fontSize;
		String = string;
	}
	void FONT::draw(SHADER* shader){
		(this->*DrawMethod)(shader);
	}
	VECTOR2 FONT::wh() {
		if (DrawMethod== drawMethodDefault()){
			return VECTOR2((float)LIBRARY_FONT::stringWidth(String.c_str(), FontSize), (float)FontSize);
		}
		if (DrawMethod == drawMethodAdjustDraw_Over()) {
			return VECTOR2(MaxWidth, (float)FontSize);
		}
		return VECTOR2();
	}
	void FONT::drawInvisible(SHADER* shader){

	}
	void FONT::drawDefault(SHADER* shader){
		Font.draw(shader, FONT_SET_1, String.c_str(), Pos, Scale, Color);
	}
	void FONT::drawAdjustDraw_Over(SHADER* shader){
		Font.adjustDraw_Over(shader, FONT_SET_1, String.c_str(),MaxWidth, Pos, Scale, Color);
	}
}
