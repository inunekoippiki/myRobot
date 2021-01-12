#pragma once
#include "UI.h"
namespace ENTITY {
	class ENTITY;
}
//ENTITY�̃T�C�Y�̕ύX�Ȃǂ��s���N���X
//�ό`���郍�{�ł͂Ȃ�
class ENTITY_TRANSFORMER{
public:
	enum class STATE {
		NONE, POSITION, SCALE
	};
	ENTITY_TRANSFORMER();
	~ENTITY_TRANSFORMER();
	void change(ENTITY::ENTITY* entity);
	void changePosition(ENTITY::ENTITY* entity);
	void changeScale(ENTITY::ENTITY * entity);
	void changeState(STATE state);
private:
	STATE State = STATE::NONE;
	float MoveSpeed = 0.0f;
	float ScalingSpeed = 0.0f;
};

