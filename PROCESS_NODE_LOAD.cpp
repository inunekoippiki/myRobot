#include <filesystem>
#include <limits>
#include "../Library/common.h"
#include "../Library/STRING_TREE.h"
#include "../Library/STRING_TREE_SL.h"
#include "PROCESS_NODE_MANAGER.h"
#include "PROCESS_NODE_ASSIGNMENT.h"
#include "PROCESS_NODE_CALCULATION.h"
#include "PROCESS_NODE_FUNCTION.h"
#include "PROCESS_NODE_IF.h"
#include "PROCESS_NODE_INPUT.h"
#include "PROCESS_NODE_JUMP.h"
#include "PROCESS_NODE_JUMP_BACK.h"
#include "PROCESS_NODE_JUMP_POINT.h"
#include "PROCESS_NODE_OUTPUT.h"
#include "PROCESS_NODE_START.h"
#include "PROCESS_NODE_WAIT.h"
#include "PROCESS_NODE.h"
#include "PROCESS_NODE_TYPE.h"
#include "PROCESS_NODE_SAVE.h"
#include "PROCESS_NODE_LOAD.h"

void PROCESS_NODE_LOAD::load(const STRING_TREE& stringTree, CONTAINER* c, STATIC_FONT* font, PROCESS_NODE_MANAGER* processNodeManager, std::vector<PROCESS_NODE*>& addList) {	
	//入れ子データ構造を読み込む
	const STRING_TREE& tree = stringTree;
	int idx = tree.findData("root");
	if (idx != -1) {
		//各ノードの種類と入力されているそれぞれのデータを読み込む
		STRING_TREE* nodeTree = tree.childs()[idx]->atw("node");
		nodeLoad(nodeTree, c, font, processNodeManager, addList);
		//各ノードの繋がりを読み込む
		STRING_TREE* connectorTree = tree.childs()[idx]->atw("connector");
		lineLoad(connectorTree, addList, processNodeManager);
	}
}

void PROCESS_NODE_LOAD::load(const STRING_TREE& stringTree, CONTAINER* c, STATIC_FONT* font, PROCESS_NODE_MANAGER* processNodeManager){
	std::vector<PROCESS_NODE*> addList;
	load(stringTree, c, font, processNodeManager, addList);
}

void PROCESS_NODE_LOAD::nodeLoad(const STRING_TREE* nodeTree, CONTAINER* c, STATIC_FONT* font, PROCESS_NODE_MANAGER* processNodeManager, std::vector<PROCESS_NODE*>& addList) {
	addList.reserve(nodeTree->childs().size());
	//各ノードの種類と入力されているそれぞれのデータを読み込む
	for (auto& i : nodeTree->childs()) {
		PROCESS_NODE* p = instanceFromSaveString(*i, c, font, processNodeManager->processNodeLineDrawers(), processNodeManager->processNodeLiner(), processNodeManager);
		addList.push_back(p);
	}
}

void PROCESS_NODE_LOAD::nodeLoad(const STRING_TREE* nodeTree, CONTAINER* c, STATIC_FONT* font, PROCESS_NODE_MANAGER* processNodeManager){
	//各ノードの種類と入力されているそれぞれのデータを読み込む
	for (auto& i : nodeTree->childs()) {
		PROCESS_NODE* p = instanceFromSaveString(*i, c, font, processNodeManager->processNodeLineDrawers(), processNodeManager->processNodeLiner(), processNodeManager);
		processNodeManager->addProcessNode(p);
	}
}

