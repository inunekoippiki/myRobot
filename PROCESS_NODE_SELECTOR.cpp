#include <windows.h>
#include "../Library/GRAPHIC.h"
#include "../Library/MB_LIB.h"
#include "../Library/STRING_TREE.h"
#include "../Library/CONTAINER.h"
#include "DRAWERS_SHADER.h"
#include "COLLISION2D_RECT.h"
#include "PROCESS_NODE.h"
#include "NODE_LINE.h"
#include "UI.h"
#include "PROCESS_NODE_CONNECTOR.h"
#include "PROCESS_NODE_MANAGER.h"
#include "PROCESS_NODE_SAVE.h"
#include "PROCESS_NODE_LOAD.h"
#include "PROCESS_NODE_COMMAND/FACTORY.h"
#include "PROCESS_NODE_SELECTOR.h"
PROCESS_NODE_SELECTOR::PROCESS_NODE_SELECTOR(
	CONTAINER* c,
	STATIC_FONT* font,
	DRAWER::DRAWERS_SHADER* processNodeSelectField,
	DRAWER::DRAWERS_SHADER* processNodeSelectRangeField,
	PROCESS_NODE_MANAGER* processNodeManager,
	PROCESS_NODE_WINDOW* processNodeWindow) :
	Container(c),
	Font(font),
	ProcessNodeSelectField(processNodeSelectField),
	ProcessNodeSelectRangeField(processNodeSelectRangeField),
	ProcessNodeManager(processNodeManager),
	ProcessNodeWindow(processNodeWindow)
	{

	DRAWER::IMAGE2D * drawer = new DRAWER::IMAGE2D;
	drawer->setTexture(Container->texture("oneDot"));
	drawer->setColor(COLOR(0.0f, 0.0f, 1.0f, 0.5f));
	drawer->setPivot(DRAWER::IMAGE2D::drawMethodInvisible());
	SelectRangeDrawer = drawer;
	processNodeSelectRangeField->add(drawer);
}

PROCESS_NODE_SELECTOR::~PROCESS_NODE_SELECTOR() {
	for (auto& i : SelectProcessNodeOverlay) {
		i->Delete();
	}
	SelectRangeDrawer->Delete();
}

void PROCESS_NODE_SELECTOR::mouseDown(const VECTOR2& localPos){
	VECTOR2 worldPos = ProcessNodeWindow->processNodeListUi()->localPosToWorldPos(localPos);
	SelectRangeDrawer->setPivot(DRAWER::IMAGE2D::drawMethodLeft());
	SelectRangeDrawer->setPos(worldPos);
	SelectRangeDrawer->setScale(VECTOR2(0.0f, 0.0f));
	MouseDownWindowLocalPos = localPos;
	MouseWindowLocalPos = localPos;
}

void PROCESS_NODE_SELECTOR::mouseDragUpdate(const VECTOR2& localPos){
	GRAPHIC* g = GRAPHIC::instance();
	MouseWindowLocalPos = localPos;
	UI* windowUi = ProcessNodeWindow->processNodeListUi();
	SelectRangeDrawer->minusWhFix(windowUi->localPosToWorldPos(MouseWindowLocalPos), windowUi->localPosToWorldPos(MouseDownWindowLocalPos));
}

void PROCESS_NODE_SELECTOR::mouseUp(){
	SelectRangeDrawer->setPivot(DRAWER::IMAGE2D::drawMethodInvisible());
	std::vector<PROCESS_NODE*> oldSelectList;
	swap(SelectList, oldSelectList);
	select(MouseDownWindowLocalPos, MouseWindowLocalPos);
	auto command = PROCESS_NODE_COMMAND::instanceSelect(SelectList, oldSelectList, this);
	ProcessNodeManager->commandStream()->push(command);

}

void PROCESS_NODE_SELECTOR::select(COLLISION2D* collision){
	SelectList.clear();
	auto& processNodeList = ProcessNodeManager->processNodeList();
	for (auto& i : processNodeList) {
		if (i->rootUi()->collision()->dispatch(collision)) {
			SelectList.push_back(i);
		}
	}
	selectUpdate();
}

