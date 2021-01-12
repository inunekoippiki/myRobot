#pragma once
#include "NODE_LINE_DATA.h"
class PROCESS_NODE;
class PROCESS_NODE_LINE_DATA{
public:
	PROCESS_NODE_LINE_DATA(PROCESS_NODE* processNode);
	~PROCESS_NODE_LINE_DATA();

private:
	NODE_LINE_DATA Front;

};

