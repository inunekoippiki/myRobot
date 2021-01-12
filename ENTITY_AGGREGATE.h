#pragma once
#include <vector>
class VECTOR3;
namespace ENTITY {
	class ENTITY;
}
//entityList���猟��������A��������H���ĕԂ����肷��N���X
class ENTITY_AGGREGATE{
public:
	ENTITY_AGGREGATE();
	~ENTITY_AGGREGATE();
	//�w��̈ʒu�����ԋ߂�ITEM�̈ʒu��Ԃ�
	static VECTOR3 nearestItemPos(const VECTOR3& pos, const std::vector<ENTITY::ENTITY*>& entityList);
	//�w��̈ʒu�����ԋ߂�TARGET�̈ʒu��Ԃ�
	static VECTOR3 nearestTargetPos(const VECTOR3& pos, const std::vector<ENTITY::ENTITY*>& entityList);
	//�w��̈ʒu�����ԋ߂�GOAL�̈ʒu��Ԃ�
	static VECTOR3 nearestGoalPos(const VECTOR3& pos, const std::vector<ENTITY::ENTITY*>& entityList);
private:

};

