#pragma once
#include <array>
#include "UI_INPUT_BOX.h"
#include "UI_INPUT_BOX_VARIABLE.h"
#include "UI_INPUT_BOX_COMPARISON_OPERATOR.h"
#include "PROCESS_NODE_CONNECTOR.h"
#include "PROCESS_NODE.h" 
namespace DRAWER {
	class DRAWERS_SHADER;
}
class PROCESS_NODE_IF :public PROCESS_NODE {
public:
	PROCESS_NODE_IF(CONTAINER* c, STATIC_FONT* font, DRAWER::DRAWERS_SHADER* lineDrawers, PROCESS_NODE_LINER* processNodeLiner, PROCESS_NODE_MANAGER* processNodeManager);
	~PROCESS_NODE_IF();
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
	UI_INPUT_BOX_VARIABLE StringBoxInputVariable;
	UI_INPUT_BOX_COMPARISON_OPERATOR StringBoxComparisonOperator;
	UI_INPUT_BOX_VARIABLE StringBoxInputVariable2;
	PROCESS_NODE_CONNECTOR_IN NodeConnectorFront;
	PROCESS_NODE_CONNECTOR_OUT NodeConnectorBack;
	PROCESS_NODE_CONNECTOR_OUT NodeConnectorBackElse;
	PROCESS_NODE_CONNECTOR_IN* NodeConnectorFront_ = nullptr;
	std::array<PROCESS_NODE_CONNECTOR_OUT*, 2> NodeConnectorBack_;
	PROCESS_NODE_MANAGER* ProcessNodeManager = nullptr;
};

