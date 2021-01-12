#include "ROUND_MISSION.h"
#include "TARGET.h"
namespace COMPONENT {
	TARGET::TARGET(ROUND_MISSION* roundMission) :
		RoundMission(roundMission) {
	}
	TARGET::~TARGET() {
		RoundMission->destroyTarget();
	}
}