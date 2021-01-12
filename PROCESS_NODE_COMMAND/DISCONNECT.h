#pragma once
#include "INTERFACE.h"
#include "../NODE_LINE_DATA.h"
class PROCESS_NODE_CONNECTOR_OUT;
class PROCESS_NODE_CONNECTOR_IN;
class PROCESS_NODE_LINER;
namespace PROCESS_NODE_COMMAND {
	//ノード同士の繋がりを切るコマンド
	class DISCONNECT :public BASE {
	public:
		DISCONNECT(
			PROCESS_NODE_CONNECTOR_OUT* connecterOut,
			PROCESS_NODE_LINER* processNodeLiner);
		~DISCONNECT();
		void execute()override;
		void undo()override;
	private:
		//
		PROCESS_NODE_CONNECTOR_OUT* ConnecterOut = nullptr;

		//Outにつながっていた前のIn
		PROCESS_NODE_CONNECTOR_IN* OldConnecterIn = nullptr;
		NODE_LINE_DATA NodeLineData;

		PROCESS_NODE_LINER* ProcessNodeLiner = nullptr;
	};

}