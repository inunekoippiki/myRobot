#pragma once
namespace COMPONENT {
	class GOAL{
	public:
		GOAL();
		~GOAL();
		void setIsAlreadyGoal(bool isAlreadyGoal) { IsAlreadyGoal= isAlreadyGoal; }
		bool isAlreadyGoal() const{ return IsAlreadyGoal; }
	private:
		//ÉSÅ[ÉãçœÇ›Ç©
		bool IsAlreadyGoal = false;
	};
}