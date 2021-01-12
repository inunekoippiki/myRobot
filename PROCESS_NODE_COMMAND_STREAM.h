#pragma once
namespace PROCESS_NODE_COMMAND {
	class BASE;
}
//ä¬èÛÇ…Ç»Ç¡ÇƒÇ¢Çƒè„å¿Çí¥Ç¶ÇÈÇ∆å√Ç¢ÇÃÇ‡Ç©ÇÁè„èëÇ´Ç≥ÇÍÇƒÇ¢Ç≠
class PROCESS_NODE_COMMAND_STREAM {
public:
	using COMMAND = PROCESS_NODE_COMMAND::BASE;
	PROCESS_NODE_COMMAND_STREAM();
	~PROCESS_NODE_COMMAND_STREAM();
	void push(COMMAND* command);
	void redo();
	void undo();
private:
	COMMAND** nextPtr(COMMAND** ptr) {
		if (ptr == nullptr) {
			return CommandQue;
		}
		ptr++;
		if (ptr == CommandQue + Size)ptr = CommandQue;
		return ptr;
	}
	COMMAND** backPtr(COMMAND** ptr) {
		ptr--;
		if (ptr == CommandQue - 1)ptr += Size;
		return ptr;
	}
	COMMAND** CommandQue = nullptr;
	int Size = 0;
	COMMAND** Current = 0;
	COMMAND** Begin = nullptr;
	COMMAND** End = nullptr;
};

