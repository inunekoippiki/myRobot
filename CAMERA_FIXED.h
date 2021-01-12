#pragma once
#include "CAMERA.h"
class STRING_TREE;
class CAMERA_FIXED:public CAMERA{
public:
	CAMERA_FIXED();
	~CAMERA_FIXED();
	void create(const STRING_TREE& dataTree);
	void update()override;
	void setPos(const VECTOR3& pos);
	void setLookAt(const VECTOR3& lookAt);
private:
	VECTOR3 LookAt;
};

