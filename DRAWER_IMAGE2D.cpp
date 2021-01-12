#include "../Library/TEXTURE.h"
#include "DRAWER_IMAGE2D.h"
namespace DRAWER {
	void IMAGE2D::create(){}
	void IMAGE2D::draw(SHADER* shader){
		(this->*DrawMethod)(shader);
	}
	VECTOR2 IMAGE2D::wh() {
		return Texture->wh();
	}
	VECTOR2 IMAGE2D::actualWh(){
		return wh() * scale();
	}
	VECTOR2 IMAGE2D::topLeftPos(){
		if (DrawMethod == drawMethodCentered()) {
			return Pos - actualWh() * 0.5f;
		}
		return Pos;
	}
	IMAGE2D* IMAGE2D::instance(TEXTURE* texture, const VECTOR2& pos, const VECTOR2& scale, DRAW_METHOD drawMethod){
		IMAGE2D* p = new IMAGE2D;
		p->setTexture(texture);
		p->setPos(pos);
		p->setScale(scale);
		p->setPivot(drawMethod);
		return p;
	}
	IMAGE2D* IMAGE2D::instance(TEXTURE* texture, const VECTOR2& pos, const VECTOR2& scale){
		IMAGE2D* p = new IMAGE2D;
		p->setTexture(texture);
		p->setPos(pos);
		p->setScale(scale);
		return p;
	}
	void IMAGE2D::drawInvisible(SHADER* shader){
	}
	void IMAGE2D::drawCentered(SHADER* shader) {
		Texture->draw(shader, Pos, Rad, Scale, Color);
	}
	void IMAGE2D::drawLeft(SHADER* shader) {
		Texture->draw(shader, Pos, Scale, Color);
	}
	void IMAGE2D::minusWhFix(const VECTOR2& pos1, const VECTOR2& pos2) {
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
