#include <chrono>
#include <sstream>
#include "../Library/VECTOR2.h"
#include "../Library/STRING_TREE.h"
#include "../Library/common.h"
#include "NODE_LINE.h"
#include "PROCESS_NODE.h"
#include "PROCESS_NODE_CONNECTOR.h"
#include "PROCESS_NODE_SAVE.h"

std::unordered_map<std::string, PROCESS_NODE_TYPE> PROCESS_NODE_SAVE::StringNameToTypeTable =
{
{getTypeStringName(PROCESS_NODE_TYPE::START),		PROCESS_NODE_TYPE::START} ,
{getTypeStringName(PROCESS_NODE_TYPE::INPUT),		PROCESS_NODE_TYPE::INPUT} ,
{getTypeStringName(PROCESS_NODE_TYPE::OUTPUT),		PROCESS_NODE_TYPE::OUTPUT} ,
{getTypeStringName(PROCESS_NODE_TYPE::ASSIGNMENT),	PROCESS_NODE_TYPE::ASSIGNMENT} ,
{getTypeStringName(PROCESS_NODE_TYPE::CALCULATION),	PROCESS_NODE_TYPE::CALCULATION} ,
{getTypeStringName(PROCESS_NODE_TYPE::IF),			PROCESS_NODE_TYPE::IF} ,
{getTypeStringName(PROCESS_NODE_TYPE::WAIT),		PROCESS_NODE_TYPE::WAIT} ,
{getTypeStringName(PROCESS_NODE_TYPE::JUMP_POINT),	PROCESS_NODE_TYPE::JUMP_POINT} ,
{getTypeStringName(PROCESS_NODE_TYPE::JUMP),		PROCESS_NODE_TYPE::JUMP} ,
{getTypeStringName(PROCESS_NODE_TYPE::JUMP_BACK),	PROCESS_NODE_TYPE::JUMP_BACK} ,
{getTypeStringName(PROCESS_NODE_TYPE::FUNCTION),	PROCESS_NODE_TYPE::FUNCTION}
};

PROCESS_NODE_SAVE::PROCESS_NODE_SAVE() {
}

PROCESS_NODE_SAVE::~PROCESS_NODE_SAVE() {
}

std::string PROCESS_NODE_SAVE::commonSaveDataString(const std::string& typeName, const VECTOR2& pos){
	return "type{"+ typeName+"}"
			"pos{"+"x{"+ std::to_string(pos.x) +"}"+
				   "y{"+ std::to_string(pos.y) +"}"+
			"}";
}

void PROCESS_NODE_SAVE::saveDesignData(const std::string& saveName, const std::string& designData){
	time_t saveTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	tm saveTimeTm;
	localtime_s(&saveTimeTm, &saveTime);
	std::stringstream ss;
	ss << 
		std::setw(4) << std::setfill('0') << saveTimeTm.tm_year + 1900<<
		std::setw(2) << std::setfill('0') << saveTimeTm.tm_mon + 1 <<
		std::setw(2) << std::setfill('0') << saveTimeTm.tm_mday <<
		std::setw(2) << std::setfill('0') << saveTimeTm.tm_hour <<
		std::setw(2) << std::setfill('0') << saveTimeTm.tm_min <<
		std::setw(2) << std::setfill('0') << saveTimeTm.tm_sec;

	std::ofstream ofs("saveData/design/" + ss.str() + saveName);
	ofs << designData;
	ofs.close();
}

