#pragma once
#include "../Library/COLOR.h"
#include "../Library/VECTOR2.h"
#include "DRAWER.h"
class SHADER;
class TEXTURE;
namespace DRAWER {
	class LINE :public BASE {
	public:
		LINE() :
			Width(1.0f){
		};
		~LINE() {};
		void create();
		void setTexture(TEXTURE* texture) { Texture = texture; }
		void setPos1(const VECTOR2& pos1) { Pos1 = pos1; }
		void setPos2(const VECTOR2& pos2) { Pos2 = pos2; }
		void setColor(const COLOR& color) { Color = color; }
		void draw(SHADER* shader)override;
	private:
		TEXTURE* Texture = nullptr;
		VECTOR2 Pos1;
		VECTOR2 Pos2;
		float Width = 0.0f;
		COLOR Color;
		float Rad = 0.0f;
	};
}