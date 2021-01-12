#pragma once
#include "../Library/COLOR.h"
#include "../Library/VECTOR2.h"
#include "DRAWER.h"
class SHADER;
class TEXTURE;
namespace DRAWER {
	class DUMMY_IMAGE2D :public BASE {
	public:
		DUMMY_IMAGE2D() :
			Scale(VECTOR2(1.0f, 1.0f))
		{
		};
		~DUMMY_IMAGE2D() {};
		void create();
		void setWh(const VECTOR2& wh) { Wh=wh; }
		void setPos(const VECTOR2& pos) { Pos = pos; }
		void setScale(const VECTOR2& scale) { Scale = scale; }
		void setColor(const COLOR& color) {}
		void draw(SHADER* shader)override;
		//�Q�b�^�[
		VECTOR2 pos() { return Pos; }
		VECTOR2 scale() { return Scale; }
		VECTOR2 wh();//���̉摜�̃T�C�Y
		VECTOR2 actualWh();//�`�掞�̃T�C�Y

		static DUMMY_IMAGE2D* instance(const VECTOR2& wh, const VECTOR2& pos, const VECTOR2& scale);
	private:
		VECTOR2 Wh;
		VECTOR2 Pos;
		VECTOR2 Scale;
	};
}