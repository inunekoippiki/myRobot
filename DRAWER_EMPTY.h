#pragma once
#include "../Library/COLOR.h"
#include "../Library/VECTOR2.h"
#include "DRAWER.h"
class SHADER;
class TEXTURE;
namespace DRAWER {
	class EMPTY :public BASE {
	public:
		EMPTY() {};
		~EMPTY() {};
		VECTOR2 pos() { return VECTOR2(); }
		VECTOR2 scale() { return VECTOR2::one(); }
		void draw(SHADER* shader)override {}
		void setPos(const VECTOR2& pos) {}
		void setScale(const VECTOR2& scale) {}
		//ゲッター
		VECTOR2 wh() { return VECTOR2(); }//描画時のサイズ
	private:
	};
}