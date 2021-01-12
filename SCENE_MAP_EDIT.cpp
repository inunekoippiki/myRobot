#include "../Library/common.h"
#include "../Library/WINDOW.h"
#include "../Library/GRAPHIC.h"
#include "../Library/DEBUG_STR.h"
#include "../Library/CONTAINER.h"
#include "../Library/STRING_TREE.h"
#include "../Library/collisionUtil.h"
#include "../Library/INDEV.h"
#include "INPUT_COMMON.h"
#include "DRAWER_STATIC_FONT.h"
#include "DRAWER_EMPTY.h"
#include "UI_FUNC_ATTACHER.h"
#include "UI_FACTORY.h"
#include "SCENE_MANAGER.h"
#include "DRAWER_IMAGE3D.h"
#include "CAMERA_DEBUG.h"
#include "SCENE_MANAGER.h"
#include "POSITION.h"
#include "ENTITY_FACTORY.h"
#include "FADE.h"
#include "LOAD_DISP.h"
#include "SCENE_MAP_EDIT.h"


SCENE_MAP_EDIT::SCENE_MAP_EDIT(SCENE_MANAGER* sceneManager):
SceneManager(sceneManager){
	const auto Font = font();
	SoftShadowShader = new SOFT_SHADOW(2048, 2048);
	DEBUG_STR* ds = DEBUG_STR::instance();
	GRAPHIC* g = GRAPHIC::instance();

	EntityMarkDrawers.setShader(image2d());
	EntityManager.create(c(), SoftShadowShader, image2d(),&RoundMission);
	Camera = new CAMERA_DEBUG(STRING_TREE(STRING_TREE::loadFile("Assets/ROUND/cameraData.txt")));
	UiRoot = UI_FACTORY::instance(new DRAWER::EMPTY);
	UiRoot->setIsUnconditionalCollisionHit(true);
	{
		DRAWER::STATIC_FONT* drawer = DRAWER::STATIC_FONT::instance("save", Font, VECTOR2(300, 300), VECTOR2(64.0f, 64.0f), DRAWER::STATIC_FONT::drawMethodDefault());
		SaveButtonUi.create(drawer);
		SaveButtonUi.setPushFunc([this]() {this->save();});
		UI_FUNC_ATTACHER::OverlapColorChange(&SaveButtonUi, drawer);
		SaveButtonUi.setIsReleaseDisable(true);
		SaveButtonUi.setIsDisable(false);
		UiRoot->addChilds(&SaveButtonUi);
	}
	{
		DRAWER::STATIC_FONT* drawer = DRAWER::STATIC_FONT::instance("load", Font, VECTOR2(300, 364), VECTOR2(64.0f, 64.0f), DRAWER::STATIC_FONT::drawMethodDefault());
		LoadButtonUi.create(drawer);
		LoadButtonUi.setPushFunc([this]() {this->load();});
		UI_FUNC_ATTACHER::OverlapColorChange(&LoadButtonUi, drawer);
		LoadButtonUi.setIsReleaseDisable(true);
		LoadButtonUi.setIsDisable(false);
		UiRoot->addChilds(&LoadButtonUi);
	}
	{
		std::vector<UI*>listUi;
		const char* s[] = {
			"ボックス",
			"円柱",
			"ゴール",
			"アイテム",
			"ターゲット",
			"自爆エネミー",
			"射撃エネミー",
			""
		};

		for (int i = 0;i < 8;i++) {
			UI* ui = UI_FACTORY::instance(c()->texture("UiScrollNode"), VECTOR2(0.0f, 0.0f), VECTOR2(1.0f, 1.0f));
			DRAWER::STATIC_FONT* drawer = DRAWER::STATIC_FONT::instance(s[i], font(), VECTOR2(), VECTOR2(32.0f, 32.0f), DRAWER::STATIC_FONT::drawMethodAdjustDraw_Over());
			drawer->setMaxWidth(7);
			UI* stringUi = UI_FACTORY::instance(drawer);
			stringUi->setIsCollisionDisable(true);
			UI_FUNC_ATTACHER::OverlapColorChange(ui, drawer);
			ui->addChilds(stringUi);
			listUi.push_back(ui);
		}
		listUi[0]->setPushFunc([this]() {this->EntityManager.entityFactory()->instanceEntityTerrainAABB(VECTOR3());});
		listUi[1]->setPushFunc([this]() {this->EntityManager.entityFactory()->instanceEntityTerrainCylinder(VECTOR3());});
		listUi[2]->setPushFunc([this]() {this->EntityManager.entityFactory()->instanceEntityGoal(VECTOR3());});
		listUi[3]->setPushFunc([this]() {this->EntityManager.entityFactory()->instanceEntityItem(VECTOR3());});
		listUi[4]->setPushFunc([this]() {this->EntityManager.entityFactory()->instanceEntityTarget(VECTOR3());});
		listUi[5]->setPushFunc([this]() {this->EntityManager.entityFactory()->instanceEntityEnemy(VECTOR3());});
		listUi[6]->setPushFunc([this]() {this->EntityManager.entityFactory()->instanceEntityEnemyCanon(VECTOR3());});

		UiScrollAppearEntityButtonList.create(
			UI_FACTORY::instance(c()->texture("UiScrollBack"), VECTOR2(0.0f, 0.0f), VECTOR2(2.0f, 1.5f)),
			UI_FACTORY::instance(c()->texture("UiScrollBarBack"), VECTOR2(112.0f, 40.0f), VECTOR2::one()),
			UI_FACTORY::instance(c()->texture("UiScrollBar"), VECTOR2(0.0f, 0.0f), VECTOR2::one()),
			UI_FACTORY::instance(c()->texture("UiScrollNodeBack"), VECTOR2(0.0f, 32.0f), VECTOR2::one()),
			UI_FACTORY::instance(c()->texture("UiScrollUp"), VECTOR2(112.0f, 32.0f), VECTOR2::one()),
			UI_FACTORY::instance(c()->texture("UiScrollDown"), VECTOR2(112.0f, 280.0f), VECTOR2::one()),
			std::move(listUi),
			8
		);
		UiScrollAppearEntityButtonList.rootUi()->setIsReleaseDisable(true);
		UiRoot->addChilds(UiScrollAppearEntityButtonList.rootUi());
	}
	Light.init(STRING_TREE(STRING_TREE::loadFile("Assets/ROUND/lightData.txt")));
	UiManager.setRootUi(UiRoot);
	UiAnnotationManager.init(commonData());
	UiAnnotationManager.setRootUi(UiRoot);
	for (int i = 0;i < EntityMarkDrawer.size();i++) {
		DRAWER::IMAGE2D* drawer = new DRAWER::IMAGE2D();
		drawer->setTexture(c()->texture("nodeConnectorIcon"));
		drawer->setScale(VECTOR2(1.0f, 1.0f));
		drawer->setColor(COLOR(1.0f, 1.0f, 1.0f, 0.5f));
		drawer->setPivot(drawer->drawMethodInvisible());
		EntityMarkDrawer[i] = drawer;
		EntityMarkDrawers.add(drawer);
	}
	SelectEntityIcon = new DRAWER::IMAGE2D();
	SelectEntityIcon->setTexture(c()->texture("saveDataLoadScrollDown"));
	SelectEntityIcon->setScale(VECTOR2(1.0f, 1.0f));
	SelectEntityIcon->setColor(COLOR(1.0f, 1.0f, 1.0f, 0.2f));
	EntityMarkDrawers.add(SelectEntityIcon);

}

