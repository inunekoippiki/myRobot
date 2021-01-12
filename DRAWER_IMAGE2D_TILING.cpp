#include "../Library/TEXTURE.h"
#include "../Library/DEBUG_STR.h"
#include "DRAWER_IMAGE2D_TILING.h"
namespace DRAWER {
	void IMAGE2D_TILING::create() {}
	void IMAGE2D_TILING::draw(SHADER* shader) {
		VECTOR2 space = (Texture->wh() * Scale);
		VECTOR2 offset = (Pos-RangePosSt);
		if (offset.x < 0.0f) {
			offset.x += ((int)(-offset.x / space.x)+1)* space.x;
		}
		if (offset.y < 0.0f) {
			offset.y += ((int)(-offset.y / space.y)+1) * space.y;
		}

		VECTOR2 shift = (space - (offset- VECTOR2((float)(int)(offset.x / space.x), (float)(int)(offset.y / space.y)) * space));
		VECTOR2 pos = RangePosSt  - shift;
		int ix = (int)((RangePosEd.x - RangePosSt.x) / space.x + 2);
		int iy = (int)((RangePosEd.y - RangePosSt.y) / space.y + 2);
		for (int y = 0;y < iy;y++) {
			for (int x = 0;x < ix;x++) {
				Texture->draw(shader, pos +VECTOR2(space.x *x, space.y * y), Scale, Color);
			}
		}
	}
	VECTOR2 IMAGE2D_TILING::wh() {
		return  RangePosEd - RangePosSt;
	}
	VECTOR2 IMAGE2D_TILING::actualWh() {
		return wh() *Scale;
	}
	IMAGE2D_TILING* IMAGE2D_TILING::instance(TEXTURE* texture, const VECTOR2& pos, const VECTOR2& scale) {
		IMAGE2D_TILING* p = new IMAGE2D_TILING;
		p->setTexture(texture);
		p->setPos(pos);
		p->setScale(scale);
		return p;
	}
	void IMAGE2D_TILING::minusWhFix(const VECTOR2& pos1, const VECTOR2& pos2) {
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
