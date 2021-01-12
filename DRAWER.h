#pragma once
class SHADER;
class TEXTURE;
class VECTOR2;
class VECTOR3;
class MATRIX;
/*
DRAWERのシステムは描画が必要なオブジェクトで生成し、
イテレーションのための別のマネージャークラスに委譲する。
マネージャークラスでまとめて描画し、位置などの更新は
登録元のオブジェクトで行う。
登録元のオブジェクトがdeleteされるときDRAWERもデリートしないといけないが
マネージャークラスに通知が必要なためDelete()で間接でデリートする。
*/

namespace DRAWER {
	class BASE {
	public:
		BASE() {};
		virtual ~BASE() {};
		virtual void draw(SHADER* shader) = 0;
		bool isDelete()const { return IsDelete; }
		void Delete() { IsDelete = true; }
	private:
		bool IsDelete = false;
	};


	//継承できないときはこれを使う
	//入れれる条件はvoid draw(SHADER* shader)を持っていること
	template <class T>
	class SAUCER :public BASE {
	public:
		using type = T;
		SAUCER(T* obj) { Obj = obj; }
		~SAUCER() {};
		void draw(SHADER* shader) override {
			Obj->draw(shader);
		};
	private:
		T* Obj = nullptr;
	};
}