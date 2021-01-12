#include "../Library/STRING_TREE_SL.h"
#include "../Library/STRING_TREE.h"
#include "../Library/SHADER.h"
#include "LIGHT.h"
LIGHT::LIGHT() {
}

LIGHT::~LIGHT() {
}

void LIGHT::init(const STRING_TREE& dataTree){
	Pos = STRING_TREE_LOADER::vector3(dataTree.atw("pos"));
	Lookat = STRING_TREE_LOADER::vector3(dataTree.atw("lookat"));
	View.set(Pos,Lookat,VECTOR3(0, 1, 0));//ライトから見た頂点群に変換するマトリックス

	float s = dataTree.atw("orthoSize")->toFloat();
	float n = dataTree.atw("orthoNear")->toFloat();
	float f = dataTree.atw("orthoFar")->toFloat();

	Proj.setOrtho(s,s, n, f);//正投影（見たまんま＝遠いものを小さくしない）マトリックス
	Ambient = dataTree.atw("ambient")->toFloat();
	Diffuse = STRING_TREE_LOADER::color(dataTree.atw("diffuse"));
}

void LIGHT::shaderUpdate(SHADER* shader){
	shader->setLightPosition(Pos);
	shader->setLightAmbient(Ambient);
	shader->setDiffuse(Diffuse);
	shader->setLight_ProjView(Proj * View);
}
