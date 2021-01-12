#pragma once
#include <string>
#include "../Library/STATIC_FONT.h"
#include "../Library/VECTOR2.h"
#include "../Library/COLOR.h"
#include "DRAWER.h"
class SHADER;
using LIBRARY_STATIC_FONT = STATIC_FONT;
namespace DRAWER {
	class STATIC_FONT :public BASE {
		using DRAW_METHOD = void (STATIC_FONT::*)(SHADER * shader);
	public:
		STATIC_FONT();;
		~STATIC_FONT() {};
		void create(LIBRARY_STATIC_FONT* font);
		void create(const char* string, LIBRARY_STATIC_FONT* font);
		void create(const char* string, LIBRARY_STATIC_FONT* font, const VECTOR2& pos, const VECTOR2& scale, DRAW_METHOD drawMethod, const COLOR& color = COLOR(1.0f, 1.0f, 1.0f, 1.0f));
		void setString(const char* string) { String = string; }
		void setString(const std::string& string) { String = string; }
		void setPos(const VECTOR2& pos);
		void setScale(const VECTOR2& scale) { Scale = scale; }
		void setDrawMethod(DRAW_METHOD drawMethod) { DrawMethod = drawMethod; }
		void setColor(const COLOR& color) { Color = color; }
		//ÉoÉCÉgêî
		void setMaxWidth(int maxWidth) { MaxWidth = maxWidth; }
		void draw(SHADER* shader)override;
		VECTOR2 pos();
		VECTOR2 scale() { return Scale; }
		VECTOR2 wh();
		std::string string() { return String; }
		COLOR color() { return Color; }
		static DRAW_METHOD drawMethodInvisible() { return &STATIC_FONT::drawInvisible; }
		static DRAW_METHOD drawMethodDefault() { return &STATIC_FONT::drawDefault; }
		static DRAW_METHOD drawMethodAdjustDraw_Over() { return &STATIC_FONT::drawAdjustDraw_Over; }
	private:
		void drawInvisible(SHADER* shader);
		void drawDefault(SHADER* shader);
		void drawAdjustDraw_Over(SHADER* shader);
		DRAW_METHOD DrawMethod = nullptr;
		VECTOR2 Pos;
		VECTOR2 Scale;
		COLOR Color;
		std::string String;
		int MaxWidth = 0;
		LIBRARY_STATIC_FONT* Font = nullptr;
	public:
		static STATIC_FONT* instance(const char* string, LIBRARY_STATIC_FONT* font,const VECTOR2& pos,const VECTOR2& scale, DRAW_METHOD drawMethod,const COLOR& color = COLOR(1.0f,1.0f,1.0f,1.0f));
		static STATIC_FONT* instance(const char* string, LIBRARY_STATIC_FONT* font, const VECTOR2& pos, const VECTOR2& scale, const COLOR& color = COLOR(1.0f, 1.0f, 1.0f, 1.0f));
	};
}