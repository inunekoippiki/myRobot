#pragma once
#include "../Library/VECTOR3.h"
class STATIC_FONT;
namespace DRAWER {
	class STATIC_FONT;
	class DRAWERS_SHADER;
}
class ACCESSORY_NUMBER_POPUP{
public:
	ACCESSORY_NUMBER_POPUP();
	~ACCESSORY_NUMBER_POPUP();
	void create(STATIC_FONT* font, DRAWER::DRAWERS_SHADER* drawers2d);
	void pop(int damage,const VECTOR3& pos);
	void update();
private:
	DRAWER::STATIC_FONT* Drawer = nullptr;
	VECTOR3 Pos;
	int Frame = 0;
};

