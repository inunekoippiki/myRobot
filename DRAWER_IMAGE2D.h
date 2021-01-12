#pragma once
#include "../Library/COLOR.h"
#include "../Library/VECTOR2.h"
#include "DRAWER.h"
class SHADER;
class TEXTURE;
namespace DRAWER {
	class IMAGE2D :public BASE {
	public:
		using DRAW_METHOD = void (IMAGE2D::*)(SHADER * shader);
		IMAGE2D():
			Scale(VECTOR2(1.0f,1.0f)),
			DrawMethod(&IMAGE2D::drawLeft)
		{
		};
		~IMAGE2D() {};
		void create();
		void setPivot(DRAW_METHOD drawMethod) { DrawMethod = drawMethod; }
		void setTexture(TEXTURE* texture) { Texture = texture; }
		void setPos(const VECTOR2& pos) { Pos = pos; }
		void setScale(const VECTOR2& scale) { Scale = scale; }
		void setColor(const COLOR& color) { Color = color; }
		void draw(SHADER* shader)override;
		void minusWhFix(const VECTOR2& pos1, const VECTOR2& pos2);

		//ゲッター
		VECTOR2 pos() { return Pos; }
		VECTOR2 scale() { return Scale; }
		VECTOR2 wh();//元の画像のサイズ
		VECTOR2 actualWh();//描画時のサイズ
		COLOR color() { return Color; }
		bool isInvisible() { return (DrawMethod == drawMethodInvisible()); }
		VECTOR2 topLeftPos();

		static DRAW_METHOD drawMethodInvisible() { return &IMAGE2D::drawInvisible; }
		static DRAW_METHOD drawMethodCentered() { return &IMAGE2D::drawCentered; }
		static DRAW_METHOD drawMethodLeft() { return &IMAGE2D::drawLeft; }

		static IMAGE2D* instance(TEXTURE* texture,const VECTOR2& pos, const VECTOR2& scale, DRAW_METHOD drawMethod);
		static IMAGE2D* instance(TEXTURE* texture, const VECTOR2& pos, const VECTOR2& scale);
	private:
		void drawInvisible(SHADER* shader);
		void drawCentered(SHADER* shader);
		void drawLeft(SHADER* shader);

		DRAW_METHOD DrawMethod = nullptr;
		TEXTURE* Texture = nullptr;
		VECTOR2 Pos;
		VECTOR2 Scale;
		COLOR Color;
		float Rad = 0.0f;
	};
}