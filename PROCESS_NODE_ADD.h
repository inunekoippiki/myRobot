#pragma once
#include <array>
#include "UI.h"
class PROCESS_NODE_ADD{
public:
	PROCESS_NODE_ADD();
	~PROCESS_NODE_ADD();
	void create(
		CONTAINER* c,
		STATIC_FONT* font,
		STRING_TREE* data, 
		PROCESS_NODE_MANAGER* processNodeManager, 
		DRAWER::DRAWERS_SHADER* processNodeLineDrawers,
		PROCESS_NODE_LINER* processNodeLiner);
	UI* rootUi() { return ProceeNodeAddBar; }
	void draw(SHADER* shader);
private:
	//いづれかのプロセスノード追加ボタンを押した
	void onClickAddProcessButton(PROCESS_NODE* processNode);
	//プロセスノードをインスタンスして返す
	template<class T>
	T* processNodeInstance() {
		return new T(Container, Font, ProcessNodeLineDrawers, ProcessNodeLiner, ProcessNodeManager);
	}
	//参照オブジェクト
	PROCESS_NODE_MANAGER* ProcessNodeManager = nullptr;
	CONTAINER* Container = nullptr;
	STATIC_FONT* Font = nullptr;
	DRAWER::DRAWERS_SHADER* ProcessNodeLineDrawers = nullptr;
	PROCESS_NODE_LINER* ProcessNodeLiner = nullptr;
	//各ボタンUIの枠
	UI* ProceeNodeAddBar = nullptr;
	//各ボタンUI
	std::array<UI*, 11> ProcessNodeAddButtonUi = {};
	//音
	SOUND* SoundProcessNodeAdd = nullptr;
};

