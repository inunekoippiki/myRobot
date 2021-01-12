#include "../Library/WINDOW.h"
#include "../Library/CONTAINER.h"
#include "../Library/INDEV.h"
#include "../Library/GRAPHIC.h"
#include "../Library/DEBUG_STR.h"
#include "UI_FACTORY.h"
#include "INPUT_COMMON.h"
#include "SOUND_MANAGER.h"
#include "PROCESS_NODE_SELECTOR.h"
#include "PROCESS_NODE_MANAGER.h"
#include "PROCESS_NODE_COMMAND/FACTORY.h"
#include "PROCESS_NODE_OPERATOR.h"
PROCESS_NODE_OPERATOR::PROCESS_NODE_OPERATOR() {
}

PROCESS_NODE_OPERATOR::~PROCESS_NODE_OPERATOR() {
}

void PROCESS_NODE_OPERATOR::create(
	CONTAINER* c,
	PROCESS_NODE_MANAGER* processNodeManager,
	PROCESS_NODE_SELECTOR* processNodeSelector) {
	ProcessNodeManager = processNodeManager;
	ProcessNodeSelector = processNodeSelector;
	//操作バー
	ProceeNodeOperationBar = UI_FACTORY::instance(c->texture("processNodeOperationBar"), VECTOR2(457.0f, 928.0f), VECTOR2::one());
	ProceeNodeOperationBar->setIsChildCollisionRestrict(true);
	VECTOR2 position = VECTOR2(6.0f, 6.0f);
	VECTOR2 space = VECTOR2(122.0f, 0.0f);

	ProcessNodeUndoButtonUi = UI_FACTORY::instance(c->texture("processNodeOperationUndo"), position + space * 0.0f, VECTOR2::one());
	ProcessNodeUndoButtonUi->setPushFunc([this]() {onClickNodeUndo();});
	ProcessNodeRedoButtonUi = UI_FACTORY::instance(c->texture("processNodeOperationRedo"), position + space * 1.0f, VECTOR2::one());
	ProcessNodeRedoButtonUi->setPushFunc([this]() {onClickNodeRedo();});
	ProcessNodeAlignmentXButtonUi = UI_FACTORY::instance(c->texture("processNodeOperationAlignmentX"), position + space * 2.0f, VECTOR2::one());
	ProcessNodeAlignmentXButtonUi->setPushFunc([this]() {onClickNodeAlignmentX();});
	ProcessNodeAlignmentYButtonUi = UI_FACTORY::instance(c->texture("processNodeOperationAlignmentY"), position + space * 3.0f, VECTOR2::one());
	ProcessNodeAlignmentYButtonUi->setPushFunc([this]() {onClickNodeAlignmentY();});
	ProcessNodeMoveButtonUi = UI_FACTORY::instance(c->texture("processNodeOperationMove"), position + space * 4.0f, VECTOR2::one());
	ProcessNodeMoveButtonUi->setDownFunc([this]() {onDownNodeMove();});
	ProcessNodeMoveButtonUi->setDragUpdate([this]() {onDragNodeMove();});
	ProcessNodeMoveButtonUi->setDragEndFunc([this]() {onDragEndNodeMove();});
	ProcessNodeCopyButtonUi = UI_FACTORY::instance(c->texture("processNodeOperationCopyIcon"), position + space * 5.0f, VECTOR2::one());
	ProcessNodeCopyButtonUi->setPushFunc([this]() {onClickNodeCopy();});
	ProcessNodePasteButtonUi = UI_FACTORY::instance(c->texture("processNodeOperationPasteIcon"), position + space * 6.0f, VECTOR2::one());
	ProcessNodePasteButtonUi->setPushFunc([this]() {onClickNodePaste();});
	ProcessNodeDeleteButtonUi = UI_FACTORY::instance(c->texture("processNodeOperationDeleteIcon"), position + space * 7.0f, VECTOR2::one());
	ProcessNodeDeleteButtonUi->setPushFunc([this]() {onClickNodeDelete();});
	ProcessNodeSaveButtonUi = UI_FACTORY::instance(c->texture("processNodeOperationSaveIcon"), position + space * 8.0f, VECTOR2::one());
	ProcessNodeSaveButtonUi->setPushFunc([this]() {onClickNodeSave();});
	ProcessNodeLoadButtonUi = UI_FACTORY::instance(c->texture("processNodeOperationLoadIcon"), position + space * 9.0f, VECTOR2::one());
	ProcessNodeLoadButtonUi->setPushFunc([this]() {onClickNodeLoad();});
	ProceeNodeOperationBar->child()->reserve(8);
	ProceeNodeOperationBar->addChilds(ProcessNodeUndoButtonUi);
	ProceeNodeOperationBar->addChilds(ProcessNodeRedoButtonUi);
	ProceeNodeOperationBar->addChilds(ProcessNodeAlignmentXButtonUi);
	ProceeNodeOperationBar->addChilds(ProcessNodeAlignmentYButtonUi);
	ProceeNodeOperationBar->addChilds(ProcessNodeMoveButtonUi);
	ProceeNodeOperationBar->addChilds(ProcessNodeCopyButtonUi);
	ProceeNodeOperationBar->addChilds(ProcessNodePasteButtonUi);
	ProceeNodeOperationBar->addChilds(ProcessNodeDeleteButtonUi);
	ProceeNodeOperationBar->addChilds(ProcessNodeSaveButtonUi);
	ProceeNodeOperationBar->addChilds(ProcessNodeLoadButtonUi);
	//音
	SoundButton = c->sound("button");
	SoundProcessDelete = c->sound("nodeDelete");
	SoundProcessDeleteAndo = c->sound("nodeDeleteAndo");

}
void PROCESS_NODE_OPERATOR::onClickNodeUndo(){
	ProcessNodeManager->commandStream()->undo();
	SOUND_MANAGER::instance()->playSound(SoundButton);
}

