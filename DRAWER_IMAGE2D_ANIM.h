#pragma once
#include "../Library/COLOR.h"
#include "../Library/VECTOR2.h"
#include "DRAWER.h"
class SHADER;
class TEXTURE;
namespace DRAWER {
	class IMAGE2D_ANIM :public BASE {
	public:
		IMAGE2D_ANIM() :
			Scale(VECTOR2::one()),
			Scale1(VECTOR2::one()),
			Scale2(VECTOR2::one())
		{
		};
		~IMAGE2D_ANIM() {};
		void create();
		void setTexture(TEXTURE* texture) { Texture = texture; }
		void setPos(const VECTOR2& pos) { Pos = pos; }
		void setScale(const VECTOR2& scale) { Scale = scale; }
		void setColor(const COLOR& color) { Color = color; }
		void draw(SHADER* shader)override;
		void update();
		void setAnimSpeed(double animSpeed) { AnimSpeed = animSpeed; }
		void timeReset() { Time = 0.0; }
		void setTime(double time) { Time = time; }
		void minusWhFix(const VECTOR2& pos1, const VECTOR2& pos2);
		//ゲッター
		VECTOR2 pos() { return Pos; }
		VECTOR2 scale() { return Scale; }
		VECTOR2 wh();//元の画像のサイズ
		VECTOR2 actualWh();//描画時のサイズ
		COLOR color() { return Color; }
		static IMAGE2D_ANIM* instance(TEXTURE* texture, const VECTOR2& pos, const VECTOR2& scale);
	private:
		TEXTURE* Texture = nullptr;
		VECTOR2 Pos;
		VECTOR2 Scale;
		COLOR Color;
		double Time = 0.0f;//0~1
		double AnimSpeed = 0.0f;

		//今
		VECTOR2 Pos_;
		VECTOR2 Scale_;
		COLOR Color_;
		//始点
		VECTOR2 Pos1;
		VECTOR2 Scale1;
		COLOR Color1;
		//終点
		VECTOR2 Pos2;
		VECTOR2 Scale2;
		COLOR Color2;

	};
}