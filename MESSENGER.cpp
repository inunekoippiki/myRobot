#include "ENTITY.h"
#include "MESSENGER.h"
namespace MESSENGER{
	void sendMessege(ENTITY::ENTITY* handle, MSG_TYPE msgType, DATA data,ENTITY::ENTITY* caller) {
		handle->receiveMessage(msgType, data, caller);
	}
}