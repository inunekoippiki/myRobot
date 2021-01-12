#pragma once
#include <string>
#include "../Library/FONT.h"
#include "../Library/VECTOR2.h"
#include "../Library/COLOR.h"
#include "DRAWER.h"
class SHADER;
using LIBRARY_FONT = FONT;
namespace DRAWER {
	class FONT :public BASE {
	using DRAW_METHOD = void (FONT::*)(SHADER * shader);
	public:
		FONT() :
			Scale(VECTOR2::one()),
			DrawMethod(drawMethodDefault()) {

		};
		~FONT() {};
		void create(const char* fontFileName,const char* fontName,const char* string , int fontSize);
		void setPos(const VECTOR2& pos) { Pos = pos; }
		void setScale(const VECTOR2& scale) { Scale = scale; }
		void setDrawMethod(DRAW_METHOD drawMethod) { DrawMethod = drawMethod; }
		void setColor(const COLOR& color) { Color = color; }
		//スケール掛ける前
		void setMaxWidth(float maxWidth) { MaxWidth = maxWidth; }
		void draw(SHADER* shader)override;
		VECTOR2 pos() { return Pos; }
		VECTOR2 scale() { return Scale; }
		VECTOR2 wh();
		static DRAW_METHOD drawMethodInvisible() { return &FONT::drawInvisible; }
		static DRAW_METHOD drawMethodDefault() { return &FONT::drawDefault; }
		static DRAW_METHOD drawMethodAdjustDraw_Over() { return &FONT::drawAdjustDraw_Over; }
	private:
		void drawInvisible(SHADER* shader);
		void drawDefault(SHADER* shader);
		void drawAdjustDraw_Over(SHADER* shader);
		DRAW_METHOD DrawMethod = nullptr;
		VECTOR2 Pos;
		VECTOR2 Scale;
		COLOR Color;
		std::string String;
		int FontSize = 0;
		float MaxWidth = 0.0;
		LIBRARY_FONT Font;
	};
}