#pragma once
#include <array>
#include "../Library/VECTOR2.h"
#include "DRAWER.h"
class TEXTURE;
class SHADER;
class COLOR;
//折れ線矢印を描画するクラス
namespace DRAWER {
	class ARROW :public BASE {
	public:
		ARROW(std::array<VECTOR2, 6>* points, size_t* num) :
			Points(points),
			Num(num) {
		}
		void draw(SHADER* shader);
		//線の太さを設定する。テクスチャサイズで可変
		void setLineWidth(float lineWidth) { LineWidth = lineWidth; }
		//矢印の線の部分のテクスチャを設定する
		void setTexture(TEXTURE* texture) { Texture = texture; }
		//矢印の先端のテクスチャを設定する
		void setTextureEnd(TEXTURE* textureEnd) { TextureEnd = textureEnd; }
		void setColor(const COLOR& color) { Color = color; }
		void setIsInvisible(bool isInvisible) { IsInvisible = isInvisible; }
		//デバック用
		static int drawCallCnt;
	private:
		//その点が画面上にあるかを返す
		bool isNecessaryDraw(const VECTOR2& p1, const VECTOR2& p2);
		std::array<VECTOR2, 6>* Points = nullptr;
		size_t* Num = nullptr;
		float LineWidth = 0.0f;
		TEXTURE* Texture = nullptr;
		TEXTURE* TextureEnd = nullptr;
		COLOR Color;
		bool IsInvisible = false;
	};
}
