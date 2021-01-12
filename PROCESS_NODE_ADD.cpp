#include "../Library/STRING_TREE.h"
#include "../Library/CONTAINER.h"
#include "../Library/MB_LIB.h"
#include "../Library/GRAPHIC.h"
#include "SOUND_MANAGER.h"
#include "UI_FACTORY.h"
#include "UI_FUNC_ATTACHER.h"
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
#include "PROCESS_NODE_SAVE.h"

#include "PROCESS_NODE_COMMAND/FACTORY.h"
#include "PROCESS_NODE_ADD.h"
PROCESS_NODE_ADD::PROCESS_NODE_ADD() {
}

PROCESS_NODE_ADD::~PROCESS_NODE_ADD() {
}

void PROCESS_NODE_ADD::create(
	CONTAINER* c,
	STATIC_FONT* font,
	STRING_TREE* data,
	PROCESS_NODE_MANAGER* processNodeManager,
	DRAWER::DRAWERS_SHADER* processNodeLineDrawers,
	PROCESS_NODE_LINER* processNodeLiner){

	//参照オブジェクトを設定
	Container = c;
	Font = font;
	ProcessNodeManager = processNodeManager;
	ProcessNodeLineDrawers = processNodeLineDrawers;
	ProcessNodeLiner = processNodeLiner;


	ProceeNodeAddBar = UI_FACTORY::instance(c->texture("processNodeAddBar"), VECTOR2(0.0f, 0.0f), VECTOR2::one());
	//各プロセスノード追加ボタンを作る
	ProcessNodeAddButtonUi[0] = UI_FACTORY::instance(c->texture("processNodeAddStartIcon"), VECTOR2(0.0f, 0.0f), VECTOR2::one());
	ProcessNodeAddButtonUi[0]->setPushFunc([this]() {this->onClickAddProcessButton(processNodeInstance<PROCESS_NODE_START>());});
	ProcessNodeAddButtonUi[1] = UI_FACTORY::instance(c->texture("processNodeAddOutputIcon"), VECTOR2(0.0f, 0.0f), VECTOR2::one());
	ProcessNodeAddButtonUi[1]->setPushFunc([this]() {this->onClickAddProcessButton(processNodeInstance<PROCESS_NODE_OUTPUT>());});
	ProcessNodeAddButtonUi[2] = UI_FACTORY::instance(c->texture("processNodeAddInputIcon"), VECTOR2(0.0f, 0.0f), VECTOR2::one());
	ProcessNodeAddButtonUi[2]->setPushFunc([this]() {this->onClickAddProcessButton(processNodeInstance<PROCESS_NODE_INPUT>());});
	ProcessNodeAddButtonUi[3] = UI_FACTORY::instance(c->texture("processNodeAddWaitIcon"), VECTOR2(0.0f, 0.0f), VECTOR2::one());
	ProcessNodeAddButtonUi[3]->setPushFunc([this]() {this->onClickAddProcessButton(processNodeInstance<PROCESS_NODE_WAIT>());});
	ProcessNodeAddButtonUi[4] = UI_FACTORY::instance(c->texture("processNodeAddCalculationIcon"), VECTOR2(0.0f, 0.0f), VECTOR2::one());
	ProcessNodeAddButtonUi[4]->setPushFunc([this]() {this->onClickAddProcessButton(processNodeInstance<PROCESS_NODE_CALCULATION>());});
	ProcessNodeAddButtonUi[5] = UI_FACTORY::instance(c->texture("processNodeAddAssignmentIcon"), VECTOR2(0.0f, 0.0f), VECTOR2::one());
	ProcessNodeAddButtonUi[5]->setPushFunc([this]() {this->onClickAddProcessButton(processNodeInstance<PROCESS_NODE_ASSIGNMENT>());});
	ProcessNodeAddButtonUi[6] = UI_FACTORY::instance(c->texture("processNodeAddIfIcon"), VECTOR2(0.0f, 0.0f), VECTOR2::one());
	ProcessNodeAddButtonUi[6]->setPushFunc([this]() {this->onClickAddProcessButton(processNodeInstance<PROCESS_NODE_IF>());});
	ProcessNodeAddButtonUi[7] = UI_FACTORY::instance(c->texture("processNodeAddJumpPointIcon"), VECTOR2(0.0f, 0.0f), VECTOR2::one());
	ProcessNodeAddButtonUi[7]->setPushFunc([this]() {this->onClickAddProcessButton(processNodeInstance<PROCESS_NODE_JUMP_POINT>());});
	ProcessNodeAddButtonUi[8] = UI_FACTORY::instance(c->texture("processNodeAddJumpIcon"), VECTOR2(0.0f, 0.0f), VECTOR2::one());
	ProcessNodeAddButtonUi[8]->setPushFunc([this]() {this->onClickAddProcessButton(processNodeInstance<PROCESS_NODE_JUMP>());});
	ProcessNodeAddButtonUi[9] = UI_FACTORY::instance(c->texture("processNodeAddJumpBackIcon"), VECTOR2(0.0f, 0.0f), VECTOR2::one());
	ProcessNodeAddButtonUi[9]->setPushFunc([this]() {this->onClickAddProcessButton(processNodeInstance<PROCESS_NODE_JUMP_BACK>());});
	ProcessNodeAddButtonUi[10] = UI_FACTORY::instance(c->texture("processNodeAddFunctionIcon"), VECTOR2(0.0f, 0.0f), VECTOR2::one());
	ProcessNodeAddButtonUi[10]->setPushFunc([this]() {this->onClickAddProcessButton(processNodeInstance<PROCESS_NODE_FUNCTION>());});

	//データ構造の読込
	STRING_TREE* processNodeAddButtonSTList = data->atw("processNodeAddButton")->atw("list");
	//基準位置
	VECTOR2 position = VECTOR2(13.0f, 13.0f);
	float space = 158.0f;
	for (int i = 0;i < ProcessNodeAddButtonUi.size();i++) {
		UI* ui = ProcessNodeAddButtonUi[i];
		//説明を設定
		std::string annotation = MB_LIB::replaceText(processNodeAddButtonSTList->atw(i)->atw("annotation")->data(), "\\n", "\n");
		ui->annotation()->setAnnotationString(annotation);
		//翳すと色が変わるようにする
		UI_FUNC_ATTACHER::OverlapColorChange(ui, /*※ダウンキャスト*/static_cast<UI_DRAWER_<DRAWER::IMAGE2D>*>(ui->drawer())->obj(), COLOR(1.0f, 0.9f, 0.9f, 1.0f));
		//UIの位置を設定
		ui->setPos(VECTOR2(position.x + space * i, position.y));
		//親に追加
		ProceeNodeAddBar->addChilds(ui);
	}
	//音の設定
	SoundProcessNodeAdd = c->sound("nodeAdd");
}

void PROCESS_NODE_ADD::draw(SHADER* shader){
	ProceeNodeAddBar->draw(shader);
}

void PROCESS_NODE_ADD::onClickAddProcessButton(PROCESS_NODE* processNode){
	GRAPHIC* g = GRAPHIC::instance();
	VECTOR2 pos = ProcessNodeManager->processNodeListUi()->worldPosToLocalPos(VECTOR2(g->centerX(), g->centerY()));
	auto command = PROCESS_NODE_COMMAND::instanceAdd(pos, processNode, ProcessNodeManager);
	ProcessNodeManager->commandStream()->push(command);
	command->execute();
	SOUND_MANAGER::instance()->playSound(SoundProcessNodeAdd);
}
