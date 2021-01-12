#include "../PROCESS_NODE.h"
#include "../PROCESS_NODE_MANAGER.h"
#include "../PROCESS_NODE_LINER.h"
#include "../PROCESS_NODE_WINDOW.h"
#include "OPERATOR_DELETE.h"
namespace PROCESS_NODE_COMMAND {
	OPERATOR_DELETE::OPERATOR_DELETE(
		PROCESS_NODE_SELECTOR* processNodeSelector,
		PROCESS_NODE_MANAGER* processNodeManager) :
		ProcessNodeSelector(processNodeSelector),
		ProcessNodeManager(processNodeManager)	{
	}

	OPERATOR_DELETE::~OPERATOR_DELETE(){
		for (auto& i : DeleteList) {
			SAFE_DELETE(i);
		}
	}
	void OPERATOR_DELETE::execute(){
		auto& selectList = *ProcessNodeSelector->selectList();
		ConnectList.reserve(selectList.size());
		for (auto& eraseNode : selectList) {
			ConnectList.emplace_back(CONNECTOR_DATA(eraseNode));
		}
		for (auto &eraseNode : selectList) {
			ProcessNodeManager->removeProcessNode(eraseNode);
		}
		std::swap(DeleteList, selectList);
		ProcessNodeSelector->selectUpdate();
	}
	void OPERATOR_DELETE::undo(){
		for (int i = 0;i < DeleteList.size();i++) {
			ProcessNodeManager->addProcessNode(DeleteList[i]);
			ConnectList[i].reConnect(DeleteList[i]);
		}
		ProcessNodeSelector->select(DeleteList);
		DeleteList.clear();
		ConnectList.clear();
	}	
	/////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////

	OPERATOR_DELETE::CONNECTOR_DATA::CONNECTOR_DATA(CONNECTOR_DATA&& rhs)noexcept :
		InData(rhs.InData),
		OutData(rhs.OutData) {
		rhs.InData = { nullptr ,0 };
		rhs.OutData = { nullptr ,0 };
	}
	OPERATOR_DELETE::CONNECTOR_DATA::CONNECTOR_DATA(PROCESS_NODE* processNode)	{
		const auto& inData = processNode->allNodeConnectorIn();
		OutData.first = nullptr;
		if (inData.second > 0) {
			OutData.first = new PROCESS_NODE_CONNECTOR_OUT * [inData.second];
			OutData.second = inData.second;
		}
		for (int i = 0;i < inData.second;i++) {
			OutData.first[i] = inData.first[i]->connectorFront();
		}
		const auto& outData = processNode->allNodeConnectorOut();
		InData.first = nullptr;
		if (outData.second > 0) {
			InData.first = new PROCESS_NODE_CONNECTOR_IN * [outData.second];
			InData.second = outData.second;
		}
		for (int i = 0;i < outData.second;i++) {
			InData.first[i] = outData.first[i]->cnnectorNext();
		}
	}
	OPERATOR_DELETE::CONNECTOR_DATA::~CONNECTOR_DATA(){
		SAFE_DELETE_ARRAY(InData.first);
		SAFE_DELETE_ARRAY(OutData.first);
	}
	void OPERATOR_DELETE::CONNECTOR_DATA::reConnect(PROCESS_NODE* processNode){
		const auto& inData = processNode->allNodeConnectorIn();
		for (int i = 0;i < inData.second;i++) {
			inData.first[i]->setConnectorFront(OutData.first[i]);
			if (OutData.first[i] != nullptr) {
				OutData.first[i]->setConnectorNext(inData.first[i]);
			}
		}
		const auto& outData = processNode->allNodeConnectorOut();
		for (int i = 0;i < outData.second;i++) {
			outData.first[i]->setConnectorNext(InData.first[i]);
			if (InData.first[i] != nullptr) {
				InData.first[i]->setConnectorFront(outData.first[i]);
			}
		}
	}
}