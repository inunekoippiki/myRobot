#pragma once
#include <unordered_map>
#include <stack>
#include "ROBOT_COMPILER.h"
#include "UI_ANNOTATION.h"
#include "OUTPUT_MODULE_LIST.h"
#include "INPUT_MODULE_LIST.h"
class OUTPUT_MODULE_VALUE;
class INPUT_MODULE_VALUE;
class PROCESS_NODE;
class PROCESS_NODE_JUMP_BACK;
class PROCESS_NODE_START;
class ROBOT_PROCESSOR{
public:
	ROBOT_PROCESSOR();
	~ROBOT_PROCESSOR();
	//出力モジュールリストを適用
	void createOutputModuleList(OUTPUT_MODULE_LIST&& outputModuleList);
	//入力モジュールリストを適用
	void createInputModuleList(INPUT_MODULE_LIST&& inputModuleList);
	//出力モジュールリストに追加
	void addOutputModule(const std::string& s,const OUTPUT_MODULE_DATA& data);
	//入力モジュールリストに追加
	void addInputModule(const std::string& s, const INPUT_MODULE_DATA& data);
	//ノードを実行するための準備
	void startCompile(const std::vector<PROCESS_NODE*>& processNodeList);
	//開始ノードをセットする
	void setProcessNodeStart(PROCESS_NODE_START* processNodeStart);
	//開始ノードを返す。無いとnullptr
	PROCESS_NODE_START* processNodeStart() { return ProcessNodeStart; }
	auto& outputModuleList(){ return OutputModuleList; }
	auto& inputModuleList() { return InputModuleList; }
	auto& jumpPointList() { return JumpPointList; }
	auto& variableList() { return VariableList; }
	//アウトプットモジュールの値を返す
	double outputModule(const std::string& s);
	//インプットモジュールに値を送る
	void inputModule(const std::string& s,double value);
	//変数を返す
	double variable(const std::string& s);
	//変数を代入する
	void setVariable(const std::string& s, double value);
	//実行する
	void stepStart();
	//前のフレームの続きから実行を始める
	void stepIn();
	//1フレームに実行できるプロセス数を加算。上限以上だとtrueを返す
	bool stepCnt();
	//フレーム数を秒にする
	double waitFrameTime();
	//待機ノードの待ち時間タイマーを進める
	void addTime();
	//待機ノードの待ち時間タイマーをリセットする
	void resetTime();
	//1フレームの実行の終わり
	void oneFrameProcessEnd(PROCESS_NODE* processNode);
	//ジャンプバックに入る時
	void JumpBackIn(PROCESS_NODE_JUMP_BACK* processNode);
	//次のノードがないとき、ジャンプバックの中だったらジャンプバックの入り口まで戻す
	void JumpBackReturn();
	//実行終わり
	void ProcessEnd();

	const ROBOT_COMPILER* robotCompiler()const { return &RobotCompiler; }
	const auto& jumpBackPointStack() {return JumpBackPointStack; }
private:
	//一フレームに実行したプロセス数
	int OneFrameStepCnt = 0;
	//待機ノード用のタイマー
	int WaitFrameCnt = 0;
	//現在のノード
	PROCESS_NODE* CurrentProcessNode = nullptr;
	//開始ノード
	PROCESS_NODE_START* ProcessNodeStart = nullptr;
	using JUMP_BACK_POINT_STACK = std::stack<PROCESS_NODE_JUMP_BACK*, std::vector<PROCESS_NODE_JUMP_BACK*>>;
	//ジャンプバックに入る時積むスタック
	JUMP_BACK_POINT_STACK JumpBackPointStack;
	//出力モジュールリスト
	OUTPUT_MODULE_LIST OutputModuleList;
	//入力モジュールリスト
	INPUT_MODULE_LIST InputModuleList;
	//ジャンプポイントリスト
	std::unordered_map<std::string, PROCESS_NODE*> JumpPointList;
	//変数リスト
	std::unordered_map<std::string, double> VariableList;
	//UIのノード情報から実行準備をする
	ROBOT_COMPILER RobotCompiler;
	//ジャンプバック内の時戻るべきノードを返す。そうでなかったらnullptrを返す
	PROCESS_NODE_JUMP_BACK* jumpBackOut();
};

