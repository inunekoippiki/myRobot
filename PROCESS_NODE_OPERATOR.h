#pragma once
#include "../Library/VECTOR2.h"
#include "UI.h"
class PROCESS_NODE_OPERATOR {
public:
	PROCESS_NODE_OPERATOR();
	~PROCESS_NODE_OPERATOR();
	void create(CONTAINER* c,
		class PROCESS_NODE_MANAGER* processNodeManager,
		class PROCESS_NODE_SELECTOR* processNodeSelector);
	UI* rootUi() { return ProceeNodeOperationBar; }
private:
	void onClickNodeUndo();
	void onClickNodeRedo();
	void onClickNodeAlignmentX();
	void onClickNodeAlignmentY();
	void onDownNodeMove();
	void onDragNodeMove();
	void onDragEndNodeMove();
	void onClickNodeCopy();
	void onClickNodePaste();
	void onClickNodeDelete();
	void onClickNodeSave();
	void onClickNodeLoad();
	//参照オブジェクト
	class PROCESS_NODE_MANAGER* ProcessNodeManager = nullptr;
	class PROCESS_NODE_SELECTOR* ProcessNodeSelector = nullptr;


	UI* ProceeNodeOperationBar = nullptr;
	UI* ProcessNodeDeleteButtonUi = nullptr;
	UI* ProcessNodeUndoButtonUi = nullptr;
	UI* ProcessNodeRedoButtonUi = nullptr;
	UI* ProcessNodeAlignmentXButtonUi = nullptr;
	UI* ProcessNodeAlignmentYButtonUi = nullptr;
	UI* ProcessNodeMoveButtonUi = nullptr;
	VECTOR2 MouseDownPos;
	VECTOR2 MoveNodeTotal;
	UI* ProcessNodeCopyButtonUi = nullptr;
	UI* ProcessNodePasteButtonUi = nullptr;
	UI* ProcessNodeSaveButtonUi = nullptr;
	UI* ProcessNodeLoadButtonUi = nullptr;
	//音
	SOUND* SoundButton = nullptr;
	SOUND* SoundProcessDelete = nullptr;
	SOUND* SoundProcessDeleteAndo = nullptr;
};

