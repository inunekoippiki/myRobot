#pragma once
namespace COMPONENT {
	class HIT_POINT{
	public:
		HIT_POINT();
		~HIT_POINT();
		void setMaxHp(int maxHp) { MaxHp = maxHp; }
		//全快させる
		void hpFull() { Hp = MaxHp; }
		void setHp(int hp) { Hp = hp; }
		int maxHp()const { return MaxHp; }
		int hp()const { return Hp; }
		void damage(int damage) { Hp -= damage; }
		//HP残り割合
		float ratio()const { return Hp / (float)MaxHp; }
		bool isDead()const { return Hp <= 0; }
	private:
		int MaxHp = 0;
		int Hp = 0;
	};

}