#pragma once
#include "../Library/COLOR.h"
#include "../Library/VECTOR3.h"
#include "../Library/MATRIX.h"
#include "DRAWER.h"
class SHADER;
class TREE;
using TREE_LIB = TREE;
//ロケーターと繋げて使う
namespace DRAWER {
	class TREE2 :public BASE {
	public:
		TREE2() :Scale(VECTOR3::one()) {
		};
		~TREE2() {};
		void create();
		void update();
		void draw(SHADER* shader)override;
		//セッター
		void setIsDisable(bool isDisable) { IsDisable = isDisable; }
		void setTree(TREE_LIB* tree) { Tree = tree; }
		void setPos(const VECTOR3& pos);
		void setRad(const VECTOR3& rad);
		void setScale(const VECTOR3& scale);
		void setWorld(const MATRIX& world);
		//ゲッター
		bool isDisable() { return IsDisable; }
		TREE_LIB* tree() { return Tree; }
		VECTOR3 pos() { return Pos; }
		VECTOR3 rad() { return Rad; }
		VECTOR3 scale() { return Scale; }
		MATRIX world() { return World; }

	private:
		bool IsDisable = false;
		TREE_LIB* Tree = nullptr;
		VECTOR3 Pos;
		VECTOR3 Rad;
		VECTOR3 Scale;
		MATRIX World;
	};
}