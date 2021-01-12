#include<filesystem>
#include "../Library/MB_LIB.h"
#include "../Library/INDEV.h"
#include "../Library/CONTAINER.h"
#include "../Library/STRING_TREE.h"
#include "../Library/GRAPHIC.h"
#include "UI_KEYBOARD.h"
#include "UI_SCROLL.h"
#include "UI.h"
#include "UI_FACTORY.h"
#include "UI_FUNC_ATTACHER.h"
#include "DRAWER_EMPTY.h"
#include "DRAWER_IMAGE2D_TILING.h"
#include "PROCESS_NODE.h"
#include "PROCESS_NODE_CONNECTOR.h"
#include "NODE_LINE.h"
#include "INPUT_COMMON.h"
#include "PROCESS_NODE_SAVE.h"
#include "UI_ANNOTATION.h"
#include "SOUND_MANAGER.h"
#include "PROCESS_NODE_MANAGER.h"
PROCESS_NODE_MANAGER::PROCESS_NODE_MANAGER(
	CONTAINER* c, 
	STATIC_FONT* font,
	IMAGE_2D* image2dShader):
	Container(c),
	Font(font),
	Image2dShader(image2dShader),
	ProcessNodeLineDrawers(image2dShader),
	ProcessNodeSelectField(image2dShader),
	ProcessNodeSelectRangeField(image2dShader),
	ProcessNodeSelectLineField(image2dShader),
	SaveDataLoadScroll(c,font,this){
	ProcessNodeSelector = new PROCESS_NODE_SELECTOR(c, Font, &ProcessNodeLineDrawers, &ProcessNodeSelectRangeField, this, &ProcessNodeWindow);

	GRAPHIC* g = GRAPHIC::instance();
	//データコンテナ
	STRING_TREE stringTree(STRING_TREE::loadFile("Assets/processNodeManagerData.txt"));
	STRING_TREE* rootST = stringTree.atw("root");

	//RootUIの生成
	RootUi = new UI;
	RootUi->create(new DRAWER::EMPTY());
	//キーボードーや選択スクロール表示用のレイヤ
	PopupUi = UI_FACTORY::instance(new DRAWER::EMPTY);
	//キーボードの生成/////////////////////////////////////////////////////////////////
	{
		UiKeyboard = new UI_KEYBOARD(c, font);
		UiKeyboard->rootUi()->setIsUnconditionalCollisionHit(true);
		UiKeyboard->rootUi()->setIsDisable(true);
		UiKeyboard->setEnterFunc([this]() {
			if (SendStringFunc != nullptr) {
				this->SendStringFunc(this->UiKeyboard->inputString());
			};}
		);
		UiKeyboard->setCancelFunc([this]() {UiKeyboard->rootUi()->setIsDisable(true);});
		PopupUi->addChilds(UiKeyboard->rootUi());
	}
	//入力モジュールリストの生成/////////////////////////////////////////////////////////////////
	{
		createUiScroll(&InputModuleScroll, Container, Font, std::move(std::vector<UI*>()));
		PopupUi->addChilds(InputModuleScroll.rootUi());
	}
	//出力モジュールリストの生成/////////////////////////////////////////////////////////////////
	{
		createUiScroll(&OutputModuleScroll, Container, Font, std::move(std::vector<UI*>()));
		PopupUi->addChilds(OutputModuleScroll.rootUi());
	}
	//変数リストの生成/////////////////////////////////////////////////////////////////
	{
		createUiScroll(&VariableScroll, c, font, std::move(std::vector<UI*>()));
		PopupUi->addChilds(VariableScroll.rootUi());
	}
	//ジャンプポイントリスト
	{
		createUiScroll(&JumpPointScroll, c, font, std::move(std::vector<UI*>()));
		PopupUi->addChilds(JumpPointScroll.rootUi());
	}
	//代入演算子リストの生成/////////////////////////////////////////////////////////////////
	{
		createUiScroll(&AssignmentOperatorScroll, rootST, "assignmentOperatorScroll");
		PopupUi->addChilds(AssignmentOperatorScroll.rootUi());
	}
	//演算子リストの生成/////////////////////////////////////////////////////////////////
	{
		createUiScroll(&OperatorScroll, rootST, "operatorScroll");
		PopupUi->addChilds(OperatorScroll.rootUi());
	}
	//比較演算子リストの生成/////////////////////////////////////////////////////////////////
	{
		createUiScroll(&ComparisonOperatorScroll, rootST, "comparisonOperatorScroll");
		PopupUi->addChilds(ComparisonOperatorScroll.rootUi());
	}
	//関数リストの生成/////////////////////////////////////////////////////////////////
	{
		createUiScroll(&FunctionScroll, rootST, "functionScroll");
		PopupUi->addChilds(FunctionScroll.rootUi());
	}
	//loadスクロールの生成
	{
		SaveDataLoadScroll.create(this);
		PopupUi->addChilds(SaveDataLoadScroll.uiScroll()->rootUi());
		SaveDataLoadScroll.uiScroll()->rootUi()->setIsDisable(true);
	}
	//プロセスノードのウインドウ////////////////////////////////////////////////////////////
	{
		ProcessNodeWindow.create(c, rootST, ProcessNodeSelector, this);
	}
	//プロセスノード生成ボタン////////////////////////////////////////////////////////////
	{
		ProcessNodeAdd.create(c, Font, rootST, this, &ProcessNodeLineDrawers, &ProcessNodeLiner);
	}
	//操作バー
	{
		ProcessNodeOperator.create(c, this, ProcessNodeSelector);
	}

	RootUi->addChilds(ProcessNodeWindow.processNodeListUi());
	RootUi->addChilds(ProcessNodeWindow.processNodeLinePointListUi());
	RootUi->addChilds(ProcessNodeOperator.rootUi());
	RootUi->addChilds(ProcessNodeWindow.cameraOperationUi());
	RootUi->addChilds(ProcessNodeAdd.rootUi());
	RootUi->addChilds(PopupUi);

	ProcessNodeLiner.create(this, c, &ProcessNodeLineDrawers);
	//音
	SoundProcessNodeAdd = c->sound("nodeAdd");
	SoundButton = c->sound("button");
	SoundProcessSave = c->sound("save");
}

