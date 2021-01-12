#pragma once
#include <string>
#include <vector>
#include "PROCESS_NODE_TYPE.h"
class VECTOR2;
//�`��
/*
�^�C�v
�ʒu
��������
In�m�[�h���
Out�m�[�h���
���C�����
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
	//�S�Ẵm�[�h�ɕK�v�ȏ��𕶎���ɂ��ĕԂ�
	static std::string commonSaveDataString(const std::string& typeName, const VECTOR2& pos);
	//�f�B���N�g���ɕۑ�
	static void saveDesignData(const std::string& saveName,const std::string& designData);
	//processNode���X�g���Z�[�u�p�̕�����ɕϊ�����
	static std::string ProcessNodeToSaveDataString(const std::vector<PROCESS_NODE*>& selectList);
	//�Z�[�u���鎞�̃m�[�h�^�C�v���Ƃ̕������Ԃ�
	static std::string getTypeStringName(PROCESS_NODE_TYPE type);
	//��������m�[�h�^�C�v�ɕϊ�
	static PROCESS_NODE_TYPE stringNameToType(const std::string& s);

private:
	static std::unordered_map<std::string, PROCESS_NODE_TYPE> StringNameToTypeTable;
};

