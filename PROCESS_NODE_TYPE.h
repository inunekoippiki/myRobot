#pragma once
enum class PROCESS_NODE_TYPE {
	START,
	INPUT,
	OUTPUT,
	ASSIGNMENT,
	CALCULATION,
	IF,
	WAIT,
	JUMP_POINT,
	JUMP,
	JUMP_BACK,
	FUNCTION
};