PROCESS_NODE_MANAGER::~PROCESS_NODE_MANAGER() {
	SAFE_DELETE(RootUi);
	SAFE_DELETE(UiKeyboard);
	for (auto& i : ProcessNodeList) {
		SAFE_DELETE(i);
	}
	SAFE_DELETE(ProcessNodeSelector);
}

void PROCESS_NODE_MANAGER::draw(){
	SHADER* shader = Image2dShader;
	BEGIN_PATH_
	processNodeListUi()->draw(shader);
	ProcessNodeLineDrawers.draw(shader);
	ProcessNodeSelectField.draw(shader);
	ProcessNodeSelectRangeField.draw(shader);
	ProcessNodeSelectLineField.draw(shader);
	ProcessNodeWindow.processNodeLinePointListUi()->draw(shader);
	ProcessNodeOperator.rootUi()->draw(shader);
	ProcessNodeWindow.cameraOperationUi()->draw(shader);
	ProcessNodeAdd.draw(shader);
	PopupUi->draw(shader);
	END_PATH_

}

void PROCESS_NODE_MANAGER::startKeyboardInput(const std::function<void(const std::string&)>& callback){
	UiKeyboard->rootUi()->setIsDisable(false);
	UiKeyboard->resetInputString();
	SendStringFunc = [this, callback](const std::string& s) {
		callback(s);
		UiKeyboard->rootUi()->setIsDisable(true);
	};
}

void PROCESS_NODE_MANAGER::startScrollInput(UI_SCROLL* uiScroll, const VECTOR2& pos, const std::function<void(const std::string&)>& callback){
	uiScroll->rootUi()->setIsDisable(false);
	SendStringFunc = [this, uiScroll, callback](const std::string& s) {
		callback(s);
		uiScroll->rootUi()->setIsDisable(true);
	};
	uiScroll->rootUi()->setPos(pos);
	uiScroll->scrollUpdate(0);
}



void PROCESS_NODE_MANAGER::startSaveDataLoadScroll(){
	SaveDataLoadScroll.uiScroll()->rootUi()->setIsDisable(false);
	SaveDataLoadScroll.SaveDataListScrollUpdate();
	SOUND_MANAGER::instance()->playSound(SoundButton);
}

void PROCESS_NODE_MANAGER::startSaveDataSaveKeyBoard(){
	startKeyboardInput([this](const std::string& s) {
		PROCESS_NODE_SAVE::saveDesignData(s,PROCESS_NODE_SAVE::ProcessNodeToSaveDataString(this->ProcessNodeList));
		SOUND_MANAGER::instance()->playSound(SoundProcessSave);}
	);
	SOUND_MANAGER::instance()->playSound(SoundButton);
}

