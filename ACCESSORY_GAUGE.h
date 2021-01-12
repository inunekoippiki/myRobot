#pragma once
class CONTAINER;
namespace DRAWER {
	class IMAGE3D;
	class DRAWERS_SHADER;
}
//HP�o�[�Ƃ��\������p
class ACCESSORY_GAUGE{
public:
	ACCESSORY_GAUGE();
	~ACCESSORY_GAUGE();
	void create(CONTAINER* c, DRAWER::DRAWERS_SHADER* drawers2d);
	void setRatio(float ratio);
	void setPos(const VECTOR3& pos);

private:
	DRAWER::IMAGE3D* Drawer = nullptr;
};

