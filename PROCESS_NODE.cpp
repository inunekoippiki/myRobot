#include "DRAWER_STATIC_FONT.h"
#include "PROCESS_NODE_CONNECTOR.h"
#include "UI_FACTORY.h"
#include "NODE_LINE.h"
#include "PROCESS_NODE.h"

PROCESS_NODE::PROCESS_NODE() {

}

UI* PROCESS_NODE::rootUi() { 
	return Frame.rootUi(); 
}

void PROCESS_NODE::lineUpdate(PROCESS_NODE* processNode){
	const auto& allIn = processNode->allNodeConnectorIn();
	for (int i = 0;i < allIn.second;i++) {
		if (auto in = allIn.first[i]->connectorFront(); in != nullptr) {
			in->updateLine();
		}
	}
	const auto& allOut = processNode->allNodeConnectorOut();
	for (int i = 0;i < allOut.second;i++) {
		allOut.first[i]->updateLine();
	}
}

void PROCESS_NODE::addLinePointUiToRootUi(PROCESS_NODE* processNode, UI* linePointRootUi){
	const auto& allOut = processNode->allNodeConnectorOut();
	for (int i = 0;i < allOut.second;i++) {
		allOut.first[i]->nodeLine()->setLinePointParent(linePointRootUi);
	}
}

void PROCESS_NODE::removeLinePointUiToRootUi(PROCESS_NODE* processNode){
	const auto& allOut = processNode->allNodeConnectorOut();
	for (int i = 0;i < allOut.second;i++) {
		allOut.first[i]->nodeLine()->setLinePointParent(nullptr);
	}
}

void PROCESS_NODE::disconnect(PROCESS_NODE* processNode){
	const auto& allIn = processNode->allNodeConnectorIn();
	for (int i = 0;i < allIn.second;i++) {
		if (auto in = allIn.first[i]->connectorFront();in != nullptr) {
			in->setConnectorNext(nullptr);
		}
	}
	const auto& allOut = processNode->allNodeConnectorOut();
	for (int i = 0;i < allOut.second;i++) {
		if (auto out = allOut.first[i]->cnnectorNext();out != nullptr) {
			out->setConnectorFront(nullptr);
		}

	}
}

UI* PROCESS_NODE::instanceNodeTypeNameUi(const char* name, STATIC_FONT* font){
	UI* ui = UI_FACTORY::instance(DRAWER::STATIC_FONT::instance(name, font, VECTOR2(), VECTOR2(24.0f, 24.0f), DRAWER::STATIC_FONT::drawMethodDefault()));
	ui->setIsCollisionDisable(true);
	return ui;
}
