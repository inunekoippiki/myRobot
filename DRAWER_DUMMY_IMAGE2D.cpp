#include "../Library/TEXTURE.h"
#include "DRAWER_DUMMY_IMAGE2D.h"
namespace DRAWER {
	void DUMMY_IMAGE2D::create() {}
	void DUMMY_IMAGE2D::draw(SHADER* shader) {
	}
	VECTOR2 DUMMY_IMAGE2D::wh() {
		return Wh;
	}
	VECTOR2 DUMMY_IMAGE2D::actualWh() {
		return wh() * scale();
	}
	DUMMY_IMAGE2D* DUMMY_IMAGE2D::instance(const VECTOR2& wh, const VECTOR2& pos, const VECTOR2& scale) {
		DUMMY_IMAGE2D* p = new DUMMY_IMAGE2D;
		p->setWh(wh);
		p->setPos(pos);
		p->setScale(scale);
		return p;
	}
}
