#include <filesystem>
#include "../Library/common.h"
#include "../Library/CONTAINER.h"
#include "../Library/STRING_TREE.h"
#include "DRAWER.h"
#include "DRAWER_STATIC_FONT.h"
#include "UI_FACTORY.h"
#include "SOUND_MANAGER.h"
#include "PROCESS_NODE_MANAGER.h"
#include "PROCESS_NODE_SAVE.h"
#include "PROCESS_NODE_LOAD.h"
#include "PROCESS_NODE_COMMAND/FACTORY.h"
#include "PROCESS_NODE_LOAD_SCROLL.h"

const std::string PROCESS_NODE_LOAD_SCROLL::DesignDataSavePath{ "saveData/design/" };

PROCESS_NODE_LOAD_SCROLL::PROCESS_NODE_LOAD_SCROLL(CONTAINER* c, STATIC_FONT* font, PROCESS_NODE_MANAGER* processNodeManager) :
	C(c),
	Font(font),
	ProcessNodeManager(processNodeManager) {
	//音
	SoundSaveDataDelete = c->sound("nodeDelete");
	SoundSaveDataLoad = c->sound("load");
}
PROCESS_NODE_LOAD_SCROLL::~PROCESS_NODE_LOAD_SCROLL() {
	UiScroll.listUi()->clear();
	for (auto& i : NodeList) {
		delete i;
	}
}
void PROCESS_NODE_LOAD_SCROLL::create(PROCESS_NODE_MANAGER* processNodeManager) {
	UiScroll.create(
		UI_FACTORY::instance(C->texture("saveDataLoadScrollBack"), VECTOR2(0.0f, 0.0f), VECTOR2::one()),
		UI_FACTORY::instance(C->texture("saveDataLoadScrollBarBack"), VECTOR2(1216.0f, 128.0f), VECTOR2::one()),
		UI_FACTORY::instance(C->texture("saveDataLoadScrollBar"), VECTOR2(0.0f, 0.0f), VECTOR2::one()),
		UI_FACTORY::instance(C->texture("saveDataLoadScrollNodeBack"), VECTOR2(0.0f, 64.0f), VECTOR2::one()),
		UI_FACTORY::instance(C->texture("saveDataLoadScrollUp"), VECTOR2(1216.0f, 64.0f), VECTOR2::one()),
		UI_FACTORY::instance(C->texture("saveDataLoadScrollDown"), VECTOR2(1216.0f, 768.0f), VECTOR2::one()),
		std::vector<UI*>(),
		8
	);
	UiScroll.rootUi()->setPushFunc([this]() {endScrollDisp();});
	UiScroll.rootUi()->setIsReleaseDisable(true);
	UiScroll.rootUi()->setIsUnconditionalCollisionHit(true);
}
void PROCESS_NODE_LOAD_SCROLL::SaveDataListScrollUpdate() {
	auto listUi = UiScroll.listUi();
	listUi->clear();
	for (auto& i : NodeList) {
		delete i;
	}
	NodeList.clear();
	//ディレクトリからセーブデータをリストに追加
	for (const auto& e : std::filesystem::directory_iterator(DesignDataSavePath)) {
		NodeList.push_back(new SCROLL_NODE(e.path().filename().string(), C, Font, this));
	}
	//名前（日付）でソート
	sort(NodeList.begin(), NodeList.end(), [](SCROLL_NODE* a, SCROLL_NODE* b)->bool {return a->drawerString() > b->drawerString();});
	//スクロールのリストにUIを入れる
	for (int i = 0;i < NodeList.size(); i++) {
		listUi->push_back(NodeList[i]->rootUi());
	}

	UiScroll.scrollUpdate(0);
}

void PROCESS_NODE_LOAD_SCROLL::deleteSaveData(const std::string& fileName) {
	std::filesystem::remove(DesignDataSavePath + fileName);
	SaveDataListScrollUpdate();
}

