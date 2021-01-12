#pragma once
#include "DRAWERS_SHADER.h"
#include "SCENE.h"
#include "UI.h"
#include "UI_SCROLL.h"
#include "LIGHT.h"
#include "ENTITY_MANAGER.h"
#include "UI_MANAGER.h"
#include "UI_ANNOTATION_MANAGER.h"
#include "ENTITY_TRANSFORMER.h"
#include "ROUND_MISSION.h"
class CONTAINER;
class STATIC_FONT;
class IMAGE_2D;
class SOFT_SHADOW;
class CAMERA_DEBUG;
class SCENE_MANAGER;
namespace DRAWER {
	class IMAGE2D;
}
class SCENE_MAP_EDIT :public SCENE {
public:
	SCENE_MAP_EDIT(SCENE_MANAGER* sceneManager);
	~SCENE_MAP_EDIT();
	void proc()override;
private:
	void save();
	void load();
	void update();
	void draw();
	SCENE_MANAGER* SceneManager = nullptr;
	SOFT_SHADOW* SoftShadowShader = nullptr;
	DRAWER::DRAWERS_SHADER EntityMarkDrawers;
	UI* UiRoot = nullptr;
	UI_MANAGER UiManager;
	UI_ANNOTATION_MANAGER UiAnnotationManager;
	LIGHT Light;
	CAMERA_DEBUG* Camera = nullptr;
	UI SaveButtonUi;
	UI LoadButtonUi;
	UI_SCROLL UiScrollAppearEntityButtonList;
	ENTITY_MANAGER EntityManager;
	ENTITY::ENTITY* SelectEntity = nullptr;
	std::array<DRAWER::IMAGE2D*, 512> EntityMarkDrawer = {};
	DRAWER::IMAGE2D* SelectEntityIcon = nullptr;
	ENTITY_TRANSFORMER EntityTransformer;
	ROUND_MISSION RoundMission;
};

