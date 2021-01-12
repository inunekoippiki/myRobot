#pragma once
#include <vector>
#include "../Library/TEXTURE.h"
#include "../Library/VECTOR2.h"
class GRAPHIC;
class CONTAINER;
class CONTAINER_LOAD_THREAD;
class IMAGE_2D;
//ÉçÅ[ÉhâÊñ ââèo
class LOAD_DISP {
public:
	LOAD_DISP(CONTAINER* container);
	~LOAD_DISP();
	void addLoadContainer(CONTAINER* container);
	void startProc();
private:
	std::vector< CONTAINER_LOAD_THREAD*> ContainerLoadThread;
	IMAGE_2D* Shader = nullptr;
	GRAPHIC* G = nullptr;
	TEXTURE Texture;
	COLOR Color;
	VECTOR2 Pos;

	int Sw = 0;
	float AnimSpeed = 0;
	float TempAnimPlay = 0.0f;
	int Frame = 0;
	bool LoopFlag = false;
};