void PROCESS_NODE_LOAD::lineLoad(STRING_TREE* connectorTree,const std::vector<PROCESS_NODE*>& addList, PROCESS_NODE_MANAGER* processNodeManager){
	//各ノードの繋がりを読み込む
	for (int i = 0;i < connectorTree->childs().size();i++) {
		STRING_TREE* outNodeListTree = connectorTree->childs()[i];
		int i2 = outNodeListTree->findData("outNode");
		if (i2 != -1) {
			STRING_TREE* outNodeTree = outNodeListTree->at(i2);
			for (int outConnectorIdx = 0;outConnectorIdx < outNodeTree->childs().size();outConnectorIdx++) {
				STRING_TREE* idxTree = outNodeTree->childs()[outConnectorIdx]->at("idx");
				int nodeIdx = idxTree->at("node")->toInt();
				if (nodeIdx != -1) {//-1でどれとも繋がっていない
					PROCESS_NODE_CONNECTOR_OUT* connectorOut = addList[i]->allNodeConnectorOut().first[outConnectorIdx];
					PROCESS_NODE_CONNECTOR_IN* connectorIn = addList[nodeIdx]->allNodeConnectorIn().first[idxTree->at("connector")->toInt()];
					connectorOut->setConnectorNext(connectorIn);
					connectorIn->setConnectorFront(connectorOut);
					//線の情報を読み込む
					STRING_TREE* lineTree = outNodeTree->childs()[outConnectorIdx]->at("line");
					int lineNum = lineTree->at("num")->toInt();
					std::array<VECTOR2, 6> linePoints;
					STRING_TREE* pointsTree = lineTree->at("points");
					for (int linePointIdx = 0;linePointIdx < lineNum;linePointIdx++) {
						//位置0,0スケール1,1基準に位置を変換
						VECTOR2 pointPos = loadSaveDataStringPos(*pointsTree->at(linePointIdx));
						linePoints[linePointIdx] = pointPos;
					}
					connectorOut->nodeLine()->pointsUpdate(lineNum,linePoints);
				}
			}
		}
	}
}

PROCESS_NODE* PROCESS_NODE_LOAD::instanceFromSaveString(
	const STRING_TREE& data,
	CONTAINER* c,
	STATIC_FONT* font,
	DRAWER::DRAWERS_SHADER* lineDrawers,
	PROCESS_NODE_LINER* processNodeLiner,
	PROCESS_NODE_MANAGER* processNodeManager) {
	std::string s = data.at("type")->data();
	PROCESS_NODE* processNode = nullptr;
	switch (PROCESS_NODE_SAVE::stringNameToType(s)) {
	case PROCESS_NODE_TYPE::START:
		processNode = new PROCESS_NODE_START(c, font, lineDrawers, processNodeLiner, processNodeManager);
		break;
	case PROCESS_NODE_TYPE::INPUT:
		processNode = new PROCESS_NODE_INPUT(c, font, lineDrawers, processNodeLiner, processNodeManager);
		break;
	case PROCESS_NODE_TYPE::OUTPUT:
		processNode = new PROCESS_NODE_OUTPUT(c, font, lineDrawers, processNodeLiner, processNodeManager);
		break;
	case PROCESS_NODE_TYPE::ASSIGNMENT:
		processNode = new PROCESS_NODE_ASSIGNMENT(c, font, lineDrawers, processNodeLiner, processNodeManager);
		break;
	case PROCESS_NODE_TYPE::CALCULATION:
		processNode = new PROCESS_NODE_CALCULATION(c, font, lineDrawers, processNodeLiner, processNodeManager);
		break;
	case PROCESS_NODE_TYPE::IF:
		processNode = new PROCESS_NODE_IF(c, font, lineDrawers, processNodeLiner, processNodeManager);
		break;
	case PROCESS_NODE_TYPE::WAIT:
		processNode = new PROCESS_NODE_WAIT(c, font, lineDrawers, processNodeLiner, processNodeManager);
		break;
	case PROCESS_NODE_TYPE::JUMP_POINT:
		processNode = new PROCESS_NODE_JUMP_POINT(c, font, lineDrawers, processNodeLiner, processNodeManager);
		break;
	case PROCESS_NODE_TYPE::JUMP:
		processNode = new PROCESS_NODE_JUMP(c, font, lineDrawers, processNodeLiner, processNodeManager);
		break;
	case PROCESS_NODE_TYPE::JUMP_BACK:
		processNode = new PROCESS_NODE_JUMP_BACK(c, font, lineDrawers, processNodeLiner, processNodeManager);
		break;
	case PROCESS_NODE_TYPE::FUNCTION:
		processNode = new PROCESS_NODE_FUNCTION(c, font, lineDrawers, processNodeLiner, processNodeManager);
		break;
	default:
		WARNING(true, "PROCESS_NODE::createFromSaveString", "enum classオーバーラン");
		break;
	}
	if (processNode != nullptr) {
		processNode->loadFromSaveString(data);
	}
	return processNode;
}

VECTOR2 PROCESS_NODE_LOAD::loadSaveDataStringPos(const STRING_TREE& data){
	int idx = data.findData("pos");
	VECTOR2 pos;
	if (idx != -1) {
		STRING_TREE* posData = data.childs()[idx];
		idx = posData->findData("x");
		if (idx != -1) {
			pos.x = posData->childs()[idx]->toFloat();
		}
		idx = posData->findData("y");
		if (idx != -1) {
			pos.y = posData->childs()[idx]->toFloat();
		}
	}
	return pos;
}
