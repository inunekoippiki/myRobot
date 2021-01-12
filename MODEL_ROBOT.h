#pragma once
#include "../Library/TREE.h"
class CONTAINER;
namespace DRAWER {
	class DRAWERS_SHADER;
	class TREE;
	class TREE2;
	class BATCH2;
}
class MODEL_ROBOT{
public:
	MODEL_ROBOT();
	~MODEL_ROBOT();
	void create(CONTAINER* c, DRAWER::DRAWERS_SHADER* drawers3d);
	void setPos(const VECTOR3& pos);
	void update(const VECTOR3& pos,float ry,const VECTOR3& canonRad);
	void lWheelRotate(float rad);
	void rWheelRotate(float rad);
	VECTOR3 canonPos()const;
	VECTOR3 canonTipPos()const;
	VECTOR3 topPos()const;
	VECTOR3 minPos()const;
	VECTOR3 scale()const;
private:
	TREE Tree;
	DRAWER::TREE* Drawer = nullptr;
	TREE CanonTree;
	DRAWER::TREE2* CanonDrawer = nullptr;
	DRAWER::BATCH2* LWheel = nullptr;
	DRAWER::BATCH2* RWheel = nullptr;

	const MATRIX* CanonBarrelLocator = nullptr;
	const MATRIX* CanonRootLocator = nullptr;
	const MATRIX* LWheelLocator = nullptr;
	const MATRIX* RWheelLocator = nullptr;

};

