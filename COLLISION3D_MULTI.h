#pragma once
#include <vector>
#include "COLLISION3D.h"
class COLLISION3D_MULTI:public COLLISION3D{
public:
	COLLISION3D_MULTI(ENTITY::ENTITY* entity);
	~COLLISION3D_MULTI();
	std::vector<COLLISION3D*>* collision() { return &Collisions; }
private:
	std::vector<COLLISION3D*> Collisions;
};

