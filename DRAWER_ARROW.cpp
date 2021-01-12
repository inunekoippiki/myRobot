#include "../Library/collisionUtil.h"
#include "../Library/TEXTURE.h"
#include "../Library/GRAPHIC.h"
#include "DRAWER_ARROW.h"
namespace DRAWER {
	int ARROW::drawCallCnt = 0;
	void ARROW::draw(SHADER* shader) {
		if (IsInvisible) return;
		auto p = *Points;
		size_t num = *Num;
		if (num == 0)  return; 
		for (size_t i = 0;i < num - 1;i++) {
			const VECTOR2& p2 = p[i + 1];
			//•Ð•û‚Ì“_‚Å‚à•`‰æ‚ª•K—v‚È‚ç•`‰æ‚·‚é
			if (isNecessaryDraw(p[i], p2)) {
				drawCallCnt++;
				Texture->drawLine(shader, p[i], p2, LineWidth, Color);
			}
		}
		TextureEnd->draw(shader, p[num - 1], 0.0f, VECTOR2(LineWidth, LineWidth), Color);
	}

	bool ARROW::isNecessaryDraw(const VECTOR2& p1,const VECTOR2& p2) {
		GRAPHIC* g = GRAPHIC::instance();
		float sx = min(p1.x, p2.x);
		float ex = max(p1.x, p2.x);
		float sy = min(p1.y, p2.y);
		float ey = max(p1.y, p2.y);
		return 0.0f < ex + LineWidth && 0.0f < ey + LineWidth && g->baseWidth() > sx - LineWidth && g->baseHeight() > sy - LineWidth;

	}
}
