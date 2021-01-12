#include "../Library/VECTOR2.h"
#include "DRAWER_IMAGE2D.h"
#include "DRAWER_EMPTY.h"
#include "UI.h"
#include "UI_FACTORY.h"
UI* UI_FACTORY::instance(TEXTURE* texture, const VECTOR2& pos, const VECTOR2& scale){
	UI* ui = new UI;
	DRAWER::IMAGE2D* Image = new DRAWER::IMAGE2D;
	Image->setPos(pos);
	Image->setScale(scale);
	Image->setTexture(texture);
	Image->setPivot(Image->drawMethodLeft());
	ui->create(Image);
	return ui;
}

UI* UI_FACTORY::instance(TEXTURE* texture, const VECTOR2& pos, const VECTOR2& scale, const COLOR& color){
	UI* ui = new UI;
	DRAWER::IMAGE2D* Image = new DRAWER::IMAGE2D;
	Image->setPos(pos);
	Image->setScale(scale);
	Image->setTexture(texture);
	Image->setColor(color);
	Image->setPivot(Image->drawMethodLeft());
	ui->create(Image);
	return ui;
}

UI* UI_FACTORY::instanceEmpty(){
	return instance(new DRAWER::EMPTY);
}
