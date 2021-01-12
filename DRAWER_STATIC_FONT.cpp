#include "DRAWER_TREE.h"
#include "DRAWER_STATIC_FONT.h"
namespace DRAWER {
	STATIC_FONT::STATIC_FONT() :
		Scale(VECTOR2::one()),
		DrawMethod(drawMethodDefault()) {

	}
	void STATIC_FONT::create(LIBRARY_STATIC_FONT* font){
		Font = font;
	}
	void STATIC_FONT::create(const char* string, LIBRARY_STATIC_FONT* font){
		Font = font;
		String = string;
	}
	void STATIC_FONT::create(const char* string, LIBRARY_STATIC_FONT* font, const VECTOR2& pos, const VECTOR2& scale, DRAW_METHOD drawMethod, const COLOR& color){
		create(string, font);
		Pos =pos;
		Scale=scale;
		DrawMethod=drawMethod;
		Color =color;
	}
	void STATIC_FONT::setPos(const VECTOR2& pos) {
		Pos = pos;
	}
	void STATIC_FONT::draw(SHADER* shader) {
		(this->*DrawMethod)(shader);
	}
	VECTOR2 STATIC_FONT::pos() {
		return Pos; 
	}
	VECTOR2 STATIC_FONT::wh() {
		if (DrawMethod == drawMethodDefault()) {
			return VECTOR2(LIBRARY_STATIC_FONT::stringWidth(String.c_str()) * 0.5f,1.0f);
		}
		if (DrawMethod == drawMethodAdjustDraw_Over()) {
			return VECTOR2(MaxWidth*0.5f, 1.0f);
		}
		return VECTOR2();
	}
	void STATIC_FONT::drawInvisible(SHADER* shader) {

	}
	void STATIC_FONT::drawDefault(SHADER* shader) {
		Font->draw(shader, String.c_str(), Pos, Scale, Color);
	}
	void STATIC_FONT::drawAdjustDraw_Over(SHADER* shader) {
		Font->adjustDraw_Over(shader, String.c_str(), MaxWidth, Pos, Scale, Color);
	}
	STATIC_FONT* STATIC_FONT::instance(const char* string, LIBRARY_STATIC_FONT* font, const VECTOR2& pos, const VECTOR2& scale, DRAW_METHOD drawMethod, const COLOR& color){
		STATIC_FONT* p = new STATIC_FONT();
		p->create(string, font);
		p->setPos(pos);
		p->setScale(scale);
		p->setDrawMethod(drawMethod);
		p->setColor(color);
		return p;
	}
	STATIC_FONT* STATIC_FONT::instance(const char* string, LIBRARY_STATIC_FONT* font, const VECTOR2& pos, const VECTOR2& scale, const COLOR& color){
		return instance(string,font,pos,scale, drawMethodDefault(), color);
	}
}
