#pragma once
#include "UI_INPUT_BOX.h"
#include "PROCESS_NODE_CONNECTOR.h"
#include "PROCESS_NODE.h"
namespace DRAWER {
	class DRAWERS_SHADER;
}
class PROCESS_NODE_START :public PROCESS_NODE {
public:
	PROCESS_NODE_START(CONTAINER* c, STATIC_FONT* font, DRAWER::DRAWERS_SHADER* lineDrawers, PROCESS_NODE_LINER* processNodeLiner, PROCESS_NODE_MANAGER* processNodeManager);
	~PROCESS_NODE_START();
	std::pair<PROCESS_NODE_CONNECTOR_IN**, int> allNodeConnectorIn();
	std::pair<PROCESS_NODE_CONNECTOR_OUT**, int> allNodeConnectorOut();
	std::string saveDataString();
	void loadFromSaveString(const STRING_TREE& data);
	void compile(ROBOT_COMPILER* robotCompiler);
	void nextStep(ROBOT_PROCESSOR* robotProcessor);
	void setEnable()override;
	void setDisable()override;
private:
	UI* NodeTypeNameUi = nullptr;
	PROCESS_NODE_CONNECTOR_OUT NodeConnectorBack;
	PROCESS_NODE_CONNECTOR_OUT* NodeConnectorBack_ = nullptr;
	PROCESS_NODE_MANAGER* ProcessNodeManager = nullptr;
};

