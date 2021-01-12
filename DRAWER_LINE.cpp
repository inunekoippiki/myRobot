#include "../Library/TEXTURE.h"
#include "DRAWER_LINE.h"
namespace DRAWER {
	void LINE::create() {}
	void LINE::draw(SHADER* shader) {
		Texture->drawLine(shader, Pos1, Pos2,Width,Color);
	}
}
