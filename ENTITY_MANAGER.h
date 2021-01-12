#pragma once
#include <random>
#include <vector>
#include "../Library/IMAGE_2D.h"
#include "../Library/SOFT_SHADOW.h"
#include "DRAWERS_SHADER.h"
#include "COLLISION_MANAGER.h"
#include "EFFEKSEER.h"
#include "ENTITY_FACTORY.h"
#include "ENTITY_MEDIATOR.h"
#include "ENTITY.h"
class CONTAINER;
namespace ENTITY {
	class TERRAIN_FLOOR;
	class ROBOT;
}
class ENTITY_FACTORY;
class ROUND_MISSION;
class ENTITY_MANAGER{
public:
	ENTITY_MANAGER();
	~ENTITY_MANAGER();
	void create(
		CONTAINER* c,
		SOFT_SHADOW* softShadowShader,
		IMAGE_2D* image2dShader, 
		ROUND_MISSION* roundMission);
	void update();
	//deleteÉtÉâÉOÇ™ì¸Ç¡ÇƒÇ¢ÇÈENTITYÇè¡Ç∑
	void deleteUpdate();
	void apearTempEntityTransfer();
	void activeUpdate();
	void collisionUpdate();
	void effekseerUpdate();
	void updateProjView(const MATRIX& proj, const MATRIX& view);
	void draw3d();
	void drawEffect();
	void draw2d();
	void allDeleteEntitys();
	ENTITY_FACTORY* entityFactory() { return &EntityFactory; }
	DRAWER::DRAWERS_SHADER* drawers2d() { return &Drawers2d; }
	DRAWER::DRAWERS_SHADER* drawers3d() { return &Drawers3d; }
	void loadEntitys();
	void loadEntitys(STRING_TREE* dataTree);
	void loadEntitys(const std::string& fileName);
	void saveEntitys();
	void saveEntitys(const std::string& fileName);
	std::string saveEntitysString();
	ENTITY_MEDIATOR* entityMediator() { return &EntityMediator; }
	const std::vector< ENTITY::ENTITY*>* entityList() const{ return &EntityList; }
private:
	int Timer = 0;
	std::mt19937 Mt19937;
	ENTITY_FACTORY EntityFactory;
	ENTITY_MEDIATOR EntityMediator;
	COMPONENT::COLLISION_MANAGER CollisionManager;
	DRAWER::DRAWERS_SHADER Drawers3d;
	DRAWER::DRAWERS_SHADER Drawers2d;
	EFFEKSEER::MANAGER EffekseerManager;
	ENTITY::TERRAIN_FLOOR* TerrainFloor = nullptr;
	ENTITY::ROBOT* Robot = nullptr;
	std::vector< ENTITY::ENTITY*> AppearTempEntityList;
	std::vector< ENTITY::ENTITY*> EntityList;
};

