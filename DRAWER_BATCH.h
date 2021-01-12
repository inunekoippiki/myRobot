#pragma once
#include "../Library/VECTOR3.h"
#include "../Library/COLOR.h"
#include "../Library/MATRIX.h"
#include "DRAWER.h"
class SHADER;
class BATCH;
using BATCH_LIB = BATCH;
namespace DRAWER {
	class BATCH :public BASE {
	public:
		BATCH():Scale(VECTOR3::one()) {};
		~BATCH() {};
		void create();
		//セッター
		void setIsDisable(bool isDisable) { IsDisable = isDisable; }
		void setBatch(BATCH_LIB* batch) { Batch = batch; }
		void setPos(const VECTOR3& pos);
		void setRad(const VECTOR3& rad);
		void setScale(const VECTOR3& scale);
		//ゲッター
		bool isDisable() { return IsDisable; }
		BATCH_LIB* batch() { return Batch; }
   		VECTOR3 pos() { return Pos; }
		VECTOR3 rad() { return Rad; }
		VECTOR3 scale() { return Scale; }
		MATRIX world() { return World; }

		void draw(SHADER* shader)override;
	private:
		bool IsDisable = false;
		BATCH_LIB* Batch = nullptr;
		VECTOR3 Pos;
		VECTOR3 Rad;
		VECTOR3 Scale;
		MATRIX World;
	};
}    