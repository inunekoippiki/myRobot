#pragma once
#include <string>
#include <vector>
#include "PROCESS_NODE_TYPE.h"
class VECTOR2;
//形式
/*
タイプ
位置
文字列情報
Inノード情報
Outノード情報
ライン情報
*/

/*
IF
{
	type{if}
	pos{x{}y{}}
	variable1{}
	variable2{}
	comparison{}
}
*/
/*
INPUT
{
	type{input}
	pos{x{}y{}}
	variable1{}
	variable2{}
	comparison{}
}

connectorData
[
	{
		outNode[
			{idx{node{}connector{}}line{num{}points[{}{}{}{}{}{}]}}
			{idx{node{}connector{}}line{num{}points[{}{}{}{}{}{}]}}
		]
	}

	{
		outNode[
			{idx{node{}connector{}}line{num{}points[{}{}{}{}{}{}]}}
		]
	}
]
*/
class PROCESS_NODE;

class PROCESS_NODE_SAVE{
public:
	PROCESS_NODE_SAVE();
	~PROCESS_NODE_SAVE();
	//全てのノードに必要な情報を文字列にして返す
	static std::string commonSaveDataString(const std::string& typeName, const VECTOR2& pos);
	//ディレクトリに保存
	static void saveDesignData(const std::string& saveName,const std::string& designData);
	//processNodeリストをセーブ用の文字列に変換する
	static std::string ProcessNodeToSaveDataString(const std::vector<PROCESS_NODE*>& selectList);
	//セーブする時のノードタイプごとの文字列を返す
	static std::string getTypeStringName(PROCESS_NODE_TYPE type);
	//文字列をノードタイプに変換
	static PROCESS_NODE_TYPE stringNameToType(const std::string& s);

private:
	static std::unordered_map<std::string, PROCESS_NODE_TYPE> StringNameToTypeTable;
};

