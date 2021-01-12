#pragma once
namespace PROCESS_NODE_COMMAND {
	class BASE {
	public:
		virtual ~BASE() {};
		virtual void execute() = 0;
		virtual void undo() = 0;
	};
}
