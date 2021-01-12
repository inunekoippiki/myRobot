#pragma once
#include "../Library/VECTOR3.h"
#include "CAMERA.h"
class MATRIX;
class CONTAINER;
class STRING_TREE;
class CAMERA_DEBUG :public CAMERA{
public:
	CAMERA_DEBUG();
	CAMERA_DEBUG(CONTAINER* container);
	CAMERA_DEBUG(const STRING_TREE& dataTree);
	~CAMERA_DEBUG();
	void create(const STRING_TREE& dataTree);
	void reset();
	void update()override;
	void viewUpdate();
	void setLookVec(const VECTOR3& lookVec) { LookVec = lookVec; }
	void setCameraPos(const VECTOR3& pos) { Pos = pos; }
	VECTOR3 lookatVec()const;
	VECTOR3 cameraPos()const;
	float verticalRad()const;
	float horizontalRad()const;
	void setRotateSpeed(float rotateSpeed) { RotateSpeed = rotateSpeed; }
	MATRIX view()const { return View; }
	MATRIX proj()const { return Proj; }
	MATRIX rotateMatrix()const;
	MATRIX projView()const;
private:
	void mouseScroll();
	void keyScroll();
	//äeï˚å¸(ÉçÅ[Éãñ≥Çµ,ê≥ãKâªÇ»Çµ)
	VECTOR3 VecFlont()const;
	VECTOR3 VecBack()const;
	VECTOR3 VecRight()const;
	VECTOR3 VecLeft()const;

	VECTOR3 InitCameraPos;
	float InitVerticalRad = 0.0f;
	float InitHorizontalRad = 0.0f;

	VECTOR3 LookVec;
	float VerticalRad = 0.0f;
	float HorizontalRad = 0.0f;

	float BaseRotateSpeed = 0.0f;
	float RotateSpeed = 0.0f;
	float ZoomSpeed = 0.0f;
};