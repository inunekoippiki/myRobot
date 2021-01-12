#pragma once
#include <utility>
#include <string>
#include "UI.h"
#include "PROCESS_NODE_FUNC_SET.h"
#include "PROCESS_NODE_FRAME.h"
class CONTAINER;
class STATIC_FONT;
class STRING_TREE;
class PROCESS_NODE_LINER;
class PROCESS_NODE_CONNECTOR_IN;
class PROCESS_NODE_CONNECTOR_OUT;
class NODE_LINE;
class PROCESS_NODE_MANAGER;
class ROBOT_PROCESSOR;
class ROBOT_COMPILER;
class UI_SCROLL;

class PROCESS_NODE {
public:
	PROCESS_NODE();
	virtual ~PROCESS_NODE() {};
	UI* rootUi();
	//前のコネクターノードを返す(複数)
	virtual std::pair<PROCESS_NODE_CONNECTOR_IN**, int> allNodeConnectorIn() = 0;
	//後ろのコネクターノードを返す(複数)
	virtual std::pair<PROCESS_NODE_CONNECTOR_OUT**, int> allNodeConnectorOut() = 0;
	//セーブ用のデータ文字列を返す
	virtual std::string saveDataString() = 0;
	//セーブ用のデータ文字列から読み込む
	virtual void loadFromSaveString(const STRING_TREE& data) = 0;
	//実行の前の準備。ROBOT_COMPILERを介してデータを作成する
	virtual void compile(ROBOT_COMPILER* robotCompiler) = 0;
	//実行
	virtual void nextStep(ROBOT_PROCESSOR* robotProcessor) = 0;
	//活性化処理
	virtual void setEnable() = 0;
	//非活性化処理
	virtual void setDisable() = 0;

	//ノードに繋がってる線を更新
	static void lineUpdate(PROCESS_NODE* processNode);
	//PROCESSノードが持つ線の制御点を制御点用のレイヤーUIに追加する
	static void addLinePointUiToRootUi(PROCESS_NODE* processNode, UI* linePointRootUi);
	//PROCESSノードが持つ線の制御点を制御点用のレイヤーUIから削除する
	static void removeLinePointUiToRootUi(PROCESS_NODE* processNode);
	//繋がっていたコネクターに自身が消えたことを通知
	static void disconnect(PROCESS_NODE* processNode);


protected:
	static UI* instanceNodeTypeNameUi(const char* name, STATIC_FONT* font);
	template<class INPUT_OBJ>
	static void startScrollInput(UI* ui, UI_SCROLL* scroll, PROCESS_NODE_MANAGER* processNodeManager, INPUT_OBJ* inputObj) {
		auto callback = PROCESS_NODE_FUNC_SET::inputObjSetStringFunc(inputObj, processNodeManager);
		PROCESS_NODE_FUNC_SET::startScrollInputAnyCallback(ui, scroll, processNodeManager, callback);
	};
	template<class INPUT_OBJ>
	static void startKeyboardInput(UI* ui, PROCESS_NODE_MANAGER* processNodeManager, INPUT_OBJ* inputObj) {
		auto callback = PROCESS_NODE_FUNC_SET::inputObjSetStringFunc(inputObj, processNodeManager);
		PROCESS_NODE_FUNC_SET::startKeyboardInputAnyCallback(ui, processNodeManager, callback);
	}

	PROCESS_NODE_FRAME Frame ;
private:
};

