#pragma once
#include <vector>
class VECTOR3;
namespace ENTITY {
	class ENTITY;
}
//entityListから検索したり、それを加工して返したりするクラス
class ENTITY_AGGREGATE{
public:
	ENTITY_AGGREGATE();
	~ENTITY_AGGREGATE();
	//指定の位置から一番近いITEMの位置を返す
	static VECTOR3 nearestItemPos(const VECTOR3& pos, const std::vector<ENTITY::ENTITY*>& entityList);
	//指定の位置から一番近いTARGETの位置を返す
	static VECTOR3 nearestTargetPos(const VECTOR3& pos, const std::vector<ENTITY::ENTITY*>& entityList);
	//指定の位置から一番近いGOALの位置を返す
	static VECTOR3 nearestGoalPos(const VECTOR3& pos, const std::vector<ENTITY::ENTITY*>& entityList);
private:

};

