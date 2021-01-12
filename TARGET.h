#pragma once
class ROUND_MISSION;
namespace COMPONENT {
	class TARGET {
	public:
		TARGET(ROUND_MISSION* roundMission);
		~TARGET();
	private:
		ROUND_MISSION* RoundMission = nullptr;
	};
}