void PROCESS_NODE_SELECTOR::select(const VECTOR2& localSt, const VECTOR2& localEd) {
	UI* windowUi = ProcessNodeWindow->processNodeListUi();
	VECTOR2 st = windowUi->localPosToWorldPos(localSt);
	VECTOR2 ed = windowUi->localPosToWorldPos(localEd);
	COLLISION2D_RECT rect;
	rect.minusWhFix(st, ed);
	select(&rect);
}

void PROCESS_NODE_SELECTOR::select(const std::vector<PROCESS_NODE*>& selectList, std::vector<PROCESS_NODE*>& oldSelectList) {
	swap(oldSelectList, SelectList);
	SelectList = selectList;
	selectUpdate();
}

void PROCESS_NODE_SELECTOR::select(const std::vector<PROCESS_NODE*>& selectList){
	SelectList = selectList;
	selectUpdate();
}


void PROCESS_NODE_SELECTOR::selectUpdate(){
	SelectProcessNodeOverlay.reserve(SelectList.size());
	if (SelectList.size() > SelectProcessNodeOverlay.size()) {
		for (auto& i : SelectProcessNodeOverlay) {
			i->setPivot(i->drawMethodLeft());
		}
	}
	else {
		for (size_t i = 0;i < SelectList.size();i++) {
			SelectProcessNodeOverlay[i]->setPivot(DRAWER::IMAGE2D::drawMethodLeft());
		}
		for (size_t i = SelectList.size();i < SelectProcessNodeOverlay.size();i++) {
			SelectProcessNodeOverlay[i]->setPivot(DRAWER::IMAGE2D::drawMethodInvisible());
		}
	}
	for (size_t i = 0;i < SelectList.size();i++) {
		if (SelectProcessNodeOverlay.size() <= i) {
			DRAWER::IMAGE2D* drawer = new DRAWER::IMAGE2D;
			drawer->setTexture(Container->texture("oneDot"));
			drawer->setPos(SelectList[i]->rootUi()->collision()->pos());
			drawer->setScale(SelectList[i]->rootUi()->collision()->wh());
			drawer->setColor(COLOR(0.0f, 0.0f, 1.0f, 0.5f));
			SelectProcessNodeOverlay.push_back(drawer);
			ProcessNodeSelectField->add(drawer);
		}
		else {
			DRAWER::IMAGE2D* drawer = SelectProcessNodeOverlay[i];
			drawer->setTexture(Container->texture("oneDot"));
			drawer->setPos(SelectList[i]->rootUi()->collision()->pos());
			drawer->setScale(SelectList[i]->rootUi()->collision()->wh());
		}
	}
}

void PROCESS_NODE_SELECTOR::drawerUpdate(){
	for (size_t i = 0;i < SelectList.size();i++) {
		DRAWER::IMAGE2D* drawer = SelectProcessNodeOverlay[i];
		drawer->setPos(SelectList[i]->rootUi()->collision()->pos());
		drawer->setScale(SelectList[i]->rootUi()->collision()->wh());
	}
}

void PROCESS_NODE_SELECTOR::updateLine(){
	for (auto& i : SelectList) {
		auto allNodeConnectorOut = i->allNodeConnectorOut();
		for (int i2 = 0;i2 < allNodeConnectorOut.second;i2++) {
			allNodeConnectorOut.first[i2]->updateLine();
		}
		auto allNodeConnectorIn = i->allNodeConnectorIn();
		for (int i2 = 0;i2 < allNodeConnectorIn.second;i2++) {
			selectProcessNodeFrontLineUpdate(allNodeConnectorIn.first[i2]);
		}
	}
}

bool PROCESS_NODE_SELECTOR::removeSelectProcessNode(){
	if (SelectList.empty()) return true;
	for (auto& i : SelectList) {
		ProcessNodeManager->removeProcessNode(i);//選択中のノードを消す
	}
	for (int i = 0;i < SelectList.size();i++) {
		SelectProcessNodeOverlay[i]->setPivot(DRAWER::IMAGE2D::drawMethodInvisible());//選択状態のオーバーレイ画像を消す
	}
	SelectList.clear();
	return false;
}

