#pragma once 
#include <vector>
class VECTOR3;
namespace ENTITY {
	class ROBOT;
	class ENTITY;
}
class ENTITY_MEDIATOR{
public:
	ENTITY_MEDIATOR(std::vector< ENTITY::ENTITY*>* entityList);
	~ENTITY_MEDIATOR();
	void setRobot(ENTITY::ROBOT* robot) { Robot = robot; }
	//���{�b�g�i�v���C���[�j�̈ʒu��Ԃ�
	VECTOR3 robotPos();
	//�w��̈ʒu�����ԋ߂��A�C�e���̈ʒu��Ԃ�
	VECTOR3 nearestItemPos(const VECTOR3& pos);
	//�w��̈ʒu�����ԋ߂��^�[�Q�b�g�̈ʒu��Ԃ�
	VECTOR3 nearestTargetPos(const VECTOR3& pos);
	//�w��̈ʒu�����ԋ߂��S�[���̈ʒu��Ԃ�
	VECTOR3 nearestGoalPos(const VECTOR3& pos);

private:
	ENTITY::ROBOT* Robot = nullptr;
	std::vector< ENTITY::ENTITY*>* EntityList = nullptr;
};

