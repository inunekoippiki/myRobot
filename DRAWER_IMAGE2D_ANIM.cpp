#include <cmath>
#include "../Library/TEXTURE.h"
#include "DRAWER_IMAGE2D_ANIM.h"
namespace DRAWER {
	void IMAGE2D_ANIM::create() {}
	void IMAGE2D_ANIM::draw(SHADER* shader) {
		Texture->draw(shader,
			VECTOR2(Pos.x + Pos_.x* Scale.x, Pos.y + Pos_.y * Scale.y),
			VECTOR2(Scale * Scale_),
			COLOR((Color_.r + Color_.r) * 0.5f, (Color_.g + Color_.g) * 0.5f, (Color_.b + Color_.b) * 0.5f, (Color_.a + Color_.a) * 0.5f)
		);
	}
	void IMAGE2D_ANIM::update(){
		Time += AnimSpeed;
		Pos_.x = std::lerp(Pos1.x, Pos2.x, (float)Time);
		Pos_.y = std::lerp(Pos1.y, Pos2.y, (float)Time);
		Scale.x = std::lerp(Scale.x, Scale.x, (float)Time);
		Scale.y = std::lerp(Scale.y, Scale.y, (float)Time);
		Color_.r = std::lerp(Color1.r, Color2.r, (float)Time);
		Color_.g = std::lerp(Color1.g, Color2.g, (float)Time);
		Color_.b = std::lerp(Color1.b, Color2.b, (float)Time);
		Color_.a =std::lerp(Color1.a, Color2.a, (float)Time);
	}
	VECTOR2 IMAGE2D_ANIM::wh() {
		return Texture->wh();
	}
	VECTOR2 IMAGE2D_ANIM::actualWh() {
		return wh() * scale();
	}

	IMAGE2D_ANIM* IMAGE2D_ANIM::instance(TEXTURE* texture, const VECTOR2& pos, const VECTOR2& scale) {
		IMAGE2D_ANIM* p = new IMAGE2D_ANIM;
		p->setTexture(texture);
		p->setPos(pos);
		p->setScale(scale);
		return p;
	}
	void IMAGE2D_ANIM::minusWhFix(const VECTOR2& pos1, const VECTOR2& pos2) {
		if (pos1.x > pos2.x) {
			Pos.x = pos2.x;
			Scale.x = pos1.x - pos2.x;
		}
		else {
			Pos.x = pos1.x;
			Scale.x = pos2.x - pos1.x;
		}
		if (pos1.y > pos2.y) {
			Pos.y = pos2.y;
			Scale.y = pos1.y - pos2.y;
		}
		else {
			Pos.y = pos1.y;
			Scale.y = pos2.y - pos1.y;
		}
	}
}