void PROCESS_NODE_MANAGER::addProcessNode(PROCESS_NODE* processNode){
	ProcessNodeList.push_back(processNode);
	processNode->setEnable();
	processNodeListUi()->addChilds(processNode->rootUi());
	PROCESS_NODE::addLinePointUiToRootUi(processNode,ProcessNodeWindow.processNodeLinePointListUi());
}

void PROCESS_NODE_MANAGER::removeProcessNode(PROCESS_NODE* processNode){
	for (int i = 0;i < ProcessNodeList.size();i++) {
		if (ProcessNodeList[i] == processNode) {
			processNodeListUi()->removeChilds(processNode->rootUi());
			PROCESS_NODE::removeLinePointUiToRootUi(processNode);
			processNode->setDisable();
			ProcessNodeLiner.disconnect(processNode);
			ProcessNodeList[i] = ProcessNodeList.back();
			ProcessNodeList.pop_back();
		}
	}
}

void PROCESS_NODE_MANAGER::processNodeSelectorUpdate(){
	ProcessNodeSelector->drawerUpdate();
}

void PROCESS_NODE_MANAGER::addVariable(const std::string& s) {
	VariableScroll.add(s, this);
}

void PROCESS_NODE_MANAGER::removeVeriable(const std::string& s) {
	VariableScroll.remove(s);
}

void PROCESS_NODE_MANAGER::addJumpPoint(const std::string& s){
	JumpPointScroll.add(s, this);
}

void PROCESS_NODE_MANAGER::removeJumpPoint(const std::string& s){
	JumpPointScroll.remove(s);
}

void PROCESS_NODE_MANAGER::setModuleScroll(ROBOT_PROCESSOR* robotProcessor){
	{
		std::vector<UI*>* listUi = InputModuleScroll.listUi();
		listUi->reserve(robotProcessor->inputModuleList().list()->size());
		for (auto& i : *robotProcessor->inputModuleList().list()) {
			listUi->push_back(instanceUiScrollListNode(this, Container, Font, i.first.c_str(),i.second.Annotation));
		}
		InputModuleScroll.scrollUpdate(0);
	}
	{
		std::vector<UI*>* listUi = OutputModuleScroll.listUi();
		listUi->reserve(robotProcessor->outputModuleList().list()->size());
		for (auto& i : *robotProcessor->outputModuleList().list()) {
			listUi->push_back(instanceUiScrollListNode(this, Container, Font, i.first.c_str(), i.second.Annotation));
		}
		OutputModuleScroll.scrollUpdate(0);
	}
}

void PROCESS_NODE_MANAGER::sendStringFunc(const std::string& str) { 
	if (SendStringFunc != nullptr) { 
		SendStringFunc(str); 
	} 
}

void PROCESS_NODE_MANAGER::createUiScroll(UI_SCROLL* uiScroll, STRING_TREE* data, const std::string& scrollName){
	STRING_TREE* ScrollST = data->atw(scrollName);
	std::vector<UI*> listUi;
	STRING_TREE* listST = ScrollST->atw("list");
	listUi.reserve(listST->childs().size());
	for (auto& i : listST->childs()) {
		STRING_TREE* annotationST = i->at("annotation");
		if (annotationST != nullptr) {
			UI_ANNOTATION annotation;
			annotation.setAnnotationString(MB_LIB::replaceText(annotationST->data(), "\\n", "\n"));
			listUi.push_back(instanceUiScrollListNode(this, Container, Font, i->atw("s")->data().c_str(), annotation));
		}
		else {
			listUi.push_back(instanceUiScrollListNode(this, Container, Font, i->atw("s")->data().c_str()));
		}
	}
	createUiScroll(uiScroll, Container, Font, std::move(listUi));
}

UI* PROCESS_NODE_MANAGER::instanceUiScrollListNode(const char* s){
	UI* ui = UI_FACTORY::instance(Container->texture("UiScrollNode"), VECTOR2(0.0f, 0.0f), VECTOR2(1.0f, 1.0f));
	DRAWER::STATIC_FONT* drawer = DRAWER::STATIC_FONT::instance(s, Font, VECTOR2(), VECTOR2(32.0f, 32.0f), DRAWER::STATIC_FONT::drawMethodAdjustDraw_Over());
	drawer->setMaxWidth(7);
	UI* stringUi = UI_FACTORY::instance(drawer);
	stringUi->setIsCollisionDisable(true);
	ui->addChilds(stringUi);
	ui->setPushFunc([this, drawer]() {
		this->sendStringFunc(drawer->string());}
	);
	return ui;
}

