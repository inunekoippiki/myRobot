#include "../Library/common.h"
#include "COLLISION_LIST.h"

namespace COMPONENT {
	COLLISION_LIST::~COLLISION_LIST() {
		for (auto& i : List) {
			SAFE_DELETE(i);
		}
	}
	void COLLISION_LIST::erase(size_t idx){
		SAFE_DELETE(List[idx]);
		List[idx] = List.back();
		List.pop_back();
	}
	size_t COLLISION_LIST::size() {
		return List.size();
	}
}