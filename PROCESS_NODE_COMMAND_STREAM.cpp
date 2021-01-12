#include "../Library/common.h"
#include "PROCESS_NODE_COMMAND/INTERFACE.h"
#include "PROCESS_NODE_COMMAND_STREAM.h"
PROCESS_NODE_COMMAND_STREAM::PROCESS_NODE_COMMAND_STREAM() {
	Size = 16;
	CommandQue = new COMMAND * [Size];
	memset(CommandQue, 0, sizeof(*CommandQue) * Size);
	Current = nullptr;
	Begin = nullptr;
	End = CommandQue;

}

PROCESS_NODE_COMMAND_STREAM::~PROCESS_NODE_COMMAND_STREAM() {
	for (int i = 0;i < Size;i++) {
		SAFE_DELETE(CommandQue[i]);
	}
	SAFE_DELETE_ARRAY(CommandQue);
}

void PROCESS_NODE_COMMAND_STREAM::push(COMMAND* command) {
	if (Begin == nullptr) {
		Begin = CommandQue;
		Current = CommandQue;
		*End = command;
		End = nextPtr(End);
	}
	else
	{
		Current = nextPtr(Current);
		COMMAND** CurrentTemp = Current;
		while (CurrentTemp != End) {
			SAFE_DELETE(* CurrentTemp);
			CurrentTemp = nextPtr(CurrentTemp);
		}
		End = Current;
		SAFE_DELETE(*End);
		*End = command;
		if (Begin == End) {
			if (*nextPtr(Begin) != nullptr) {
				Begin = nextPtr(Begin);
			}
		}
		End = nextPtr(End);
	}
}

void PROCESS_NODE_COMMAND_STREAM::redo() {
	if (Current != nullptr) {
		if (End != nextPtr(Current)) {
			Current = nextPtr(Current);
			(*Current)->execute();
		}
	}
	else {
		if (Begin != nullptr) {
			Current = Begin;
			(*Current)->execute();
		}
	}
}

void PROCESS_NODE_COMMAND_STREAM::undo() {
	if (Current != nullptr) {
		if (Begin != Current) {
			if ((*Current) != nullptr) {//苦肉のNULLチェック。恐らくここじゃないとこに原因がある
				(*Current)->undo();
			}
			Current = backPtr(Current);
		}
		else {
			(*Current)->undo();
			Current = nullptr;
		}
	}
}