void PROCESS_NODE_OPERATOR::onClickNodeRedo(){
	ProcessNodeManager->commandStream()->redo();
	SOUND_MANAGER::instance()->playSound(SoundButton);
}

void PROCESS_NODE_OPERATOR::onClickNodeAlignmentX() {
	auto command = PROCESS_NODE_COMMAND::instanceOperatorAlignment(
		PROCESS_NODE_COMMAND::ALIGNMENT_TYPE::X,
		ProcessNodeSelector);
	ProcessNodeManager->commandStream()->push(command);
	command->execute();
	SOUND_MANAGER::instance()->playSound(SoundButton);
}

void PROCESS_NODE_OPERATOR::onClickNodeAlignmentY() {
	auto command = PROCESS_NODE_COMMAND::instanceOperatorAlignment(
		PROCESS_NODE_COMMAND::ALIGNMENT_TYPE::Y,
		ProcessNodeSelector);
	ProcessNodeManager->commandStream()->push(command);
	command->execute();
	SOUND_MANAGER::instance()->playSound(SoundButton);
}

void PROCESS_NODE_OPERATOR::onDownNodeMove() {
	INDEV* in = INDEV::instance();
	MouseDownPos = INPUT_COMMON::MousePosition(in);
	ShowCursor(false);
}

void PROCESS_NODE_OPERATOR::onDragNodeMove() {
	GRAPHIC* g = GRAPHIC::instance();
	WINDOW* w = WINDOW::instance();
	INDEV* in = INDEV::instance();
	VECTOR2 move = (INPUT_COMMON::MousePosition(in)- MouseDownPos) / ProcessNodeManager->processNodeListUi()->absoluteScale();
	MoveNodeTotal += move;
	ProcessNodeSelector->moveSelectProcessNode(move);
	//ウインドウの座標に変換
	VECTOR2 clientMousePoint = MouseDownPos / (g->baseWh() / g->wh());
	POINT p{ clientMousePoint.x,clientMousePoint.y };
	ClientToScreen(w->hostHandle(), &p);
	//マウスポインターを固定
	SetCursorPos((int)p.x, (int)p.y);
}

void PROCESS_NODE_OPERATOR::onDragEndNodeMove(){
	auto command = PROCESS_NODE_COMMAND::instanceOperatorMove(MoveNodeTotal, ProcessNodeSelector);
	ProcessNodeManager->commandStream()->push(command);
	MoveNodeTotal = VECTOR2();
	ShowCursor(true);
}

void PROCESS_NODE_OPERATOR::onClickNodeCopy() {
	ProcessNodeSelector->CopySelectProcessNode();
	SOUND_MANAGER::instance()->playSound(SoundButton);
}

void PROCESS_NODE_OPERATOR::onClickNodePaste() {

	ProcessNodeSelector->processNodePaste();
	SOUND_MANAGER::instance()->playSound(SoundButton);
}

void PROCESS_NODE_OPERATOR::onClickNodeDelete() {
	auto command = PROCESS_NODE_COMMAND::instanceOperatorDelete(ProcessNodeSelector, ProcessNodeManager);
	ProcessNodeManager->commandStream()->push(command);
	command->execute();
	SOUND_MANAGER::instance()->playSound(SoundProcessDelete);
}

void PROCESS_NODE_OPERATOR::onClickNodeSave() {
	ProcessNodeManager->startSaveDataSaveKeyBoard();
	SOUND_MANAGER::instance()->playSound(SoundButton);
}

void PROCESS_NODE_OPERATOR::onClickNodeLoad() {
	ProcessNodeManager->startSaveDataLoadScroll();
	SOUND_MANAGER::instance()->playSound(SoundButton);
}