SCENE_MAP_EDIT::~SCENE_MAP_EDIT() {
	for (auto& i : EntityMarkDrawer) {
		i->Delete();
	}
	delete UiRoot;
	delete SoftShadowShader;
	delete Camera;
}

void SCENE_MAP_EDIT::proc(){
	update();
	draw();
}

void SCENE_MAP_EDIT::save(){
	HWND hWnd = WINDOW::instance()->hostHandle();
	static OPENFILENAME     ofn;
	static TCHAR            szPath[MAX_PATH];
	static TCHAR            szFile[MAX_PATH];

	if (szPath[0] == TEXT('\0')) {
		GetCurrentDirectory(MAX_PATH, szPath);
	}
	if (ofn.lStructSize == 0) {
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = hWnd;
		ofn.lpstrInitialDir = szPath;       // 初期フォルダ位置
		ofn.lpstrFile = szFile;       // 選択ファイル格納
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrDefExt = TEXT(".txt");
		ofn.lpstrFilter = TEXT("テキストファイル(*.txt)\0*.txt\0");
		ofn.lpstrTitle = TEXT("マップデータファイルを保存します。");
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
	}
	if (GetSaveFileName(&ofn)) {
		MessageBox(hWnd, szFile, TEXT("ファイル名を付けて保存"), MB_OK);
	}
	EntityManager.saveEntitys((const char*)szFile);
}

void SCENE_MAP_EDIT::load() {
	HWND hWnd = WINDOW::instance()->hostHandle();
	static OPENFILENAME ofn = { 0 };
	static TCHAR strFile[MAX_PATH], strCustom[256] = TEXT("Before files\0*.*\0\0");

		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = hWnd;
		ofn.lpstrFilter = TEXT("Text files {*.txt}\0*.txt\0")
			TEXT("HTML files {*.htm}\0*.htm;*.html\0")
			TEXT("All files {*.*}\0*.*\0\0");
		ofn.lpstrCustomFilter = strCustom;
		ofn.nMaxCustFilter = 256;
		ofn.nFilterIndex = 0;
		ofn.lpstrFile = strFile;
		ofn.nMaxFile = MAX_PATH;
		ofn.Flags = OFN_FILEMUSTEXIST;
		GetOpenFileName(&ofn);
		EntityManager.loadEntitys((const char*)strFile);
}

