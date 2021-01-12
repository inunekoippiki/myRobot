#pragma once
#include "../Library/COLOR.h"
#include "../Library/MATRIX.h"
#include "../Library/VECTOR3.h"
#include "../Library/VECTOR2.h"
#include "DRAWER.h"
class SHADER;
class TEXTURE;
namespace DRAWER {
	class IMAGE3D :public BASE {
	public:
		using DRAW_METHOD = void (IMAGE3D::*)(SHADER * shader);
		IMAGE3D() :
			Scale(VECTOR2(1.0f, 1.0f)),
			DrawMethod(&IMAGE3D::drawCentered)
		{
		};
		~IMAGE3D() {};
		void create();
		void setPivot(DRAW_METHOD drawMethod) { DrawMethod = drawMethod; }
		void setTexture(TEXTURE* texture) { Texture = texture; }
		void setPos(const VECTOR3& pos) { Pos = pos; }
		void setScale(const VECTOR2& scale) { Scale = scale; }
		void setColor(const COLOR& color) { Color = color; }
		static void setProjView(const MATRIX& projView) { ProjView = projView; }
		void draw(SHADER* shader)override;

		//ÉQÉbÉ^Å[
		VECTOR3 pos() { return Pos; }
		VECTOR2 scale() { return Scale; }
		VECTOR2 wh();
		VECTOR2 actualWh();
		VECTOR2 drawPos();
		VECTOR2 drawScale();
		bool isInvisible() { return (DrawMethod == drawMethodInvisible()); }
		static DRAW_METHOD drawMethodInvisible() { return &IMAGE3D::drawInvisible; }
		static DRAW_METHOD drawMethodCentered() { return &IMAGE3D::drawCentered; }
		static DRAW_METHOD drawMethodLeft() { return &IMAGE3D::drawLeft; }
		static MATRIX ProjView;
	private:
		void drawInvisible(SHADER* shader);
		void drawCentered(SHADER* shader);
		void drawLeft(SHADER* shader);

		DRAW_METHOD DrawMethod = nullptr;
		TEXTURE* Texture = nullptr;
		VECTOR3 Pos;
		VECTOR3 DrawPos;
		VECTOR2 DrawScale;
		VECTOR2 Scale;
		COLOR Color;
		float Rad = 0.0f;
	};
}