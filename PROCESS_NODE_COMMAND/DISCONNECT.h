#pragma once
#include "INTERFACE.h"
#include "../NODE_LINE_DATA.h"
class PROCESS_NODE_CONNECTOR_OUT;
class PROCESS_NODE_CONNECTOR_IN;
class PROCESS_NODE_LINER;
namespace PROCESS_NODE_COMMAND {
	//�m�[�h���m�̌q�����؂�R�}���h
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

		//Out�ɂȂ����Ă����O��In
		PROCESS_NODE_CONNECTOR_IN* OldConnecterIn = nullptr;
		NODE_LINE_DATA NodeLineData;

		PROCESS_NODE_LINER* ProcessNodeLiner = nullptr;
	};

}