void SCENE_MAP_EDIT::update(){
	INDEV* indev = INDEV::instance();
	indev->getState();
	if (indev->isPress(KEY_P) || indev->isPress(KEY_L)|| indev->isPress(KEY_K)) {
		EntityManager.activeUpdate();
	}
	else{
		EntityManager.update();
	}
	Camera->update();
	EntityManager.apearTempEntityTransfer();
	EntityManager.deleteUpdate();
	EntityManager.effekseerUpdate();
	EntityManager.updateProjView(Camera->proj(), Camera->view());
	auto& entityList = *EntityManager.entityList();
	for (int i = 0;i < EntityMarkDrawer.size();i++) {
		EntityMarkDrawer[i]->setPivot(DRAWER::IMAGE2D::drawMethodInvisible());
	}
	for (int i = 0;i < entityList.size();i++) {
		EntityMarkDrawer[i]->setPos(Camera->worldToScreenPoint(entityList[i]->componentPosition()->pos()));
		EntityMarkDrawer[i]->setPivot(DRAWER::IMAGE2D::drawMethodCentered());
	}

	if (indev->isTrigger(MOUSE_LBUTTON)) {
		SelectEntity = nullptr;
		for (int i = 0;i < EntityMarkDrawer.size();i++) {
			DRAWER::IMAGE2D& drawer = *EntityMarkDrawer[i];
			if (drawer.isInvisible()) continue;
			
			if (Calc2DRectAndPointIsHit(drawer.topLeftPos(), drawer.actualWh(), INPUT_COMMON::MousePosition(indev))) {
				SelectEntity = entityList[i];
				break;
			};
		}
	}
	if (indev->isTrigger(KEY_Z)) EntityTransformer.changeState(ENTITY_TRANSFORMER::STATE::POSITION);
	if (indev->isTrigger(KEY_X))EntityTransformer.changeState(ENTITY_TRANSFORMER::STATE::SCALE);
	//複製
	if (indev->isTrigger(KEY_C)) {
		if (SelectEntity != nullptr) {
			SelectEntity = EntityManager.entityFactory()->instanceEntityFromStringTree(STRING_TREE( SelectEntity->saveDataString()).at(0));
		}
	}
	//削除
	if (indev->isTrigger(KEY_T)) {
		if (SelectEntity != nullptr) {
			SelectEntity->Delete();
			SelectEntity = nullptr;
		}
	};
	if (indev->isPress(KEY_F)) {
		if (SelectEntity != nullptr) {
			auto position = SelectEntity->componentPosition();
			position->setPos(CalcFloorAndLineHitPoint(0.0f, Camera->cameraPos(), Camera->screenToWorldPoint(INPUT_COMMON::MousePosition(indev), 1.0f) - Camera->cameraPos()));
		}

	}
	if (SelectEntity != nullptr) {
		auto position = SelectEntity->componentPosition();
		SelectEntityIcon->setPos(Camera->worldToScreenPoint(position->pos()));
		SelectEntityIcon->setPivot(SelectEntityIcon->drawMethodCentered());
		EntityTransformer.change(SelectEntity);
	}
	else{
		SelectEntityIcon->setPivot(SelectEntityIcon->drawMethodInvisible());
	}
	DRAWER::IMAGE3D::setProjView(Camera->projView());
	UiManager.update();
	UiAnnotationManager.update();
}

void SCENE_MAP_EDIT::draw(){
	DEBUG_STR* ds = DEBUG_STR::instance();
	GRAPHIC* g = GRAPHIC::instance();
	g->clearTarget(COLOR(0.4f, 0.4f, 0.4f, 1.0f));
	SHADER* shader = image2d();
	auto shaderSet = [this](auto shader) {
		Light.shaderUpdate(shader);
		Camera->shaderUpdate(shader);
	};
	shaderSet(SoftShadowShader);
	shader = SoftShadowShader;
	Light.shaderUpdate(shader);
	EntityManager.draw3d();
	EntityManager.draw2d();
	shader = image2d();
	BEGIN_PATH_
		EntityMarkDrawers.draw(shader);
		UiRoot->draw(shader);
		UiAnnotationManager.draw(shader);
	ds->draw(shader);
	SceneManager->fade()->draw(shader);
	END_PATH_
	g->present();
}
