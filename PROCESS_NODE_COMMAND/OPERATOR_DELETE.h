#pragma once
#include <vector>
#include "INTERFACE.h"
#include "../PROCESS_NODE_CONNECTOR.h"
class PROCESS_NODE;
class PROCESS_NODE_SELECTOR;
class PROCESS_NODE_MANAGER;
class PROCESS_NODE_LINER;
class PROCESS_NODE_WINDOW;
namespace PROCESS_NODE_COMMAND {
	//選択されたノードを削除するコマンド
	class OPERATOR_DELETE :public BASE {
	public:
		class CONNECTOR_DATA{
		public:
			CONNECTOR_DATA(const CONNECTOR_DATA&) = delete;
			CONNECTOR_DATA(CONNECTOR_DATA&&)noexcept;
			CONNECTOR_DATA(PROCESS_NODE* processNode);
			~CONNECTOR_DATA();
			void reConnect(PROCESS_NODE* processNode);
		private:
			std::pair<PROCESS_NODE_CONNECTOR_IN**, int> InData ;
			std::pair<PROCESS_NODE_CONNECTOR_OUT**, int> OutData;
		};
		OPERATOR_DELETE(
			PROCESS_NODE_SELECTOR* processNodeSelector,
			PROCESS_NODE_MANAGER* processNodeManager);
		~OPERATOR_DELETE();
		void execute()override;
		void undo()override;


	private:
		PROCESS_NODE_SELECTOR* ProcessNodeSelector = nullptr;
		PROCESS_NODE_MANAGER* ProcessNodeManager = nullptr;
		std::vector<PROCESS_NODE*> DeleteList;
		std::vector<CONNECTOR_DATA> ConnectList;
	};

}