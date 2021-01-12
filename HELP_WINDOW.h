#pragma once
#include "../Library/ARRAY.h"
#include "../Library/VECTOR2.h"
#include "DRAWER_STATIC_FONT.h"
#include "UI.h"
class CONTAINER;
class HELP_WINDOW{
public:
	HELP_WINDOW();
	~HELP_WINDOW();
	void create(CONTAINER* c, STATIC_FONT* font);
	UI* rootUi() { return RootUi; }
private:
	void onClickNextPage();
	void onClickBackPage();

	//そのページが変わった際の更新
	void updatePage();
	UI* RootUi = nullptr;
	UI* WindowBackUi = nullptr;
	UI* WindowUi = nullptr;
	UI* PageUi = nullptr;
	DRAWER::STATIC_FONT* PageUiDrawer = nullptr;
	UI* NextPageButtonUi = nullptr;
	UI* BackPageButtonUi = nullptr;

	DRAWER::IMAGE2D* Drawer = nullptr;

	std::vector<TEXTURE*> Textures;
	int NowPage = 0;
	//音
	SOUND* SoundButton = nullptr;
};

