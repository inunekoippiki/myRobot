#include "../Library/common.h"
#include "../Library/Thread/THREAD.h"
#include "../Library/CONTAINER.h"
#include "../Library/GRAPHIC.h"
#include "../Library/IMAGE_2D.h"
#include "LOAD_DISP.h"
LOAD_DISP::LOAD_DISP(CONTAINER* container) {
	ContainerLoadThread.push_back(new CONTAINER_LOAD_THREAD(container));
	G = GRAPHIC::instance();
	Shader = new IMAGE_2D();
	Texture.create("Assets/images/Menu/Icon/loading.png");
	Color = COLOR(1.0f, 1.0f, 1.0f, 0.0f);
	Pos = VECTOR2(G->baseWidth() * 0.5f, G->baseHeight() * 0.5f);
	AnimSpeed = 0.04f;
}

LOAD_DISP::~LOAD_DISP() {
	SAFE_DELETE(Shader);
	for (auto& i : ContainerLoadThread) {
		SAFE_DELETE(i);
	}
}

void LOAD_DISP::addLoadContainer(CONTAINER* container){
	ContainerLoadThread.push_back(new CONTAINER_LOAD_THREAD(container));
}

void LOAD_DISP::startProc() {
	while (!LoopFlag) {
		//Update-------------------------------------------------------------------------
		switch (Sw) {
		case 0://フェードイン
			Color.a += 0.025f;
			if (Color.a >= 1.0f) {
				Color.a = 1.0f;
				Sw = 1;
			}
			break;
		case 1://ロード終了待ち
		{
			bool isAllFinish = true;
			for (auto& i : ContainerLoadThread) {
				if (!i->isFinished()) {
					isAllFinish = false;
				}
			}
			TempAnimPlay += AnimSpeed;
			Color.a = abs(cosf(TempAnimPlay));
			if (isAllFinish) {
				Sw = 2;
			}
			break;
		}
		case 2://フェードアウト後、このループを抜ける
			Color.a -= 0.025f;
			if (Color.a <= 0.0f) {
				Color.a = 0.0f;
				LoopFlag = true;
			}
			break;
		}

		//Draw---------------------------------------------------------------------------
		SHADER* shader = Shader;
		BEGIN_PATH_
			G->clearTarget();
		Texture.draw(Shader, Pos, 0.0, Color);
		END_PATH_
			G->present();
	}
}
