#pragma once
class VECTOR2;
class CONTAINER;
class STATIC_FONT;
class PROCESS_NODE;
class PROCESS_NODE_MANAGER;
class PROCESS_NODE_LINER;
class STRING_TREE;
namespace DRAWER {
	class DRAWERS_SHADER;
}
class PROCESS_NODE_LOAD {
public:
	//stringTreeの設計データを読んでノードを追加する
	static void load(
		const STRING_TREE& stringTree,
		CONTAINER* c,
		STATIC_FONT* font,
		PROCESS_NODE_MANAGER* processNodeManager,
		std::vector<PROCESS_NODE*>& addList
	);
	static void load(
		const STRING_TREE& stringTree,
		CONTAINER* c,
		STATIC_FONT* font,
		PROCESS_NODE_MANAGER* processNodeManager
	);
	static void nodeLoad(
		const STRING_TREE* nodeTree,
		CONTAINER* c,
		STATIC_FONT* font,
		PROCESS_NODE_MANAGER* processNodeManager,
		std::vector<PROCESS_NODE*>& addList
	);
	static void nodeLoad(
		const STRING_TREE* nodeTree,
		CONTAINER* c,
		STATIC_FONT* font,
		PROCESS_NODE_MANAGER* processNodeManager
	);
	static void lineLoad(
		STRING_TREE* connectorTree,
		const std::vector<PROCESS_NODE*>& addList, 
		PROCESS_NODE_MANAGER* processNodeManager
	);
	//stringTreeからノード一つを生成
	static PROCESS_NODE* instanceFromSaveString(
		const STRING_TREE& data,
		CONTAINER* c,
		STATIC_FONT* font,
		DRAWER::DRAWERS_SHADER* lineDrawers,
		PROCESS_NODE_LINER* processNodeLiner,
		PROCESS_NODE_MANAGER* processNodeManager
	);
	//位置データを読み込む
	static VECTOR2 loadSaveDataStringPos(const STRING_TREE& data);
};