std::string PROCESS_NODE_SAVE::ProcessNodeToSaveDataString(const std::vector<PROCESS_NODE*>& selectList) {
	std::string data;
	constexpr size_t oneNodeSaveStringSize = 128;
	data.reserve(selectList.size()* oneNodeSaveStringSize);
	//�ٗl�Ƀl�X�g���[�����ǁA�o�͂�������q�f�[�^�\���ƏƂ炵���킹��΂��̂ق���������₷���Ǝv���B�܂���������Ȃ��Ă������͂ǂ��ɂ������ق�������
	data += "root{";
	{
		//�e�m�[�h����������
		data += "node[";
		{
			for (auto& i : selectList) {
				data += "{" + i->saveDataString() + "}";
			}
		}
		data += "]";
		//�m�[�h���m�̐ڑ������L�^
		data += "connector[";
		{
			for (int i = 0;i < selectList.size();i++) {
				data += "{outNode[";
				//�P�m�[�h�Ɋ܂܂��A�E�g�R�l�N�^�[�̉�
				auto allNodeConnectorOut = selectList[i]->allNodeConnectorOut();
				for (int i2 = 0;i2 < allNodeConnectorOut.second;i2++) {
					data += "{";
					{
						data += "idx{";
						{
							//�|�C���^�̌����őΉ�����m�[�h�ƃR�l�N�^�[��������
							int nodeIdx = -1;
							int connectorIdx = -1;
							for (int i3 = 0;i3 < selectList.size();i3++) {
								auto allNodeConnectorIn = selectList[i3]->allNodeConnectorIn();
								for (int i4 = 0;i4 < allNodeConnectorIn.second;i4++) {
									if (allNodeConnectorOut.first[i2]->cnnectorNext() == allNodeConnectorIn.first[i4]) {
										nodeIdx = i3;
										connectorIdx = i4;
									}
								}
							}
							//���Ԗڂ̃m�[�h�����L�^
							data += "node{" + std::to_string(nodeIdx) + "}";
							//�m�[�h�̂ǂ̃R�l�N�^�[�ƌq�����Ă��邩���L�^
							data += "connector{" + std::to_string(connectorIdx) + "}";
						}
						data += "}";
						//���C���̐���_�̈ʒu���L�^
						data += "line{";
						{
							//����_�̐����L�^
							data += "num{" + std::to_string(allNodeConnectorOut.first[i2]->nodeLine()->num()) + "}";
							//�e����_�̈ʒu���L�^
							auto points = allNodeConnectorOut.first[i2]->nodeLine()->localPoints();
							data += "points[";
							for (int i3 = 0;i3 < allNodeConnectorOut.first[i2]->nodeLine()->num();i3++) {
								VECTOR2 op = points[i3];
								data += "{pos{x{" + std::to_string(op.x) + "}" +
									"y{" + std::to_string(op.y) + "}}}";
							}
							data += "]";
						}
						data += "}";
					}
					data += "}";
				}
				data += "]}";
			}
		}
		data += "]";
	}
	data += "}";
	return data;
}

std::string PROCESS_NODE_SAVE::getTypeStringName(PROCESS_NODE_TYPE type) {
	switch (type) {
	case PROCESS_NODE_TYPE::START:
		return "start";
	case PROCESS_NODE_TYPE::INPUT:
		return "input";
	case PROCESS_NODE_TYPE::OUTPUT:
		return "output";
	case PROCESS_NODE_TYPE::ASSIGNMENT:
		return "assignment";
	case PROCESS_NODE_TYPE::CALCULATION:
		return "calcuation";
	case PROCESS_NODE_TYPE::IF:
		return "if";
	case PROCESS_NODE_TYPE::WAIT:
		return "wait";
	case PROCESS_NODE_TYPE::JUMP_POINT:
		return "jump_point";
	case PROCESS_NODE_TYPE::JUMP:
		return "jump";
	case PROCESS_NODE_TYPE::JUMP_BACK:
		return "jump_back";
	case PROCESS_NODE_TYPE::FUNCTION:
		return "function";
	default:
		WARNING(true, "PROCESS_NODE_SAVE::getTypeStringName(PROCESS_NODE_TYPE)", "PROCESS_NODE_TYPE�Y���Ȃ�");
		break;
	}
	return std::string();
}

PROCESS_NODE_TYPE PROCESS_NODE_SAVE::stringNameToType(const std::string& s){
	return StringNameToTypeTable[s];
}



