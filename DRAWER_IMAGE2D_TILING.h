#pragma once
#include "../Library/COLOR.h"
#include "../Library/VECTOR2.h"
#include "DRAWER.h"
class SHADER;
class TEXTURE;
namespace DRAWER {
	class IMAGE2D_TILING :public BASE {
	public:
		IMAGE2D_TILING() :
			Scale(VECTOR2(1.0f, 1.0f)){
		};
		~IMAGE2D_TILING() {};
		void create();
		void setTexture(TEXTURE* texture) { Texture = texture; }
		void setPos(const VECTOR2& pos) { Pos = pos; }
		void setScale(const VECTOR2& scale) { Scale = scale; }
		void setColor(const COLOR& color) { Color = color; }
		void draw(SHADER* shader)override;
		void minusWhFix(const VECTOR2& pos1, const VECTOR2& pos2);
		void setRangePosSt(const VECTOR2& rangePosSt) { RangePosSt = rangePosSt; }//表示範囲左上
		void setRangePosEd(const VECTOR2& rangePosEd) { RangePosEd = rangePosEd; }//表示範囲右下
		//ゲッター
		VECTOR2 pos() { return Pos; }
		VECTOR2 scale() { return Scale; }
		VECTOR2 wh();//元の画像のサイズ
		VECTOR2 actualWh();//描画時のサイズ
		COLOR color() { return Color; }

		static IMAGE2D_TILING* instance(TEXTURE* texture, const VECTOR2& pos, const VECTOR2& scale);
	private:
		TEXTURE* Texture = nullptr;
		VECTOR2 Pos;
		VECTOR2 RangePosSt;
		VECTOR2 RangePosEd;

		VECTOR2 Scale;
		COLOR Color;
		float Rad = 0.0f;
	};
}