void PROCESS_NODE_LOAD_SCROLL::load(const std::string& data) {
	std::ifstream ifs(DesignDataSavePath + data);
	STRING_TREE tree(std::string{ istreambuf_iterator<char>(ifs),istreambuf_iterator<char>() });
	std::vector<PROCESS_NODE*> addList;
	PROCESS_NODE_LOAD::load(tree, C, Font, ProcessNodeManager, addList);
	auto command = PROCESS_NODE_COMMAND::instanceOperatorLoad(tree.atw("root")->atw("connector")->data(), addList, ProcessNodeManager);
	ProcessNodeManager->commandStream()->push(command);
	command->execute();
	endScrollDisp();
	SOUND_MANAGER::instance()->playSound(SoundSaveDataLoad);
}

void PROCESS_NODE_LOAD_SCROLL::endScrollDisp() {
	UiScroll.rootUi()->setIsDisable(true);
}

PROCESS_NODE_LOAD_SCROLL::SCROLL_NODE::SCROLL_NODE(const std::string& s, CONTAINER* c, STATIC_FONT* font, PROCESS_NODE_LOAD_SCROLL* processNodeLoad) {
	//枠
	RootUi.create(DRAWER::IMAGE2D::instance(c->texture("saveDataLoadScrollNode"), VECTOR2(0.0f, 0.0f), VECTOR2::one()));
	RootUi.setIsReleaseDisable(true);
	//セーブデータ名
	Drawer = DRAWER::STATIC_FONT::instance(s.c_str(), font, VECTOR2(), VECTOR2(96.0f, 96.0f), DRAWER::STATIC_FONT::drawMethodAdjustDraw_Over());
	Drawer->setMaxWidth(22);
	StringUi.create(Drawer);
	StringUi.setIsCollisionDisable(true);
	StringUi.setIsReleaseDisable(true);
	RootUi.addChilds(&StringUi);
	//セーブデータ削除ボタン
	DeleteIcon.create(DRAWER::IMAGE2D::instance(c->texture("saveDataLoadScrollNodeDelete"), VECTOR2(1120.0f, 0.0f), VECTOR2::one()));
	DeleteIcon.setIsReleaseDisable(true);
	//DeleteIcon.setPushFunc([this, processNodeLoad]() {processNodeLoad->deleteSaveData(Drawer->string());});
	//セーブデータ削除を長押しする時間
	DeleteFrame = 60;
	//セーブデータ削除の誤操作を防ぐため長押ししないと消せないようにする
	DeleteIcon.setDragUpdate([this, processNodeLoad]() {
		if (++DeleteFrameCnt >= DeleteFrame) {
			SOUND_MANAGER::instance()->playSound(processNodeLoad->SoundSaveDataDelete);
			processNodeLoad->deleteSaveData(Drawer->string());//ここで自殺
			return;
		};
		DeleteIconOver.setScale(VECTOR2(1.0f, (float)DeleteFrameCnt / DeleteFrame));
	}
	);
	DeleteIcon.setDragEndFunc([this]() {
		DeleteIconOver.setScale(VECTOR2(1.0f, 0.0f));
		DeleteFrameCnt = 0;}
	);
	DeleteIconOver.create(DRAWER::IMAGE2D::instance(c->texture("saveDataLoadScrollNodeDeleteOver"), VECTOR2(), VECTOR2::one()));
	DeleteIconOver.setIsReleaseDisable(true);
	DeleteIconOver.setIsCollisionDisable(true);
	DeleteIcon.addChilds(&DeleteIconOver);
	DeleteIconOver.setScale(VECTOR2(1.0f, 0.0f));
	RootUi.addChilds(&DeleteIcon);
	RootUi.setPushFunc([this, processNodeLoad]() {processNodeLoad->load(Drawer->string());});
}

PROCESS_NODE_LOAD_SCROLL::SCROLL_NODE::~SCROLL_NODE() {
}

void PROCESS_NODE_LOAD_SCROLL::SCROLL_NODE::changeString(const std::string& s) {
	Drawer->setString(s);
}

std::string PROCESS_NODE_LOAD_SCROLL::SCROLL_NODE::drawerString() {
	return Drawer->string();
}

