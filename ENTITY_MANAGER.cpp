#include <fstream>
#include "../Library/STRING_TREE.h"
#include "../Library/GRAPHIC.h"
#include "ENTITY.h"
#include "ENTITY_FACTORY.h"
#include "TERRAIN_FLOOR.h"
#include "POSITION.h"
#include "../Library/DATA_BASE_OPERATOR.h"
#include "ENTITY_MANAGER.h"

ENTITY_MANAGER::ENTITY_MANAGER():
	EntityMediator(&EntityList) {
}

ENTITY_MANAGER::~ENTITY_MANAGER() {
	SAFE_DELETE(TerrainFloor);
	for (auto& i : EntityList) {
		SAFE_DELETE(i);
	}
	for (auto& i : AppearTempEntityList) {
		SAFE_DELETE(i);
	}
}

void ENTITY_MANAGER::create(
	CONTAINER* c,
	SOFT_SHADOW* softShadowShader,
	IMAGE_2D* image2dShader,
	ROUND_MISSION* roundMission) {

	Mt19937 = std::mt19937(std::random_device()());
	Drawers2d.setShader(image2dShader);
	Drawers3d.setShader(softShadowShader);
	EntityFactory.setAppearTempEntityList(&AppearTempEntityList);
	EntityFactory.setCollisionManager(&CollisionManager);
	EntityFactory.setContainer(c);
	EntityFactory.setDrawers2d(&Drawers2d);
	EntityFactory.setDrawers3d(&Drawers3d);
	EntityFactory.setEffekseerManager(&EffekseerManager);
	EntityFactory.setEntityManager(this);
	EntityFactory.setRoundMission(roundMission);
	//É}ÉbÉv
	TerrainFloor = new ENTITY::TERRAIN_FLOOR(c, &Drawers3d, CollisionManager.staticCollisions());
	TerrainFloor->setScale(VECTOR3(100.0f, 1.0f, 100.0f));

}

void ENTITY_MANAGER::update(){
	Timer++;
	deleteUpdate();
	apearTempEntityTransfer();
	for (auto& i : EntityList) {
		i->update();
	}
	effekseerUpdate();
}

void ENTITY_MANAGER::activeUpdate(){
	Timer++;
	deleteUpdate();
	apearTempEntityTransfer();
	for (auto& i : EntityList) {
		i->activeUpdate();
		i->update();
	}

	collisionUpdate();
	effekseerUpdate();
}

void ENTITY_MANAGER::deleteUpdate(){
	for (int i = 0;i < EntityList.size();) {
		if (EntityList[i]->isDelete()) {
			delete EntityList[i];
			EntityList[i] = EntityList.back();
			EntityList.pop_back();
			continue;
		}
		i++;
	}
}

void ENTITY_MANAGER::apearTempEntityTransfer(){
	EntityList.reserve(EntityList.size() + AppearTempEntityList.size());
	for (auto& i : AppearTempEntityList) {
		EntityList.push_back(i);
	}
	AppearTempEntityList.clear();
}

void ENTITY_MANAGER::collisionUpdate(){
	CollisionManager.exeCollisionExtrude();
	CollisionManager.exeCollision();
}

void ENTITY_MANAGER::effekseerUpdate(){
	EffekseerManager.update();
}

void ENTITY_MANAGER::updateProjView(const MATRIX& proj, const MATRIX& view) {
	EffekseerManager.updateProj(proj);
	EffekseerManager.updateView(view);
}

void ENTITY_MANAGER::draw3d(){
	Drawers3d.draw();
}
void ENTITY_MANAGER::drawEffect() {
	EffekseerManager.draw();
}

void ENTITY_MANAGER::draw2d(){
	Drawers2d.draw();
}

void ENTITY_MANAGER::allDeleteEntitys(){
	for_each(EntityList.begin(), EntityList.end(), [](ENTITY::ENTITY* entity) {entity->Delete();});
}

void ENTITY_MANAGER::loadEntitys(){
	loadEntitys("Assets/stageData/test");
}


void ENTITY_MANAGER::loadEntitys(STRING_TREE* stringTree) {
	for (auto& i : stringTree->childs()) {
		EntityFactory.instanceEntityFromStringTree(i);
	}
}

void ENTITY_MANAGER::loadEntitys(const std::string& fileName) {
	STRING_TREE tree(STRING_TREE::loadFile(fileName));
	STRING_TREE* rootTree = tree.atw("root");
	STRING_TREE* entitysTree = rootTree->atw("entitys");
	loadEntitys(entitysTree);
}

void ENTITY_MANAGER::saveEntitys(){
	saveEntitys("Assets/stageData/test");
}

void ENTITY_MANAGER::saveEntitys(const std::string& fileName) {
	std::string data;
	data += "root{";
	{
		data += "entitys[";
		for (auto& i : EntityList) {
			data += i->saveDataString();
		}
		data += "]";
	}data += "}";
	std::ofstream ofs(fileName);
	if (!ofs.is_open()) {
		WARNING(true,"ENTITY_MANAGER",( fileName + "Ç™ì«Ç›çûÇﬂÇ‹ÇπÇÒ").c_str());
	}
	ofs << data;
	ofs.close();
}

std::string ENTITY_MANAGER::saveEntitysString() {
	std::string data;
	data += "entitys[";
	for (auto& i : EntityList) {
		data += i->saveDataString();
	}
	data += "]";
	return data;
}
