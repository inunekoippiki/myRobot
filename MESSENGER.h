#pragma once
namespace ENTITY {
	class ENTITY;
}
namespace MESSENGER {
	enum class MSG_TYPE {
		DAMAGE, KNOCK_BACK
	};
	using DATA = unsigned __int64;
	void sendMessege(ENTITY::ENTITY* handle, MSG_TYPE msgType, DATA data, ENTITY::ENTITY* caller);
}