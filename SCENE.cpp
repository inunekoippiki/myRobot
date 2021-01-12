#include "SCENE.h"
COMMON_DATA* SCENE::CommonData = nullptr;
CONTAINER* SCENE::C = nullptr;
STATIC_FONT* SCENE::Font = nullptr;
IMAGE_2D* SCENE::Image2d = nullptr;
SOFT_SHADOW* SCENE::SoftShadow = nullptr;
COMMON_DATA* SCENE::commonData(){
	return CommonData;
}

CONTAINER* SCENE::c(){
	return C;
}

STATIC_FONT* SCENE::font(){
	return Font;
}

IMAGE_2D* SCENE::image2d(){
	return Image2d;
}

SOFT_SHADOW* SCENE::softShadow(){
	return SoftShadow;
}
