#include "../Library/TEXTURE.h"
#include "../Library/GRAPHIC.h"
#include "DRAWER_IMAGE3D.h"
namespace DRAWER {
	MATRIX IMAGE3D::ProjView;
	void IMAGE3D::create() {}
	void IMAGE3D::draw(SHADER* shader) {
		(this->*DrawMethod)(shader);
	}
	VECTOR2 IMAGE3D::wh() {
		return Texture->wh();
	}
	VECTOR2 IMAGE3D::actualWh() {
		return wh() * scale();
	}
	VECTOR2 IMAGE3D::drawPos() { 
		return DrawPos.xy() ;
	}
	VECTOR2 IMAGE3D::drawScale() { 
		return DrawScale * Texture->wh();
	}
	void IMAGE3D::drawInvisible(SHADER* shader) {
	}
	void IMAGE3D::drawCentered(SHADER* shader) {
		GRAPHIC* g = GRAPHIC::instance();
		DrawPos = Pos;
		DrawPos = ProjView * DrawPos;
		if (DrawPos.z > 0.0f) {
			DrawPos.x = (((DrawPos.x / DrawPos.z) + 1.0f) * (g->baseWidth() / 2.0f));
			DrawPos.y = (((-DrawPos.y / DrawPos.z) + 1.0f) * (g->baseHeight() / 2.0f));
			float z = 1.0f / DrawPos.z;
			DrawScale = VECTOR2(z * Scale.x, z * Scale.y);
			Texture->draw(shader, DrawPos.xy(), 0.0f, DrawScale,Color);
			DrawPos -= VECTOR3(DrawScale.x * 0.5f*Texture->wh().x, DrawScale.y * 0.5f * Texture->wh().y,0.0f);
		}
	}
	void IMAGE3D::drawLeft(SHADER* shader) {
		GRAPHIC* g = GRAPHIC::instance();
		DrawPos = Pos;
		DrawPos = ProjView * DrawPos;
		if (DrawPos.z > 0.0f) {
			DrawPos.x = (((DrawPos.x / DrawPos.z) + 1.0f) * (g->baseWidth() / 2.0f));
			DrawPos.y = (((-DrawPos.y / DrawPos.z) + 1.0f) * (g->baseHeight() / 2.0f));
			float z = 1.0f / DrawPos.z;
			float yScale = z * Scale.y;
			DrawScale = VECTOR2(z * Scale.x, yScale);
			DrawPos += VECTOR3(0.0f, -Texture->height() * 0.5f * yScale,0.0f);
			Texture->draw(shader, DrawPos.xy(), DrawScale, Color);
		}
	}
}