void PROCESS_NODE_SELECTOR::AlignPosXSelectProcessNode(){
	float sum = 0;
	for (auto& i : SelectList) {
		sum += i->rootUi()->pos().x;
	}
	sum /= SelectList.size();//座標の平均を求める
	for (auto& i : SelectList) {
		i->rootUi()->setPos(VECTOR2(sum, i->rootUi()->pos().y));//各ノードの位置を設定
	}
	updateLine();
	drawerUpdate();
}

void PROCESS_NODE_SELECTOR::AlignPosYSelectProcessNode(){
	float sum = 0;
	for (auto& i : SelectList) {
		sum += i->rootUi()->pos().y;
	}
	sum /= SelectList.size();
	for (auto& i : SelectList) {
		i->rootUi()->setPos(VECTOR2(i->rootUi()->pos().x, sum));
	}
	updateLine();
	drawerUpdate();
}

void PROCESS_NODE_SELECTOR::CopySelectProcessNode() {
	CopyDataString = PROCESS_NODE_SAVE::ProcessNodeToSaveDataString(SelectList);
}

void PROCESS_NODE_SELECTOR::processNodePaste(){
	processNodePaste(CopyDataString);
}

void PROCESS_NODE_SELECTOR::processNodePaste(const std::string& Data){
	if (Data.empty())return;
	STRING_TREE tree(Data);
	std::vector<PROCESS_NODE*> addList;
	PROCESS_NODE_LOAD::load(tree, Container, Font, ProcessNodeManager, addList);
	auto command = PROCESS_NODE_COMMAND::instanceOperatorPaste(tree.atw("root")->atw("connector")->data(), addList, this, ProcessNodeManager);
	ProcessNodeManager->commandStream()->push(command);
	command->execute();
}

void PROCESS_NODE_SELECTOR::moveSelectProcessNode(const VECTOR2& v){
	for (auto& i : SelectList) {
		i->rootUi()->setPos(i->rootUi()->pos() + v);
	}
	for (auto& i : SelectList) {
		auto allNodeConnectorOut = i->allNodeConnectorOut();
		for (int i2 = 0;i2 < allNodeConnectorOut.second;i2++) {
			bool isMatch = false;
			for (auto& i3 : SelectList) {
				auto allNodeConnectorIn = i3->allNodeConnectorIn();
				for (int i4 = 0;i4 < allNodeConnectorIn.second;i4++) {
					if (allNodeConnectorOut.first[i2]->cnnectorNext() == allNodeConnectorIn.first[i4]) {
						isMatch = true;
						goto searchEnd;
					}
				}
			}searchEnd://多重ループbreakのため(このブロック内以外で使うな)
			if (isMatch) {
				allNodeConnectorOut.first[i2]->moveLine();
			}
			else {
				allNodeConnectorOut.first[i2]->updateLine();
			}
		}
		auto allNodeConnectorIn = i->allNodeConnectorIn();
		for (int i2 = 0;i2 < allNodeConnectorIn.second;i2++) {
			selectProcessNodeFrontLineUpdate(allNodeConnectorIn.first[i2]);
		}
	}
	drawerUpdate();
}

void PROCESS_NODE_SELECTOR::selectProcessNodeFrontLineUpdate(PROCESS_NODE_CONNECTOR_IN* nodeConnectorIn) {
	if (nodeConnectorIn->connectorFront() == nullptr) return;
	for (auto& i : SelectList) {//全ての選択されたノードが持ってるConnectorOutと比較
		auto allNodeConnectorOut = i->allNodeConnectorOut();
		for (int i2 = 0;i2 < allNodeConnectorOut.second;i2++) {
			if (nodeConnectorIn->connectorFront() == allNodeConnectorOut.first[i2]) {
				//登録済みならそっちから更新されるので終了
				return;
			}
		}
	}
	//どれにも登録されていなかったら個別に更新
	nodeConnectorIn->connectorFront()->updateLine();
}
