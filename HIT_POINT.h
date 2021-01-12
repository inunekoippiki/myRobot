#pragma once
namespace COMPONENT {
	class HIT_POINT{
	public:
		HIT_POINT();
		~HIT_POINT();
		void setMaxHp(int maxHp) { MaxHp = maxHp; }
		//ëSâıÇ≥ÇπÇÈ
		void hpFull() { Hp = MaxHp; }
		void setHp(int hp) { Hp = hp; }
		int maxHp()const { return MaxHp; }
		int hp()const { return Hp; }
		void damage(int damage) { Hp -= damage; }
		//HPécÇËäÑçá
		float ratio()const { return Hp / (float)MaxHp; }
		bool isDead()const { return Hp <= 0; }
	private:
		int MaxHp = 0;
		int Hp = 0;
	};

}