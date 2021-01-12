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
	//ロボット（プレイヤー）の位置を返す
	VECTOR3 robotPos();
	//指定の位置から一番近いアイテムの位置を返す
	VECTOR3 nearestItemPos(const VECTOR3& pos);
	//指定の位置から一番近いターゲットの位置を返す
	VECTOR3 nearestTargetPos(const VECTOR3& pos);
	//指定の位置から一番近いゴールの位置を返す
	VECTOR3 nearestGoalPos(const VECTOR3& pos);

private:
	ENTITY::ROBOT* Robot = nullptr;
	std::vector< ENTITY::ENTITY*>* EntityList = nullptr;
};