void PROCESS_NODE_MANAGER::createUiScroll(UI_SCROLL* uiScroll, CONTAINER* c, STATIC_FONT* font, std::vector<UI*>&& listUi){
	uiScroll->create(
		UI_FACTORY::instance(c->texture("UiScrollBack"), VECTOR2(0.0f, 0.0f), VECTOR2(2.0f, 1.5f)),
		UI_FACTORY::instance(c->texture("UiScrollBarBack"), VECTOR2(112.0f, 40.0f), VECTOR2::one()),
		UI_FACTORY::instance(c->texture("UiScrollBar"), VECTOR2(0.0f, 0.0f), VECTOR2::one()),
		UI_FACTORY::instance(c->texture("UiScrollNodeBack"), VECTOR2(0.0f, 32.0f), VECTOR2::one()),
		UI_FACTORY::instance(c->texture("UiScrollUp"), VECTOR2(112.0f, 32.0f), VECTOR2::one()),
		UI_FACTORY::instance(c->texture("UiScrollDown"), VECTOR2(112.0f, 280.0f), VECTOR2::one()),
		std::move(listUi),
		8
	);
	uiScroll->rootUi()->setPushFunc([uiScroll]() {uiScroll->rootUi()->setIsDisable(true);});
	uiScroll->rootUi()->setIsReleaseDisable(true);
	uiScroll->rootUi()->setIsDisable(true);
	uiScroll->rootUi()->setIsUnconditionalCollisionHit(true);
}

void PROCESS_NODE_MANAGER::createUiScroll(UI_SCROLL_ADD_COUNT* uiScrollAddCount, CONTAINER* c, STATIC_FONT* font, std::vector<UI*>&& listUi){
	uiScrollAddCount->create(
		UI_FACTORY::instance(c->texture("UiScrollBack"), VECTOR2(0.0f, 0.0f), VECTOR2(2.0f, 1.5f)),
		UI_FACTORY::instance(c->texture("UiScrollBarBack"), VECTOR2(112.0f, 40.0f), VECTOR2::one()),
		UI_FACTORY::instance(c->texture("UiScrollBar"), VECTOR2(0.0f, 0.0f), VECTOR2::one()),
		UI_FACTORY::instance(c->texture("UiScrollNodeBack"), VECTOR2(0.0f, 32.0f), VECTOR2::one()),
		UI_FACTORY::instance(c->texture("UiScrollUp"), VECTOR2(112.0f, 32.0f), VECTOR2::one()),
		UI_FACTORY::instance(c->texture("UiScrollDown"), VECTOR2(112.0f, 280.0f), VECTOR2::one()),
		std::move(listUi),
		8
	);
	uiScrollAddCount->rootUi()->setPushFunc([uiScrollAddCount]() {uiScrollAddCount->rootUi()->setIsDisable(true);});
	uiScrollAddCount->rootUi()->setIsReleaseDisable(true);
	uiScrollAddCount->rootUi()->setIsDisable(true);
	uiScrollAddCount->rootUi()->setIsUnconditionalCollisionHit(true);
}

UI* PROCESS_NODE_MANAGER::instanceUiScrollListNode(PROCESS_NODE_MANAGER* processNodeManager, CONTAINER* c, STATIC_FONT* font, const char* s){
	return instanceUiScrollListNode(processNodeManager,c,font,s,UI_ANNOTATION());
}

UI* PROCESS_NODE_MANAGER::instanceUiScrollListNode(PROCESS_NODE_MANAGER* processNodeManager, CONTAINER* c, STATIC_FONT* font, const char* s,const UI_ANNOTATION& annotation){
	UI* ui = UI_FACTORY::instance(c->texture("UiScrollNode"), VECTOR2(0.0f, 0.0f), VECTOR2(1.0f, 1.0f));
	*ui->annotation() = annotation;
	DRAWER::STATIC_FONT* drawer = DRAWER::STATIC_FONT::instance(s, font, VECTOR2(), VECTOR2(32.0f, 32.0f), DRAWER::STATIC_FONT::drawMethodAdjustDraw_Over());
	drawer->setMaxWidth(7);
	UI* stringUi = UI_FACTORY::instance(drawer);
	stringUi->setIsCollisionDisable(true);
	ui->addChilds(stringUi);
	ui->setPushFunc([processNodeManager, drawer]() {
		processNodeManager->sendStringFunc(drawer->string());}
	);
	return ui;
}
