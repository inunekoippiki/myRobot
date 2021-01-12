#pragma once
#include "UI.h"
#include <vector>
class TEXTURE;
class VECTOR2;
class UI_FACTORY {
public:
	template<class T>
	static UI* instance(T* drawer) {
		UI* ui = new UI;
		ui->create(drawer);
		return ui;
	}
	static UI* instance(TEXTURE* texture, const VECTOR2& pos, const VECTOR2& scale);
	static UI* instance(TEXTURE* texture, const VECTOR2& pos, const VECTOR2& scale, const COLOR& color);
	//空のUIをインスタンスして返す
	static UI* instanceEmpty();
};


