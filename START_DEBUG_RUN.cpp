#pragma warning (disable:4996)
#include <string>
#include <Windows.h>
#include <future>
#include <thread>
#include <assert.h>
#include <imm.h>
#include <random>
#include "Effekseer.h"
#include "../Library/collisionUtil.h"
#include "../Library/common.h"
#include "../Library/WINDOW.h"
#include "../Library/GRAPHIC.h"
#include "../Library/INDEV.h"
#include "../Library/DEBUG_STR.h"
#include "../Library/SHADER.h"
#include "../Library/CONTAINER.h"
#include "../Library/IMAGE_2D.h"
#include "../Library/SOFT_SHADOW.h"
#include "../Library/TOON.h"
#include "../Library/LAMBERT.h"
#include "../Library/BATCH.h"
#include "../Library/TREE.h"
#include "../Library/IMAGE2D_CAMERA.h"
#include "../Library/STATIC_FONT.h"
#include "../Library/FONT_CREATE_SET.h"
#include "../Library/STRING_TREE.h"
#include "EFFEKSEER.h"
#include "DRAWER_TREE.h"
#include "DRAWER_FONT.h"
#include "DRAWER_TREE.h"
#include "DRAWER_IMAGE2D.h"
#include "DRAWERS.h"
#include "DRAWER_BATCH.h"
#include "DRAWER_ARROW.h"
#include "UI_MANAGER.h"
#include "CAMERA_DEBUG.h"
#include "NODE_LINE.h"
#include "UI.h"
#include "UI_SCROLL.h"
#include "PROCESS_NODE_MANAGER.h"
#include "PROCESS_NODE.h"
#include "UI_KEYBOARD.h"
#include "COLLISION2D_RECT.h"
#include "COLLISION2D_CIRCLE.h"
#include "COLLISION2D_POINT.h"
#include "COLLISION3D_AABB.h"
#include "COLLISION3D_CYLINDER_YAA.h"
#include "COLLISION3D_TERRAIN.h"
#include "INPUT_COMMON.h"
#include "COLLISION_MANAGER.h"
#include "START_DEBUG_RUN.h"

//フラグ
#if 0

void DebugRun(){
	BIT_FLAG::F8 flag;
	flag.setF1(true);
	flag.setF2(false);
	flag.setF3(true);
	flag.setF4(true);
	flag.setF1(false);
	flag.setF7(true);
	flag.setF7(true);

	bool b1 = flag.f1();
	bool b2 = flag.f2();
	bool b3 = flag.f3();
	bool b4 = flag.f4();
	bool b5 = flag.f5();
	bool b6 = flag.f6();
	bool b7 = flag.f7();
	bool b8 = flag.f8();
	flag.init();
	b1 = flag.f1();
	b2 = flag.f2();
	b3 = flag.f3();
	b4 = flag.f4();
	b5 = flag.f5();
	b6 = flag.f6();
	b7 = flag.f7();
	b8 = flag.f8();
	return;
}

#endif // 0
#if(0)
HWND create(HINSTANCE hInstance, int nShowCmd) {
	WINDOW* w = WINDOW::instance();
	TCHAR szAppName[] = TEXT("TestApp");
	HWND hwnd;
	HWND hEdit;

	WNDCLASS wc;
	// ウィンドウクラスの属性を設定
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = DefWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;

	// ウィンドウクラスを登録
	if (!RegisterClass(&wc)) return 0;



	//登録したｓｚClassNameより親となるオーバーラップウインドウの作成
	// ウィンドウを作成
	hwnd = CreateWindow(
		szAppName, TEXT("Title"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL,
		hInstance, NULL);

	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	//親ウインドウの上にエディットボックスを作成
	hEdit = CreateWindow(szAppName, "EDIT", WS_OVERLAPPEDWINDOW,
		100, 100, 100, 100, NULL, (HMENU)100, GetModuleHandle(0), NULL);
	ShowWindow(hEdit, nShowCmd);
	UpdateWindow(hEdit);
	return hEdit;
}

void DebugRun() {
	WINDOW* w = WINDOW::instance();
	CHAR lp[256]={0};
	INDEV* indev = INDEV::instance();

	DEBUG_STR* ds = DEBUG_STR::instance();
	CONTAINER* c = new CONTAINER("MenuIcon.txt");
	IMAGE_2D* Image2dShader = new IMAGE_2D();
	DRAWER::MANAGER* drawerManager = new DRAWER::MANAGER();
	DRAWER::DRAWERS* drawers = new DRAWER::DRAWERS();
	drawers->setShader(Image2dShader);
	std::array<DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT, 1> layout = {
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("ui", drawers)
	};
	DRAWER::DRAWERS_LIST* drawersList = new DRAWER::DRAWERS_LIST();
	drawersList->create(layout);
	drawerManager->create(drawersList);
	//{
	//	DRAWER::IMAGE2D* image = new DRAWER::IMAGE2D;
	//	image->setPivot(DRAWER::IMAGE2D::drawMethodLeft());
	//	image->setTexture(c->texture("backBox"));
	//	drawerManager->drawerAdd("ui", image);
	//}
	//{
	//	DRAWER::IMAGE2D* image = new DRAWER::IMAGE2D;
	//	image->setPivot(DRAWER::IMAGE2D::drawMethodCentered());
	//	image->setTexture(c->texture("backBox"));
	//	drawerManager->drawerAdd("ui", image);
	//}
	{
		DRAWER::FONT* image = new DRAWER::FONT;
		image->create("Assets/font/PixelMplus12-Regular.ttf", "PixelMplus12", "asdfghjkl;", 30);
		image->setPos(VECTOR2(100, 100));
		drawerManager->drawerAdd("ui", image);
	}
	{
		struct DebugDrawer {
			void draw(SHADER* shader) {

			};
			DEBUG_STR* Ds = nullptr;
		};
	DebugDrawer* debugDrawer = new DebugDrawer;
	debugDrawer->Ds = ds;
	auto image = new DRAWER::SAUCER(debugDrawer);
	drawerManager->drawerAdd("ui", image);
	}
	std::string str = lp;
	GRAPHIC* g = GRAPHIC::instance();
	HWND hwnd = NULL;
	while (w->msgProc()) {
		if (w->active()) {
			static bool isOpenEdit = false;
			indev->getState();
			if (isOpenEdit) {
				// ウィンドウを再描画
				UpdateWindow(hwnd);
				if (indev->isTrigger(KEY_ENTER)) {
					GetWindowText(hwnd, lp, 256);
					//DestroyWindow(hwnd);
					isOpenEdit = false;
				}
			}
			else{
				if (indev->isTrigger(KEY_E)) {
					hwnd = create(Global_hInstance,Global_nShow);
					isOpenEdit = true;
				}
			}
			g->clearTarget(COLOR(0.4f, 0.4f, 0.4f, 1.0f));
			ds->set("%s", str.c_str());

			drawerManager->draw();

			//c->texture("backBox")->draw(Image2dShader,VECTOR2(1.0f,1.0f));
			g->present();
		}
	}
	delete Image2dShader;
	delete c;
	delete drawerManager;
}
#endif;
//ごりおしcmd入力
#if(0)
void DebugRun() {
	HANDLE hPipe = INVALID_HANDLE_VALUE;
	hPipe = CreateNamedPipe("\\\\.\\pipe\\cmdInputPipe", //lpName
		PIPE_ACCESS_INBOUND,            // dwOpenMode
		PIPE_TYPE_BYTE | PIPE_WAIT,     // dwPipeMode
		1,                              // nMaxInstances
		0,                              // nOutBufferSize
		0,                              // nInBufferSize
		100,                            // nDefaultTimeOut
		NULL);                          // lpSecurityAttributes

	if (hPipe == INVALID_HANDLE_VALUE) {
		return;
	}
	DWORD dwBytesRead;
	char szBuff[256];
	auto connectFunc = [&]()->void {if (!ConnectNamedPipe(hPipe, NULL)) {
		fprintf(stderr, "Couldn't connect to NamedPipe.");
		CloseHandle(hPipe);
		WARNING(true, "だめです", "");
		return;
	}
	if (!ReadFile(hPipe, szBuff, sizeof(szBuff), &dwBytesRead, NULL)) {
		fprintf(stderr, "Couldn't read NamedPipe.");
		return;
	}
	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);
	};

	std::thread t(connectFunc);
	t.detach();
	std::system("cmdInput.exe");




	WINDOW* w = WINDOW::instance();
	INDEV* indev = INDEV::instance();

	DEBUG_STR* ds = DEBUG_STR::instance();
	CONTAINER* c = new CONTAINER("MenuIcon.txt");
	IMAGE_2D* Image2dShader = new IMAGE_2D();
	DRAWER::MANAGER* drawerManager = new DRAWER::MANAGER();
	DRAWER::DRAWERS* drawers = new DRAWER::DRAWERS();
	drawers->setShader(Image2dShader);
	std::array<DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT, 1> layout = {
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("ui", drawers)
	};
	DRAWER::DRAWERS_LIST* drawersList = new DRAWER::DRAWERS_LIST();
	drawersList->create(layout);
	drawerManager->create(drawersList);
	std::string str = szBuff;
	{
		DRAWER::FONT* image = new DRAWER::FONT;
		image->create("Assets/font/PixelMplus12-Regular.ttf", "PixelMplus12", str.c_str(), 30);
		image->setPos(VECTOR2(100, 100));
		drawerManager->drawerAdd("ui", image);
	}
	GRAPHIC* g = GRAPHIC::instance();
	HWND hwnd = NULL;
	while (w->msgProc()) {
		if (w->active()) {
			static bool isOpenEdit = false;
			indev->getState();
			g->clearTarget(COLOR(0.4f, 0.4f, 0.4f, 1.0f));
			drawerManager->draw();
			g->present();
		}
	}
	delete Image2dShader;
	delete c;
	delete drawerManager;
}
#endif
//動的矩形の衝突応答
#if(0)
bool CalcMoveRectAndMoveRectIsHit(
	const VECTOR2& pos1,
	const VECTOR2& velo1,
	const VECTOR2& wh1,
	const VECTOR2& pos2,
	const VECTOR2& velo2,
	const VECTOR2& wh2,
	VECTOR2& out_norm,
	VECTOR2& out_collisionPoint,
	float& out_t) {
	float vx = velo2.x - velo1.x;
	float maxtx;
	float mintx;
	if (vx > 0.0f) {
		maxtx = (pos1.x - pos2.x + wh1.x) / (vx);
		mintx = (pos1.x - pos2.x - wh2.x) / (vx);
	}
	else {
		mintx = (pos1.x - pos2.x + wh1.x) / (vx);
		maxtx = (pos1.x - pos2.x - wh2.x) / (vx);
	}
	float vy = velo2.y - velo1.y;
	float maxty;
	float minty;
	if (vy > 0.0f) {
		maxty = (pos1.y - pos2.y + wh1.y) / (vy);
		minty = (pos1.y - pos2.y - wh2.y) / (vy);
	}
	else {
		minty = (pos1.y - pos2.y + wh1.y) / (vy);
		maxty = (pos1.y - pos2.y - wh2.y) / (vy);
	}
	float min;
	float max;
	if (mintx > minty) {
		min = mintx;
		if (vx > 0.0f) {
			out_norm.x = 1.0f;
		}
		else {
			out_norm.x = -1.0f;
		}
	}
	else {
		min = minty;
		if (vy > 0.0f) {
			out_norm.y = 1.0f;
		}
		else {
			out_norm.y = -1.0f;
		}
	}
	if (maxtx < maxty) {
		max = maxtx;
	}
	else {
		max = maxty;
	}
	out_t = min;
	if (min < max) {
		if (min < 1.0f&&max > 0.0f) {
			if (min < 0.0f) {
				out_t = 0.0f;
				if (max < 1.0f) {
					out_t = max;
					return true;
				}
				else{
					return false;
				}
			}
			out_t = min;
			out_collisionPoint = pos1 + wh1 * 0.5f;
			out_collisionPoint = out_collisionPoint + (( pos2+ wh2 * 0.5f)- out_collisionPoint) * 0.5f;
			return true;
		}
	}
	return false;
};

void DebugRun() {
	

	class BOX{
	public:
		BOX(DRAWER::MANAGER* manager,TEXTURE* texture,const VECTOR2& pos,const VECTOR2& velo):
			Pos(pos),Velo(velo) {
			Image = new DRAWER::IMAGE2D();
			Image->setTexture(texture);
			Image->setPivot(DRAWER::IMAGE2D::drawMethodLeft());
			Image->setPos(pos);
			manager->drawerAdd("ui", Image);
			Wh.x = texture->width();
			Wh.y = texture->height();
		};
		~BOX() { Image->Delete(); };
		void update() {
			Velo.y += 0.1f;
			Pos += Velo;
			Image->setPos(Pos);
		}
		void setPos(const VECTOR2& pos) { Pos = pos; }
		void setVelo(const VECTOR2& velo) { Velo = velo; }
		VECTOR2 pos() { return Pos; }
		VECTOR2 velo() { return Velo; }
		VECTOR2 wh() { return Wh; }

	private:
		DRAWER::IMAGE2D* Image = nullptr;
		VECTOR2 Pos;
		VECTOR2 Velo;
		VECTOR2 Wh;
	};
	WINDOW* w = WINDOW::instance();
	INDEV* indev = INDEV::instance();

	DEBUG_STR* ds = DEBUG_STR::instance();
	CONTAINER* c = new CONTAINER("MenuIcon.txt");
	IMAGE_2D* Image2dShader = new IMAGE_2D();
	DRAWER::MANAGER* drawerManager = new DRAWER::MANAGER();
	DRAWER::DRAWERS* drawers = new DRAWER::DRAWERS();
	drawers->setShader(Image2dShader);
	std::array<DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT, 1> layout = {
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("ui", drawers)
	};
	DRAWER::DRAWERS_LIST* drawersList = new DRAWER::DRAWERS_LIST();
	drawersList->create(layout);
	drawerManager->create(drawersList);
	//{
	//	DRAWER::IMAGE2D* image = new DRAWER::IMAGE2D;
	//	image->setPivot(DRAWER::IMAGE2D::drawMethodLeft());
	//	image->setTexture(c->texture("backBox"));
	//	drawerManager->drawerAdd("ui", image);
	//}
	vector<BOX*> Boxs;
	Boxs.push_back(new BOX(drawerManager, c->texture("plusIcon"), VECTOR2(100.0f, 100.0f), VECTOR2(1.0f, 0.0f)));
	Boxs.push_back(new BOX(drawerManager, c->texture("lvlupIcon"), VECTOR2(500.0f, 200.0f), VECTOR2(-6.0f, -0.2f)));
	Boxs.push_back(new BOX(drawerManager, c->texture("plusIcon"), VECTOR2(700.0f, 300.0f), VECTOR2(1.0f, 4.0f)));
	Boxs.push_back(new BOX(drawerManager, c->texture("skillGauge"), VECTOR2(1500.0f, 700.0f), VECTOR2(-12.0f, -6.6f)));
	Boxs.push_back(new BOX(drawerManager, c->texture("oneDot"), VECTOR2(1000.0f, 600.0f), VECTOR2(20.0f, 10.0f)));
	Boxs.push_back(new BOX(drawerManager, c->texture("plusIcon"), VECTOR2(200.0f, 500.0f), VECTOR2(-40.0f, -9.2f)));

	{
		struct DebugDrawer {
			void draw(SHADER* shader) {
				Ds->draw(shader);
			};
			DEBUG_STR* Ds = nullptr;
		};
		DebugDrawer* debugDrawer = new DebugDrawer;
		debugDrawer->Ds = ds;
		auto image = new DRAWER::SAUCER(debugDrawer);
		drawerManager->drawerAdd("ui", image);
	}
	std::string str;
	GRAPHIC* g = GRAPHIC::instance();
	float t = 0.0f;
	VECTOR2 collisionPoint;
	while (w->msgProc()) {
		if (w->active()) {
			indev->getState();
			for (auto& i : Boxs) {
				i->update();
				if (i->pos().x < 0.0f || i->pos().x>1920.0f) {
					i->setPos(i->pos() - i->velo());
					i->setVelo(VECTOR2(i->velo().x * -1.0f, i->velo().y));
				}
				if ( i->pos().y>980.0f - 134.0f) {
					i->setPos(VECTOR2(i->pos().x, 980.0f-134.0f));
					i->setVelo(VECTOR2(i->velo().x, i->velo().y * -1.0f));
				}
			}
			for (auto& boxA : Boxs) {
				for (auto& boxB : Boxs) {
					if (boxB != boxA) {
						VECTOR2 norm;
						if (CalcMoveRectAndMoveRectIsHit(boxA->pos(), boxA->velo(), boxA->wh(), boxB->pos(), boxB->velo(), boxB->wh(),  norm, collisionPoint, t)) {
							DRAWER::IMAGE2D* image = new DRAWER::IMAGE2D;
							image->setTexture(c->texture("lvlupIcon"));
							image->setPos(collisionPoint);
							image->setScale(VECTOR2(0.1f, 0.1f));
							drawerManager->drawerAdd("ui", image);
							boxA->setPos(boxA->pos() - (boxA->velo() * (1.0f - t) * 0.5f));
							boxB->setPos(boxB->pos() - (boxB->velo() * (1.0f - t) * 0.5f));
							float rx = 1.0f * (abs(norm.x) > 0.0f) ? -1.0f : 1.0f;
							float ry = 1.0f * (abs(norm.y) > 0.0f) ? -1.0f : 1.0f;
							float l = length(boxA->velo() + boxB->velo()) * 0.5f;
							boxA->setVelo(boxA->velo() + norm * l);
							boxB->setVelo(boxB->velo() + norm *-l);
						};
					}
				}
			}
			g->clearTarget(COLOR(0.4f, 0.4f, 0.4f, 1.0f));
			ds->set("%f", t);

			drawerManager->draw();

			//c->texture("backBox")->draw(Image2dShader,VECTOR2(1.0f,1.0f));
			g->present();
		}
	}
	delete Image2dShader;
	delete c;
	delete drawerManager;
}
#endif
//レイヤーテスト
#if(0)
void DebugRun() {
	WINDOW* w = WINDOW::instance();
	INDEV* indev = INDEV::instance();
	GRAPHIC* g = GRAPHIC::instance();
	DEBUG_STR* ds = DEBUG_STR::instance();
	CONTAINER* c = new CONTAINER("Assets/images/Menu/MenuIcon.txt");
	CONTAINER* c3D = new CONTAINER("Assets/GAME/Assets.txt");
	CONTAINER* cStage1 = new CONTAINER("Assets/STAGE01/assets.txt");
	//シェーダーのインスタンス
	IMAGE_2D* Image2dShader = new IMAGE_2D();
	SOFT_SHADOW* SoftShadowShader = new SOFT_SHADOW(2048, 2048);
	TOON* ToonShader = new TOON(2048, 2048);
	//SothShadowShaderの行列情報
	MATRIX LightView;
	MATRIX LightProj;
	LightView.set(VECTOR3(10.0f,20.0f,3.0f), VECTOR3(0, 0, 0), VECTOR3(0, 1, 0));//ライトから見た頂点群に変換するマトリックス
	LightProj.setOrtho(30.0f, 30.0f, -1.0f, -20.0f);//正投影（見たまんま＝遠いものを小さくしない）マトリックス
	MATRIX Proj;
	MATRIX View;
	Proj.setPers(3.141592f / 4.0f, g->aspect(), -0.1f, -50.1f);
	View.set(VECTOR3(2.0f, 1.0f, 10.0f), VECTOR3(0.0f, 0.2f, 0.0f), VECTOR3(0.0f, 1.0f, 0.0f));
	SoftShadowShader->setLight_ProjView(LightProj * LightView);
	SoftShadowShader->setProjView(Proj * View);
	SoftShadowShader->setLightAmbient(0.7f);
	// Light
	VECTOR3 LightPos = VECTOR3(0.0f, 10.0f, 0.01f);
	float Ambient = 1.0f;
	COLOR Diffuse = COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	CAMERA* Camera = new CAMERA();
	//2D画像を描画するレイヤーを作成
	DRAWER::MANAGER* drawerManager = new DRAWER::MANAGER();
	DRAWER::DRAWERS* drawers = new DRAWER::DRAWERS();
	drawers->setShader(Image2dShader);
	//ソフトシャドウで描画するレイヤーを作成
	DRAWER::DRAWERS* drawersSoftShadow = new DRAWER::DRAWERS();
	drawersSoftShadow->setShader(SoftShadowShader);
	//トゥーンで描画するレイヤーを作成
	DRAWER::DRAWERS* drawersToon= new DRAWER::DRAWERS();
	drawersToon->setShader(ToonShader);

	//レイヤーのレイアウトを設定
	std::array<DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT, 3> layout = {
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("toon3d", drawersToon),
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("3d", drawersSoftShadow),
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("ui", drawers)
	};
	DRAWER::DRAWERS_LIST* drawersList = new DRAWER::DRAWERS_LIST();
	drawersList->create(layout);
	drawerManager->create(drawersList);
	{
		struct DebugDrawer {
			void draw(SHADER* shader) {
				Ds->draw(shader);
			};
			DEBUG_STR* Ds = nullptr;
		};
		DebugDrawer* debugDrawer = new DebugDrawer;
		debugDrawer->Ds = ds;
		auto image = new DRAWER::SAUCER(debugDrawer);
		drawerManager->drawerAdd("ui", image);
	}
	NODE_LINE* line = new NODE_LINE(drawers);
	DRAWER_ARROW::setTexture(c->texture("oneDot"));
	DRAWER_ARROW::setTextureEnd(c->texture("arrow"));
	DRAWER_ARROW::setLineWidth(4.0f);
	NODE_LINE::setBendLength(16.0f);
	std::string str;
	VECTOR2 st;
	VECTOR2 ed;
	TREE* Tree = new TREE(c3D->treeOrigin("unitychan"));
	DRAWER::TREE* drawerTree = new DRAWER::TREE();
	Tree->setAnimation(c3D->animation("unitychanWait00"));
	drawerTree->setTree(Tree);
	drawerManager->drawerAdd("toon3d", drawerTree);
	//TREE* TreeMap = new TREE(cStage1->treeOrigin("map"));
	//DRAWER::TREE* drawerTreeMap = new DRAWER::TREE();
	//drawerTreeMap->setTree(TreeMap);
	//drawerManager->drawerAdd("3d", drawerTreeMap);

	while (w->msgProc()) {
		if (w->active()) {
			indev->getState();
			Camera->update(&View);
			VECTOR2 mousePoint = VECTOR2((float)indev->value(MOUSE_X), (float)indev->value(MOUSE_Y));
			if (indev->isPress(MOUSE_LBUTTON)) {
				st = mousePoint;
			}
			else{
				ed = mousePoint;
			}
			MATRIX world;
			Tree->update(world);
			line->pointsUpdate(st, ed);
			SoftShadowShader->setLight_ProjView(LightProj * LightView);
			SoftShadowShader->setProjView(Proj * View);

			g->clearTarget(0.5f, 0.5f, 0.5f);
			SHADER* shader = SoftShadowShader;
			shader->setLightPosition(LightPos);
			shader->setLightAmbient(Ambient);
			shader->setDiffuse(Diffuse);//これ忘れて何も映らず時間無駄にしたこと忘れんな
			shader->setProjView(Proj * View);
			shader->setLight_ProjView(LightProj * LightView);

			drawerManager->draw();

			//c->texture("backBox")->draw(Image2dShader,VECTOR2(1.0f,1.0f));
			g->present();
		}
	}
	delete line;
	delete Tree;
	//delete TreeMap;
	delete c3D;
	delete cStage1;
	delete ToonShader;
	delete SoftShadowShader;
	delete Image2dShader;
	delete c;
	delete drawerManager;
}
#endif
//レイヤーテスト３D
#if(0)
class CAMERA {
public:
	CAMERA(float verticalRad = 0.0f, float horizontalRad = 0.0f, float distanceFromLookatPos = 5.0f, float rotateSpeed = 0.02f, float zoomSpeed = 0.02f);
	~CAMERA();
	void setDistanceFromLookatPos(float distanceFromLookatPos);
	void update(MATRIX* view, VECTOR3 lookatPos, float offsetPosY = 1.0f);
	float verticalRad();
	float horizontalRad();
private:
	float VerticalRad;
	float HorizontalRad;
	float DistanceFromLookatPos;
	float RotateSpeed;
	float ZoomSpeed;
	VECTOR3 CameraPos;
	VECTOR3 LookatPos;
	float OffsetPosY;
};

CAMERA::CAMERA(float verticalRad, float horizontalRad, float distanceFromLookatPos,
	float rotateSpeed, float zoomSpeed) :
	VerticalRad(verticalRad),
	HorizontalRad(horizontalRad),
	DistanceFromLookatPos(distanceFromLookatPos),
	RotateSpeed(rotateSpeed),
	ZoomSpeed(zoomSpeed) {
}

CAMERA::~CAMERA() {
}

void CAMERA::setDistanceFromLookatPos(float distanceFromLookatPos) {
	DistanceFromLookatPos = distanceFromLookatPos;
}


void CAMERA::update(MATRIX* view, VECTOR3 lookatPos, float offsetPosY) {
	INDEV* in = INDEV::instance();

	if (in->isPress(KEY_D)) {
		HorizontalRad += RotateSpeed;
	}
	if (in->isPress(KEY_A)) {
		HorizontalRad -= RotateSpeed;
	}
	if (in->isPress(KEY_W)) {
		VerticalRad += RotateSpeed;
		if (VerticalRad > 1.57f) {
			VerticalRad = 1.57f;
		}
	}
	if (in->isPress(KEY_S)) {
		VerticalRad -= RotateSpeed;
		if (VerticalRad < -1.57f) {
			VerticalRad = -1.57f;
		}
	}
	if (in->isPress(KEY_E)) {
		DistanceFromLookatPos -= ZoomSpeed;
		if (DistanceFromLookatPos < 1.0f) {
			DistanceFromLookatPos = 1.0f;
		}
	}
	if (in->isPress(KEY_Q)) {
		DistanceFromLookatPos += ZoomSpeed;
	}


	LookatPos = lookatPos;
	LookatPos.y += offsetPosY;
	CameraPos = LookatPos;
	CameraPos.x += sinf(HorizontalRad) * cosf(VerticalRad) * DistanceFromLookatPos;
	CameraPos.y += sinf(VerticalRad) * DistanceFromLookatPos;
	CameraPos.z += cosf(HorizontalRad) * cosf(VerticalRad) * DistanceFromLookatPos;
	view->set(CameraPos, LookatPos, VECTOR3(0, 1, 0));
}

float CAMERA::verticalRad() {
	return VerticalRad;
}

float CAMERA::horizontalRad() {
	return HorizontalRad;
}

void DebugRun() {
	WINDOW* w = WINDOW::instance();
	INDEV* indev = INDEV::instance();
	GRAPHIC* g = GRAPHIC::instance();
	DEBUG_STR* ds = DEBUG_STR::instance();
	IMAGE_2D* Image2dShader = new IMAGE_2D();
	SOFT_SHADOW* SoftShadowShader = new SOFT_SHADOW(2048, 2048);
	CONTAINER* c = new CONTAINER("Assets/GAME/Assets.txt");
	CONTAINER* cStage1 = new CONTAINER("Assets/STAGE01/assets.txt");
	//CONTAINER* cSample = new CONTAINER("Assets/Assets.txt");

	CAMERA* Camera = new CAMERA();
	Camera->setDistanceFromLookatPos(6.0f);

	//SothShadowShaderの行列情報
	MATRIX LightView;
	MATRIX LightProj;
	LightView.set(VECTOR3(10.0f, 20.0f, 3.0f), VECTOR3(0, 0, 0), VECTOR3(0, 1, 0));//ライトから見た頂点群に変換するマトリックス
	LightProj.setOrtho(30.0f, 30.0f, -1.0f, -20.0f);//正投影（見たまんま＝遠いものを小さくしない）マトリックス
	MATRIX Proj;
	MATRIX View;
	Proj.setPers(3.141592f / 3.0f, g->aspect(), -0.1f, -50.1f);
	// Light
	VECTOR3 LightPos = VECTOR3(0.0f, 10.0f, 0.01f);
	float Ambient = 1.0f;
	COLOR Diffuse = COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// LightからのViewとProj
	LightView.set(LightPos, VECTOR3(0, 0, 0), VECTOR3(0, 1, 0));//ライトから見た頂点群に変換するマトリックス
	LightProj.setOrtho(10.0f, 10.0f, -1.0f, -20.0f);//正投影（見たまんま＝遠いものを小さくしない）マトリックス

	//SoftShadowShader->setWorld
	TREE* TreeMap = new TREE(cStage1->treeOrigin("map"));
	TREE* Tree = new TREE(c->treeOrigin("unitychan"));
	//BATCH* Batch = cSample->batch("floor");
	MATRIX world;
	world.mulTranslate(VECTOR3(0.0f, 0.0f, 0.0f));
	Tree->update(world);
	VECTOR3 CameraPos;
	VECTOR3 LookAt;
	while (w->msgProc()) {
		if (w->active()) {
			indev->getState();
			//VECTOR3& posp = CameraPos;
			//if (indev->isPress(KEY_Z)) {
			//	posp = LookAt;
			//}
			//if(indev->isPress( KEY_D ) ){
			//	posp.x += 0.1f;
			//}
			//if(indev->isPress( KEY_A ) ){
			//	posp.x += -0.1f;
			//}
			//if(indev->isPress( KEY_W ) ){
			//	posp.y += 0.1f;
			//}
			//if(indev->isPress( KEY_S ) ){
			//	posp.y += -0.1f;
			//}
			//if(indev->isPress( KEY_E ) ){
			//	posp.z += 0.1f;
			//}
			//if(indev->isPress( KEY_Q ) ){
			//	posp.z += -0.1f;
			//}

			g->clearTarget(0.6f, 0.6f, 0.6f);
			SHADER* shader = SoftShadowShader;
			Camera->update(&View, VECTOR3(0.0f, 0.0f, 0.0f), 1.2f);
			shader->setLightPosition(LightPos);
			shader->setLightAmbient(Ambient);
			shader->setDiffuse(Diffuse);
			shader->setProjView(Proj * View);
			shader->setLight_ProjView(LightProj * LightView);
			BEGIN_PATH_
			g->setTextureSamplerWrap();
			Tree->draw(shader);
			TreeMap->update(MATRIX());
			TreeMap->draw(shader);
			//Batch->draw(shader, MATRIX());
			g->setTextureSamplerClamp();
			END_PATH_
			g->present();
		}
	}
	delete c;
	delete SoftShadowShader;
	delete Image2dShader;
}
#endif
//UI
#if(0)
void DebugRun() {
	WINDOW* w = WINDOW::instance();
	INDEV* indev = INDEV::instance();

	DEBUG_STR* ds = DEBUG_STR::instance();
	CONTAINER* c = new CONTAINER("MenuIcon.txt");
	//IMAGE_2D* Image2dShader = new IMAGE_2D();
	IMAGE2D_CAMERA* Image2dCameraShader = new IMAGE2D_CAMERA();
	DRAWER::MANAGER* drawerManager = new DRAWER::MANAGER();
	DRAWER::DRAWERS* drawers = new DRAWER::DRAWERS();
	drawers->setShader(Image2dCameraShader);
	std::array<DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT, 1> layout = {
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("ui", drawers)
	};
	DRAWER::DRAWERS_LIST* drawersList = new DRAWER::DRAWERS_LIST();
	drawersList->create(layout);
	drawerManager->create(drawersList);
	{
		struct DebugDrawer {
			void draw(SHADER* shader) {
				Ds->draw(shader);
			};
			DEBUG_STR* Ds = nullptr;
		};
		DebugDrawer* debugDrawer = new DebugDrawer;
		debugDrawer->Ds = ds;
		auto image = new DRAWER::SAUCER(debugDrawer);
		drawerManager->drawerAdd("ui", image);
	}
	std::string str;
	GRAPHIC* g = GRAPHIC::instance();
	float t = 0.0f;
	//マウスの判定
	COLLISION2D_POINT* mousePoint = new COLLISION2D_POINT;
	COLLISION2D_RECT* mouseRect = new COLLISION2D_RECT;
	mouseRect->setWh(c->texture("plusIcon")->wh());
	DRAWER::IMAGE2D* mouseRectImage = new DRAWER::IMAGE2D;
	mouseRectImage->setPivot(DRAWER::IMAGE2D::drawMethodLeft());
	mouseRectImage->setTexture(c->texture("plusIcon"));
	drawerManager->drawerAdd("ui", mouseRectImage);


	//UIレイアウト
	std::vector<UI*> Childs;
	{
		std::vector<UI*> Childs1;
		{
			{
				UI* UiChild1 = new UI;
				DRAWER::IMAGE2D* Image = new DRAWER::IMAGE2D;
				Image->setPos(VECTOR2(50, 50));
				Image->setTexture(c->texture("plusIcon"));
				Image->setPivot(Image->drawMethodLeft());
				COLLISION2D_RECT* collisionRect = new COLLISION2D_RECT();
				collisionRect->setPos(VECTOR2(50, 50));
				collisionRect->setWh(c->texture("plusIcon")->wh());
				UiChild1->create(Image, collisionRect, std::move(std::vector<UI*>()));
				Childs1.push_back(UiChild1);
			}
			{
				UI* UiChild1 = new UI;
				DRAWER::IMAGE2D* Image = new DRAWER::IMAGE2D;
				Image->setPos(VECTOR2(60, 60));
				Image->setTexture(c->texture("plusIcon"));
				Image->setPivot(Image->drawMethodLeft());
				COLLISION2D_RECT* collisionRect = new COLLISION2D_RECT();
				collisionRect->setPos(VECTOR2(60, 60));
				collisionRect->setWh(c->texture("plusIcon")->wh());
				UiChild1->create(Image, collisionRect, std::move(std::vector<UI*>()));
				Childs1.push_back(UiChild1);
			}

		}
		UI* UiChild1 = new UI;
		DRAWER::IMAGE2D* Image = new DRAWER::IMAGE2D;
		Image->setPos(VECTOR2(100, 100));
		Image->setTexture(c->texture("plusIcon"));
		Image->setPivot(Image->drawMethodLeft());
		COLLISION2D_RECT* collisionRect = new COLLISION2D_RECT();
		collisionRect->setPos(VECTOR2(100, 100));
		collisionRect->setWh(c->texture("plusIcon")->wh());
		UiChild1->create(Image, collisionRect, std::move(Childs1));
		Childs.push_back(UiChild1);
	}

	UI* UiRoot = new UI;
	DRAWER::IMAGE2D* Image = new DRAWER::IMAGE2D;
	Image->setPos(VECTOR2(200, 200));
	Image->setTexture(c->texture("plusIcon"));
	Image->setPivot(Image->drawMethodLeft());
	COLLISION2D_RECT* collisionRect = new COLLISION2D_RECT();
	collisionRect->setPos(VECTOR2(200, 200));
	collisionRect->setWh(c->texture("plusIcon")->wh());
	UiRoot->create(Image, collisionRect, std::move(Childs));

	//ドラッグしているUI
	UI* choiceUi = nullptr;
	UI* choiceUiScale = nullptr;

	//当たり判定デバッグ
	COLLISION2D_TUPLE<COLLISION2D_RECT*, COLLISION2D_RECT*> cs;
	COLLISION2D_RECT* collisionRect1 = new COLLISION2D_RECT();
	collisionRect1->setPos(VECTOR2(200, 200));
	collisionRect1->setWh(c->texture("plusIcon")->wh());
	COLLISION2D_RECT* collisionRect2 = new COLLISION2D_RECT();
	collisionRect2->setPos(VECTOR2(300, 300));
	collisionRect2->setWh(c->texture("plusIcon")->wh());
	//{
	//	DRAWER::IMAGE2D* image = new DRAWER::IMAGE2D;
	//	image->setPivot(DRAWER::IMAGE2D::drawMethodLeft());
	//	image->setPos(VECTOR2(200, 200));
	//	image->setTexture(c->texture("plusIcon"));
	//	drawerManager->drawerAdd("ui", image);
	//}
	//{
	//	DRAWER::IMAGE2D* image = new DRAWER::IMAGE2D;
	//	image->setPivot(DRAWER::IMAGE2D::drawMethodLeft());
	//	image->setPos(VECTOR2(300, 300));
	//	image->setTexture(c->texture("plusIcon"));
	//	drawerManager->drawerAdd("ui", image);
	//}

	cs.get<0>() = collisionRect1;
	cs.get<1>() = collisionRect2;

	while (w->msgProc()) {
		if (w->active()) {
			indev->getState();
			mousePoint->setPos(VECTOR2(indev->value(MOUSE_X), indev->value(MOUSE_Y)));
			mouseRectImage->setPos(mouseRect->pos());
			ds->set("mx:%d my:%d", indev->value(MOUSE_X), indev->value(MOUSE_Y));
			g->clearTarget(COLOR(0.4f, 0.4f, 0.4f, 1.0f));
			ds->set("%f", t);

			SHADER* shader = Image2dCameraShader;
			UiRoot->exeOverlap(mousePoint);
			if (indev->isTrigger(MOUSE_LBUTTON)) {
				UI* overlapUi = nullptr;
				UiRoot->OverlapUi(mousePoint, overlapUi);
				if (overlapUi != nullptr) {
					choiceUi = overlapUi;
				}
			}
			if (cs.isHit(mousePoint)) {
				ds->set("hit");
			}
			if (indev->isUp(MOUSE_LBUTTON)) {
				choiceUi = nullptr;
			}
			if (choiceUi != nullptr) {
				choiceUi->setPos(choiceUi->pos() + VECTOR2(indev->relativeValue(MOUSE_X), indev->relativeValue(MOUSE_Y)) / choiceUi->parentScale());
			}

			if (indev->isTrigger(MOUSE_RBUTTON)) {
				UI* overlapUi = nullptr;
				UiRoot->OverlapUi(mousePoint, overlapUi);
				if (overlapUi != nullptr) {
					choiceUiScale = overlapUi;
				}
			}
			if (indev->isUp(MOUSE_RBUTTON)) {
				choiceUiScale = nullptr;
			}
			if (choiceUiScale != nullptr) {
				choiceUiScale->setScale(choiceUiScale->scale() + VECTOR2(indev->relativeValue(MOUSE_X), indev->relativeValue(MOUSE_Y)) * 0.01);
			}
			MATRIX cameraWorld;
			cameraWorld.identity();
			Image2dCameraShader->setCameraWorld(cameraWorld);
			BEGIN_PATH_

				UiRoot->draw(shader);

			END_PATH_
				drawerManager->draw();
			//c->texture("backBox")->draw(Image2dShader,VECTOR2(1.0f,1.0f));
			g->present();
		}
	}
	delete mousePoint;
	delete mouseRect;
	delete UiRoot;
	delete collisionRect1;
	delete collisionRect2;
	delete Image2dCameraShader;
	delete c;
	delete drawerManager;
}
#endif
//直線当たり判定
#if(0)
void DebugRun() {
	WINDOW* w = WINDOW::instance();
	INDEV* indev = INDEV::instance();

	DEBUG_STR* ds = DEBUG_STR::instance();
	CONTAINER* c = new CONTAINER("MenuIcon.txt");
	IMAGE_2D* Image2dShader = new IMAGE_2D();
	DRAWER::MANAGER* drawerManager = new DRAWER::MANAGER();
	DRAWER::DRAWERS* drawers = new DRAWER::DRAWERS();
	drawers->setShader(Image2dShader);
	std::array<DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT, 1> layout = {
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("ui", drawers)
	};
	DRAWER::DRAWERS_LIST* drawersList = new DRAWER::DRAWERS_LIST();
	drawersList->create(layout);
	drawerManager->create(drawersList);

	{
		struct DebugDrawer {
			void draw(SHADER* shader) {
				Ds->draw(shader);
			};
			DEBUG_STR* Ds = nullptr;
		};
		DebugDrawer* debugDrawer = new DebugDrawer;
		debugDrawer->Ds = ds;
		auto image = new DRAWER::SAUCER(debugDrawer);
		drawerManager->drawerAdd("ui", image);
	}
	TEXTURE* texture = c->texture("plusIcon");
	GRAPHIC* g = GRAPHIC::instance();
	COLLISION2D_POINT* mousePoint = new COLLISION2D_POINT;

	VECTOR2 st;
	VECTOR2 ed;

	while (w->msgProc()) {
		if (w->active()) {
			indev->getState();
			mousePoint->setPos(VECTOR2(indev->value(MOUSE_X), indev->value(MOUSE_Y)));
			if (indev->isPress(MOUSE_LBUTTON)) {
				ed = mousePoint->pos();
			}
			else{
				st = mousePoint->pos();
			}
			ds->set("mx:%d my:%d", indev->value(MOUSE_X), indev->value(MOUSE_Y));
			g->clearTarget(COLOR(0.4f, 0.4f, 0.4f, 1.0f));
			SHADER* shader = Image2dShader;
			BEGIN_PATH_

				texture->drawLine(shader, st, ed, 0.01f);
				texture->drawLine(shader, VECTOR2(500, 100), VECTOR2(500, 500), 0.01f);
				texture->drawLine(shader, VECTOR2(500, 100), VECTOR2(900, 100), 0.01f);
				if (Calc2DAxisYLineAndLine(VECTOR2(500, 100), 400, st, ed - st)) {
					ds->set("hit");
				}
				if (Calc2DAxisXLineAndLine(VECTOR2(500, 100), 400, st, ed - st)) {
					ds->set("hit");
				}

			END_PATH_
				drawerManager->draw();
			//c->texture("backBox")->draw(Image2dShader,VECTOR2(1.0f,1.0f));
			g->present();
		}
	}
	delete mousePoint;
	delete Image2dShader;
	delete c;
	delete drawerManager;
}
#endif
//矩形同士の簡易押し出し
#if(0)
void DebugRun() {
	WINDOW* w = WINDOW::instance();
	INDEV* indev = INDEV::instance();

	DEBUG_STR* ds = DEBUG_STR::instance();
	CONTAINER* c = new CONTAINER("MenuIcon.txt");
	//IMAGE_2D* Image2dShader = new IMAGE_2D();
	IMAGE2D_CAMERA* Image2dCameraShader = new IMAGE2D_CAMERA();
	DRAWER::MANAGER* drawerManager = new DRAWER::MANAGER();
	DRAWER::DRAWERS* drawers = new DRAWER::DRAWERS();
	drawers->setShader(Image2dCameraShader);
	std::array<DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT, 1> layout = {
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("ui", drawers)
	};
	DRAWER::DRAWERS_LIST* drawersList = new DRAWER::DRAWERS_LIST();
	drawersList->create(layout);
	drawerManager->create(drawersList);
	{
		struct DebugDrawer {
			void draw(SHADER* shader) {
				Ds->draw(shader);
			};
			DEBUG_STR* Ds = nullptr;
		};
		DebugDrawer* debugDrawer = new DebugDrawer;
		debugDrawer->Ds = ds;
		auto image = new DRAWER::SAUCER(debugDrawer);
		drawerManager->drawerAdd("ui", image);
	}
	std::string str;
	GRAPHIC* g = GRAPHIC::instance();
	float t = 0.0f;
	//マウスの判定
	COLLISION2D_POINT* mousePoint = new COLLISION2D_POINT;
	COLLISION2D_RECT* mouseRect = new COLLISION2D_RECT;
	mouseRect->setWh(c->texture("plusIcon")->wh());
	DRAWER::IMAGE2D* mouseRectImage = new DRAWER::IMAGE2D;
	mouseRectImage->setPivot(DRAWER::IMAGE2D::drawMethodLeft());
	mouseRectImage->setTexture(c->texture("plusIcon"));
	drawerManager->drawerAdd("ui", mouseRectImage);

	//当たり判定デバッグ
	struct BOX{
		VECTOR2 Pos;
		COLLISION2D_RECT* Rect;
		DRAWER::IMAGE2D* Image;
		void update() {
			Rect->setPos(Pos);
			Image->setPos(Pos);
		}
	};

	BOX boxs[16];
	for (auto& i : boxs) {
		i.Image = new DRAWER::IMAGE2D;
		i.Image->setTexture(c->texture("plusIcon"));
		drawerManager->drawerAdd("ui", i.Image);
		i.Rect = new COLLISION2D_RECT;
		i.Rect->setWh(c->texture("plusIcon")->wh());
		i.Pos = VECTOR2((float)rand()/RAND_MAX*g->baseWidth(), (float)rand()/ RAND_MAX* g->baseHeight());
	}
	while (w->msgProc()) {
		if (w->active()) {
			indev->getState();
			mouseRect->setPos(VECTOR2(indev->value(MOUSE_X), indev->value(MOUSE_Y)));
			mouseRectImage->setPos(mouseRect->pos());
			ds->set("mx:%d my:%d", indev->value(MOUSE_X), indev->value(MOUSE_Y));
			g->clearTarget(COLOR(0.4f, 0.4f, 0.4f, 1.0f));
			ds->set("%f", t);

			for (auto& i : boxs) {
				VECTOR2 norm;
				if (Calc2DStaticRectAndRectExtrude(mouseRect->pos(), mouseRect->wh(), i.Pos, i.Rect->wh(), norm)) {
					i.Pos += norm;
				}
			}		
			for (auto& i : boxs) {
				i.update();
			}
			SHADER* shader = Image2dCameraShader;
			MATRIX cameraWorld;
			cameraWorld.identity();
			Image2dCameraShader->setCameraWorld(cameraWorld);
			BEGIN_PATH_


			END_PATH_
				drawerManager->draw();
			//c->texture("backBox")->draw(Image2dShader,VECTOR2(1.0f,1.0f));
			g->present();
		}
	}
	delete mousePoint;
	delete Image2dCameraShader;
	delete c;
	delete drawerManager;
}
#endif
//矩形と円の当たり判定
#if(0)
void DebugRun() {
	WINDOW* w = WINDOW::instance();
	INDEV* indev = INDEV::instance();

	DEBUG_STR* ds = DEBUG_STR::instance();
	CONTAINER* c = new CONTAINER("MenuIcon.txt");
	//IMAGE_2D* Image2dShader = new IMAGE_2D();
	IMAGE2D_CAMERA* Image2dCameraShader = new IMAGE2D_CAMERA();
	DRAWER::MANAGER* drawerManager = new DRAWER::MANAGER();
	DRAWER::DRAWERS* drawers = new DRAWER::DRAWERS();
	drawers->setShader(Image2dCameraShader);
	std::array<DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT, 1> layout = {
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("ui", drawers)
	};
	DRAWER::DRAWERS_LIST* drawersList = new DRAWER::DRAWERS_LIST();
	drawersList->create(layout);
	drawerManager->create(drawersList);
	{
		struct DebugDrawer {
			void draw(SHADER* shader) {
				Ds->draw(shader);
			};
			DEBUG_STR* Ds = nullptr;
		};
		DebugDrawer* debugDrawer = new DebugDrawer;
		debugDrawer->Ds = ds;
		auto image = new DRAWER::SAUCER(debugDrawer);
		drawerManager->drawerAdd("ui", image);
	}
	std::string str;
	GRAPHIC* g = GRAPHIC::instance();
	float t = 0.0f;
	//マウスの判定
	COLLISION2D_POINT* mousePoint = new COLLISION2D_POINT;
	COLLISION2D_RECT* mouseRect = new COLLISION2D_RECT;
	mouseRect->setWh(c->texture("plusIcon")->wh());
	DRAWER::IMAGE2D* mouseRectImage = new DRAWER::IMAGE2D;
	mouseRectImage->setPivot(DRAWER::IMAGE2D::drawMethodLeft());
	mouseRectImage->setTexture(c->texture("plusIcon"));
	drawerManager->drawerAdd("ui", mouseRectImage);

	//当たり判定デバッグ
	struct CIRCLE {
		VECTOR2 Pos;
		float R;
		DRAWER::IMAGE2D* Image;
		void update() {
			Image->setPos(Pos);
		}
	};

	CIRCLE circles[16];
	for (auto& i : circles) {
		i.Image = new DRAWER::IMAGE2D;
		i.Image->setTexture(c->texture("minusIcon"));
		i.Image->setPivot(DRAWER::IMAGE2D::drawMethodCentered());
		i.R = c->texture("minusIcon")->width() * 0.5f;
		drawerManager->drawerAdd("ui", i.Image);
		i.Pos = VECTOR2((float)rand() / RAND_MAX * g->baseWidth(), (float)rand() / RAND_MAX * g->baseHeight());
	}
	while (w->msgProc()) {
		if (w->active()) {
			indev->getState();
			mouseRect->setPos(VECTOR2(indev->value(MOUSE_X), indev->value(MOUSE_Y)));
			mousePoint->setPos(mouseRect->pos());
			mouseRectImage->setPos(mouseRect->pos());
			ds->set("mx:%d my:%d", indev->value(MOUSE_X), indev->value(MOUSE_Y));
			g->clearTarget(COLOR(0.4f, 0.4f, 0.4f, 1.0f));
			ds->set("%f", t);

			for (auto& i : circles) {
				VECTOR2 norm;
				if (Calc2DCircleAndPointIsHit(i.Pos,i.R,mousePoint->pos())) {
					ds->set("pointHit");
				}
				if (Calc2DRectAndCircleIsHit(mouseRect->pos(), mouseRect->wh(),i.Pos, i.R)) {
					ds->set("rectHit");
					i.Pos += norm;
				}
			}
			for (auto& i : circles) {
				i.update();
			}
			SHADER* shader = Image2dCameraShader;
			MATRIX cameraWorld;
			cameraWorld.identity();
			Image2dCameraShader->setCameraWorld(cameraWorld);
			BEGIN_PATH_


				END_PATH_
				drawerManager->draw();
			//c->texture("backBox")->draw(Image2dShader,VECTOR2(1.0f,1.0f));
			g->present();
		}
	}
	delete mousePoint;
	delete Image2dCameraShader;
	delete c;
	delete drawerManager;
}
#endif
//矩形と円の衝突応答
#if(0)
void DebugRun() {
	WINDOW* w = WINDOW::instance();
	INDEV* indev = INDEV::instance();

	DEBUG_STR* ds = DEBUG_STR::instance();
	CONTAINER* c = new CONTAINER("MenuIcon.txt");
	//IMAGE_2D* Image2dShader = new IMAGE_2D();
	IMAGE2D_CAMERA* Image2dCameraShader = new IMAGE2D_CAMERA();
	DRAWER::MANAGER* drawerManager = new DRAWER::MANAGER();
	DRAWER::DRAWERS* drawers = new DRAWER::DRAWERS();
	drawers->setShader(Image2dCameraShader);
	std::array<DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT, 1> layout = {
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("ui", drawers)
	};
	DRAWER::DRAWERS_LIST* drawersList = new DRAWER::DRAWERS_LIST();
	drawersList->create(layout);
	drawerManager->create(drawersList);
	{
		struct DebugDrawer {
			void draw(SHADER* shader) {
				Ds->draw(shader);
			};
			DEBUG_STR* Ds = nullptr;
		};
		DebugDrawer* debugDrawer = new DebugDrawer;
		debugDrawer->Ds = ds;
		auto image = new DRAWER::SAUCER(debugDrawer);
		drawerManager->drawerAdd("ui", image);
	}
	std::string str;
	GRAPHIC* g = GRAPHIC::instance();
	float t = 0.0f;
	//マウスの判定
	COLLISION2D_POINT* mousePoint = new COLLISION2D_POINT;
	COLLISION2D_RECT* mouseRect = new COLLISION2D_RECT;
	mouseRect->setWh(c->texture("minusIcon")->wh());
	DRAWER::IMAGE2D* mouseRectImage = new DRAWER::IMAGE2D;
	mouseRectImage->setPivot(DRAWER::IMAGE2D::drawMethodLeft());
	mouseRectImage->setTexture(c->texture("plusIcon"));
	drawerManager->drawerAdd("ui", mouseRectImage);
	COLLISION2D_CIRCLE* mouseCircle = new COLLISION2D_CIRCLE;
	mouseCircle->setR(c->texture("minusIcon")->width() * 0.5f);

	//当たり判定デバッグ
	struct CIRCLE {
		VECTOR2 Pos;
		float R;
		DRAWER::IMAGE2D* Image;
		void update() {
			Image->setPos(Pos);
		}
	};

	CIRCLE circles[16];
	for (auto& i : circles) {
		i.Image = new DRAWER::IMAGE2D;
		i.Image->setTexture(c->texture("minusIcon"));
		i.Image->setPivot(DRAWER::IMAGE2D::drawMethodCentered());
		i.R = c->texture("minusIcon")->width() * 0.5f;
		drawerManager->drawerAdd("ui", i.Image);
		i.Pos = VECTOR2((float)rand() / RAND_MAX * g->baseWidth(), (float)rand() / RAND_MAX * g->baseHeight());
	}
	while (w->msgProc()) {
		if (w->active()) {
			indev->getState();
			mouseRect->setPos(VECTOR2(indev->value(MOUSE_X), indev->value(MOUSE_Y)));
			mousePoint->setPos(mouseRect->pos());
			mouseRectImage->setPos(mouseRect->pos());
			mouseCircle->setPos(mouseRect->pos());
			ds->set("mx:%d my:%d", indev->value(MOUSE_X), indev->value(MOUSE_Y));
			g->clearTarget(COLOR(0.4f, 0.4f, 0.4f, 1.0f));
			ds->set("%f", t);

			for (auto& i : circles) {
				VECTOR2 norm;
				if (Calc2DCircleAndPointIsHit(i.Pos, i.R, mousePoint->pos())) {
					ds->set("pointHit");
				}
				if (Calc2DStaticRectAndCircleExtrude(mouseRect->pos(), mouseRect->wh(), i.Pos, i.R, norm)) {
					ds->set("circleHit");
					i.Pos += norm;
				}
			}
			for (auto& i : circles) {
				i.update();
			}
			SHADER* shader = Image2dCameraShader;
			MATRIX cameraWorld;
			cameraWorld.identity();
			Image2dCameraShader->setCameraWorld(cameraWorld);
			BEGIN_PATH_


				END_PATH_
				drawerManager->draw();
			//c->texture("backBox")->draw(Image2dShader,VECTOR2(1.0f,1.0f));
			g->present();
		}
	}
	delete mousePoint;
	delete Image2dCameraShader;
	delete c;
	delete drawerManager;
}
#endif
//円と矩形の衝突応答
#if(0)
void DebugRun() {
	WINDOW* w = WINDOW::instance();
	INDEV* indev = INDEV::instance();

	DEBUG_STR* ds = DEBUG_STR::instance();
	CONTAINER* c = new CONTAINER("MenuIcon.txt");
	//IMAGE_2D* Image2dShader = new IMAGE_2D();
	IMAGE2D_CAMERA* Image2dCameraShader = new IMAGE2D_CAMERA();
	DRAWER::MANAGER* drawerManager = new DRAWER::MANAGER();
	DRAWER::DRAWERS* drawers = new DRAWER::DRAWERS();
	drawers->setShader(Image2dCameraShader);
	std::array<DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT, 1> layout = {
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("ui", drawers)
	};
	DRAWER::DRAWERS_LIST* drawersList = new DRAWER::DRAWERS_LIST();
	drawersList->create(layout);
	drawerManager->create(drawersList);
	{
		struct DebugDrawer {
			void draw(SHADER* shader) {
				Ds->draw(shader);
			};
			DEBUG_STR* Ds = nullptr;
		};
		DebugDrawer* debugDrawer = new DebugDrawer;
		debugDrawer->Ds = ds;
		auto image = new DRAWER::SAUCER(debugDrawer);
		drawerManager->drawerAdd("ui", image);
	}
	std::string str;
	GRAPHIC* g = GRAPHIC::instance();
	float t = 0.0f;
	//マウスの判定
	COLLISION2D_POINT* mousePoint = new COLLISION2D_POINT;
	COLLISION2D_RECT* mouseRect = new COLLISION2D_RECT;
	mouseRect->setWh(c->texture("minusIcon")->wh());
	DRAWER::IMAGE2D* mouseRectImage = new DRAWER::IMAGE2D;
	mouseRectImage->setPivot(DRAWER::IMAGE2D::drawMethodCentered());
	mouseRectImage->setTexture(c->texture("minusIcon"));
	drawerManager->drawerAdd("ui", mouseRectImage);
	COLLISION2D_CIRCLE* mouseCircle = new COLLISION2D_CIRCLE;
	mouseCircle->setR(c->texture("minusIcon")->width() * 0.5f);

	//当たり判定デバッグ
	struct BOX {
		VECTOR2 Pos;
		VECTOR2 Wh;
		DRAWER::IMAGE2D* Image;
		void update() {
			Image->setPos(Pos);
		}
	};

	BOX boxs[16];
	for (auto& i : boxs) {
		i.Image = new DRAWER::IMAGE2D;
		i.Image->setTexture(c->texture("plusIcon"));
		i.Image->setPivot(DRAWER::IMAGE2D::drawMethodLeft());
		i.Wh = c->texture("plusIcon")->wh();
		drawerManager->drawerAdd("ui", i.Image);
		i.Pos = VECTOR2((float)rand() / RAND_MAX * g->baseWidth(), (float)rand() / RAND_MAX * g->baseHeight());
	}
	while (w->msgProc()) {
		if (w->active()) {
			indev->getState();
			mouseRect->setPos(VECTOR2(indev->value(MOUSE_X), indev->value(MOUSE_Y)));
			mousePoint->setPos(mouseRect->pos());
			mouseRectImage->setPos(mouseRect->pos());
			mouseCircle->setPos(mouseRect->pos());
			ds->set("mx:%d my:%d", indev->value(MOUSE_X), indev->value(MOUSE_Y));
			g->clearTarget(COLOR(0.4f, 0.4f, 0.4f, 1.0f));
			ds->set("%f", t);

			for (auto& i : boxs) {
				VECTOR2 norm;
				if (Calc2DStaticCircleAndRectExtrude(mouseCircle->pos(), mouseCircle->r(), i.Pos, i.Wh, norm)) {
					ds->set("boxHit");
					i.Pos += norm;
				}
			}
			for (auto& i : boxs) {
				i.update();
			}
			SHADER* shader = Image2dCameraShader;
			MATRIX cameraWorld;
			cameraWorld.identity();
			Image2dCameraShader->setCameraWorld(cameraWorld);
			BEGIN_PATH_


				END_PATH_
				drawerManager->draw();
			//c->texture("backBox")->draw(Image2dShader,VECTOR2(1.0f,1.0f));
			g->present();
		}
	}
	delete mousePoint;
	delete Image2dCameraShader;
	delete c;
	delete drawerManager;
}
#endif
//プルダウンUI
#if(0)
void DebugRun() {
	WINDOW* w = WINDOW::instance();
	INDEV* indev = INDEV::instance();

	DEBUG_STR* ds = DEBUG_STR::instance();
	CONTAINER* c = new CONTAINER("MenuIcon.txt");
	//IMAGE_2D* Image2dShader = new IMAGE_2D();
	IMAGE2D_CAMERA* Image2dCameraShader = new IMAGE2D_CAMERA();
	DRAWER::MANAGER* drawerManager = new DRAWER::MANAGER();
	DRAWER::DRAWERS* drawers = new DRAWER::DRAWERS();
	drawers->setShader(Image2dCameraShader);
	std::array<DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT, 1> layout = {
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("ui", drawers)
	};
	DRAWER::DRAWERS_LIST* drawersList = new DRAWER::DRAWERS_LIST();
	drawersList->create(layout);
	drawerManager->create(drawersList);
	{
		struct DebugDrawer {
			void draw(SHADER* shader) {
				Ds->draw(shader);
			};
			DEBUG_STR* Ds = nullptr;
		};
		DebugDrawer* debugDrawer = new DebugDrawer;
		debugDrawer->Ds = ds;
		auto image = new DRAWER::SAUCER(debugDrawer);
		drawerManager->drawerAdd("ui", image);
	}
	std::string str;
	GRAPHIC* g = GRAPHIC::instance();
	float t = 0.0f;
	//マウスの判定
	COLLISION2D_POINT* mousePoint = new COLLISION2D_POINT;
	COLLISION2D_RECT* mouseRect = new COLLISION2D_RECT;
	mouseRect->setWh(c->texture("minusIcon")->wh());
	DRAWER::IMAGE2D* mouseRectImage = new DRAWER::IMAGE2D;
	mouseRectImage->setPivot(DRAWER::IMAGE2D::drawMethodCentered());
	mouseRectImage->setTexture(c->texture("minusIcon"));
	drawerManager->drawerAdd("ui", mouseRectImage);
	COLLISION2D_CIRCLE* mouseCircle = new COLLISION2D_CIRCLE;
	mouseCircle->setR(c->texture("minusIcon")->width() * 0.5f);

	//当たり判定デバッグ
	struct BOX {
		VECTOR2 Pos;
		VECTOR2 Wh;
		DRAWER::IMAGE2D* Image;
		void update() {
			Image->setPos(Pos);
		}
	};

	BOX boxs[16];
	for (auto& i : boxs) {
		i.Image = new DRAWER::IMAGE2D;
		i.Image->setTexture(c->texture("plusIcon"));
		i.Image->setPivot(DRAWER::IMAGE2D::drawMethodLeft());
		i.Wh = c->texture("plusIcon")->wh();
		drawerManager->drawerAdd("ui", i.Image);
		i.Pos = VECTOR2((float)rand() / RAND_MAX * g->baseWidth(), (float)rand() / RAND_MAX * g->baseHeight());
	}
	while (w->msgProc()) {
		if (w->active()) {
			indev->getState();
			mouseRect->setPos(VECTOR2(indev->value(MOUSE_X), indev->value(MOUSE_Y)));
			mousePoint->setPos(mouseRect->pos());
			mouseRectImage->setPos(mouseRect->pos());
			mouseCircle->setPos(mouseRect->pos());
			ds->set("mx:%d my:%d", indev->value(MOUSE_X), indev->value(MOUSE_Y));
			g->clearTarget(COLOR(0.4f, 0.4f, 0.4f, 1.0f));
			ds->set("%f", t);

			for (auto& i : boxs) {
				VECTOR2 norm;
				if (Calc2DStaticCircleAndRectExtrude(mouseCircle->pos(), mouseCircle->r(), i.Pos, i.Wh, norm)) {
					ds->set("boxHit");
					i.Pos += norm;
				}
			}
			for (auto& i : boxs) {
				i.update();
			}
			SHADER* shader = Image2dCameraShader;
			MATRIX cameraWorld;
			cameraWorld.identity();
			Image2dCameraShader->setCameraWorld(cameraWorld);
			BEGIN_PATH_


				END_PATH_
				drawerManager->draw();
			//c->texture("backBox")->draw(Image2dShader,VECTOR2(1.0f,1.0f));
			g->present();
		}
	}
	delete mousePoint;
	delete Image2dCameraShader;
	delete c;
	delete drawerManager;
}
#endif
//フォント
#if(0)
void DebugRun() {
	WINDOW* w = WINDOW::instance();
	INDEV* indev = INDEV::instance();

	DEBUG_STR* ds = DEBUG_STR::instance();
	CONTAINER* c = new CONTAINER("MenuIcon.txt");
	IMAGE_2D* Image2dShader = new IMAGE_2D();
	IMAGE2D_CAMERA* Image2dCameraShader = new IMAGE2D_CAMERA();
	DRAWER::MANAGER* drawerManager = new DRAWER::MANAGER();
	DRAWER::DRAWERS* drawers = new DRAWER::DRAWERS();
	drawers->setShader(Image2dShader);
	std::array<DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT, 1> layout = {
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("ui", drawers)
	};
	DRAWER::DRAWERS_LIST* drawersList = new DRAWER::DRAWERS_LIST();
	drawersList->create(layout);
	drawerManager->create(drawersList);
	{
		struct DebugDrawer {
			void draw(SHADER* shader) {
				Ds->draw(shader);
			};
			DEBUG_STR* Ds = nullptr;
		};
		DebugDrawer* debugDrawer = new DebugDrawer;
		debugDrawer->Ds = ds;
		auto image = new DRAWER::SAUCER(debugDrawer);
		drawerManager->drawerAdd("ui", image);
	}
	std::string str;
	GRAPHIC* g = GRAPHIC::instance();
	float t = 0.0f;
	//マウスの判定
	COLLISION2D_POINT* mousePoint = new COLLISION2D_POINT;
	COLLISION2D_RECT* mouseRect = new COLLISION2D_RECT;
	mouseRect->setWh(c->texture("minusIcon")->wh());
	DRAWER::IMAGE2D* mouseRectImage = new DRAWER::IMAGE2D;
	mouseRectImage->setPivot(DRAWER::IMAGE2D::drawMethodCentered());
	mouseRectImage->setTexture(c->texture("minusIcon"));
	mouseRectImage->setPivot(DRAWER::IMAGE2D::drawMethodInvisible());
	drawerManager->drawerAdd("ui", mouseRectImage);
	COLLISION2D_CIRCLE* mouseCircle = new COLLISION2D_CIRCLE;
	mouseCircle->setR(c->texture("minusIcon")->width() * 0.5f);




	//UIレイアウト
	std::vector<UI*> Childs;
	std::vector<UI*> Childs1;
	Childs1.push_back(UI::create(c->texture("plusIcon"), VECTOR2(50, 50),VECTOR2::one()));
	Childs1.push_back(UI::create(c->texture("plusIcon"), VECTOR2(60, 60), VECTOR2::one()));
	Childs.push_back(UI::create(c->texture("plusIcon"), VECTOR2(100, 100), VECTOR2::one(),std::move(Childs1)));
	{
		UI* fontUi = new UI;
		DRAWER::FONT* font = new DRAWER::FONT;
		font->create("Assets/font/PixelMplus12-Bold.ttf", "PixelMplus12", "あぃｶｷｸｹｺいうえお", 64);
		font->setScale(VECTOR2(1.0f, 1.0f));
		font->setPos(VECTOR2(500.0f, 500.0f));
		font->setMaxWidth(500.0f);
		font->setDrawMethod(DRAWER::FONT::drawMethodAdjustDraw_Over());
		fontUi->create(font, std::move(std::vector<UI*>()));
		Childs.push_back(fontUi);
	}
	{
		UI* fontUi = new UI;
		DRAWER::FONT* font = new DRAWER::FONT;
		font->create("Assets/font/PixelMplus12-Bold.ttf", "PixelMplus12", "あぃｶｷｸｹｺいうえお", 64);
		font->setScale(VECTOR2(1.0f, 1.0f));
		font->setPos(VECTOR2(500.0f, 500.0f));
		font->setMaxWidth(128.0f);
		font->setDrawMethod(DRAWER::FONT::drawMethodDefault());
		fontUi->create(font, std::move(std::vector<UI*>()));
		Childs.push_back(fontUi);
	}
	UI* UiRoot = UI::create(c->texture("plusIcon"), VECTOR2(200, 200), VECTOR2::one(), std::move(Childs));
	//UiRoot->execute([](UI* ui)->void{ui->setIsChildCollisionRestrict(true);});
	//ドラッグしているUI
	UI* choiceUi = nullptr;
	UI* choiceUiScale = nullptr;

	//FONT* libFont = new FONT;
	//libFont->addUserFont("Assets/font/02UtsukushiMincho.ttf", "02UtsukushiMincho");
	//libFont->create(FONT_SET_1, "?	弁	?	弃	弄	?	?	?	?	弉	弊	弋	弌	弍	?	式5F10	弐	弑	?	弓	弔	引	弖	弗	弘	?	?	弛	?	?	?	弟5F20	?	弡	?	?	?	弥	弦	弧	?	弩	?	?	?	弭	?	弯5F30	?	弱	?	?	弴	張	?	強	弸	?	?	?	弼	?	弾	?5F40	?	彁	?	?	?	彅	?	?	彈	?	彊	?	彌	?	彎	?",
	//	USER_FONT, 64);
	//libFont->releaseUserFont();

	while (w->msgProc()) {
		if (w->active()) {
			indev->getState();
			mouseRect->setPos(VECTOR2(indev->value(MOUSE_X), indev->value(MOUSE_Y)));
			mousePoint->setPos(mouseRect->pos());
			mouseRectImage->setPos(mouseRect->pos());
			mouseCircle->setPos(mouseRect->pos());
			ds->set("mx:%d my:%d", indev->value(MOUSE_X), indev->value(MOUSE_Y));
			g->clearTarget(COLOR(0.4f, 0.4f, 0.4f, 1.0f));
			ds->set("%f", t);
			
			UiRoot->exeOverlap(mousePoint);
			if (indev->isTrigger(MOUSE_LBUTTON)) {
				UI* overlapUi = nullptr;
				UiRoot->OverlapUi(mousePoint, overlapUi);
				if (overlapUi != nullptr) {
					choiceUi = overlapUi;
				}
			}
			if (indev->isUp(MOUSE_LBUTTON)) {
				choiceUi = nullptr;
			}
			if (choiceUi != nullptr) {
				choiceUi->setPos(choiceUi->pos() + VECTOR2(indev->relativeValue(MOUSE_X), indev->relativeValue(MOUSE_Y)) / choiceUi->parentScale());
			}

			if (indev->isTrigger(MOUSE_RBUTTON)) {
				UI* overlapUi = nullptr;
				UiRoot->OverlapUi(mousePoint, overlapUi);
				if (overlapUi != nullptr) {
					choiceUiScale = overlapUi;
				}
			}
			if (indev->isUp(MOUSE_RBUTTON)) {
				choiceUiScale = nullptr;
			}
			if (choiceUiScale != nullptr) {
				choiceUiScale->setScale(
					choiceUiScale->scale() + VECTOR2(indev->relativeValue(MOUSE_X), indev->relativeValue(MOUSE_Y)) / (choiceUiScale->drawer()->wh() * choiceUiScale->scale()) / choiceUiScale->parentScale());
			}


			SHADER* shader = Image2dShader;
			MATRIX cameraWorld;
			cameraWorld.identity();
			Image2dCameraShader->setCameraWorld(cameraWorld);
			BEGIN_PATH_
				UiRoot->draw(shader);
			END_PATH_
			drawerManager->draw();
			g->present();
		}
	}
	delete UiRoot;
	delete mousePoint;
	delete mouseCircle;
	delete mouseRect;
	delete Image2dShader;
	delete Image2dCameraShader;
	delete c;
	delete drawerManager;
}
#endif
//スクロール
#if(0)
void DebugRun() {
	WINDOW* w = WINDOW::instance();
	INDEV* indev = INDEV::instance();

	DEBUG_STR* ds = DEBUG_STR::instance();
	CONTAINER* c = new CONTAINER("AssetsOrigin/MenuIcon.txt");
	IMAGE_2D* Image2dShader = new IMAGE_2D();
	IMAGE2D_CAMERA* Image2dCameraShader = new IMAGE2D_CAMERA();
	DRAWER::MANAGER* drawerManager = new DRAWER::MANAGER();
	DRAWER::DRAWERS* drawers = new DRAWER::DRAWERS();
	drawers->setShader(Image2dShader);
	std::array<DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT, 1> layout = {
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("ui", drawers)
	};
	DRAWER::DRAWERS_LIST* drawersList = new DRAWER::DRAWERS_LIST();
	drawersList->create(layout);
	drawerManager->create(drawersList);
	{
		struct DebugDrawer {
			void draw(SHADER* shader) {
				Ds->draw(shader);
			};
			DEBUG_STR* Ds = nullptr;
		};
		DebugDrawer* debugDrawer = new DebugDrawer;
		debugDrawer->Ds = ds;
		auto image = new DRAWER::SAUCER(debugDrawer);
		drawerManager->drawerAdd("ui", image);
	}
	std::string str;
	GRAPHIC* g = GRAPHIC::instance();
	float t = 0.0f;
	//マウスの判定
	COLLISION2D_POINT* mousePoint = new COLLISION2D_POINT;
	COLLISION2D_RECT* mouseRect = new COLLISION2D_RECT;
	mouseRect->setWh(c->texture("minusIcon")->wh());
	DRAWER::IMAGE2D* mouseRectImage = new DRAWER::IMAGE2D;
	mouseRectImage->setPivot(DRAWER::IMAGE2D::drawMethodCentered());
	mouseRectImage->setTexture(c->texture("minusIcon"));
	mouseRectImage->setPivot(DRAWER::IMAGE2D::drawMethodInvisible());
	drawerManager->drawerAdd("ui", mouseRectImage);
	COLLISION2D_CIRCLE* mouseCircle = new COLLISION2D_CIRCLE;
	mouseCircle->setR(c->texture("minusIcon")->width() * 0.5f);



	UI_SCROLL* uiScroll = new UI_SCROLL;
	uiScroll->create(c, 8);
	//UIレイアウト
	UI* UiRoot = uiScroll->rootUi();
	//UiRoot->execute([](UI* ui)->void{ui->setIsChildCollisionRestrict(true);});
	//ドラッグしているUI
	UI* choiceUi = nullptr;
	UI* choiceUiScale = nullptr;

	//FONT* libFont = new FONT;
	//libFont->addUserFont("Assets/font/02UtsukushiMincho.ttf", "02UtsukushiMincho");
	//libFont->create(FONT_SET_1, "?	弁	?	弃	弄	?	?	?	?	弉	弊	弋	弌	弍	?	式5F10	弐	弑	?	弓	弔	引	弖	弗	弘	?	?	弛	?	?	?	弟5F20	?	弡	?	?	?	弥	弦	弧	?	弩	?	?	?	弭	?	弯5F30	?	弱	?	?	弴	張	?	強	弸	?	?	?	弼	?	弾	?5F40	?	彁	?	?	?	彅	?	?	彈	?	彊	?	彌	?	彎	?",
	//	USER_FONT, 64);
	//libFont->releaseUserFont();

	while (w->msgProc()) {
		if (w->active()) {
			indev->getState();
			mouseRect->setPos(VECTOR2(indev->value(MOUSE_X), indev->value(MOUSE_Y)));
			mousePoint->setPos(mouseRect->pos());
			mouseRectImage->setPos(mouseRect->pos());
			mouseCircle->setPos(mouseRect->pos());
			ds->set("mx:%d my:%d", indev->value(MOUSE_X), indev->value(MOUSE_Y));
			g->clearTarget(COLOR(0.4f, 0.4f, 0.4f, 1.0f));
			ds->set("%f", t);

			uiScroll->update();
			//if (indev->isTrigger(MOUSE_LBUTTON)) {
			//	UI* overlapUi = nullptr;
			//	UiRoot->OverlapUi(mousePoint, overlapUi);
			//	if (overlapUi != nullptr) {
			//		choiceUi = overlapUi;
			//	}
			//}
			//if (indev->isUp(MOUSE_LBUTTON)) {
			//	choiceUi = nullptr;
			//}
			//if (choiceUi != nullptr) {
			//	choiceUi->setPos(choiceUi->pos() + VECTOR2(indev->relativeValue(MOUSE_X), indev->relativeValue(MOUSE_Y)) / choiceUi->parentScale());
			//}

			//if (indev->isTrigger(MOUSE_RBUTTON)) {
			//	UI* overlapUi = nullptr;
			//	UiRoot->OverlapUi(mousePoint, overlapUi);
			//	if (overlapUi != nullptr) {
			//		choiceUiScale = overlapUi;
			//	}
			//}
			//if (indev->isUp(MOUSE_RBUTTON)) {
			//	choiceUiScale = nullptr;
			//}
			//if (choiceUiScale != nullptr) {
			//	choiceUiScale->setScale(
			//		choiceUiScale->scale() + VECTOR2(indev->relativeValue(MOUSE_X), indev->relativeValue(MOUSE_Y)) / (choiceUiScale->drawer()->wh() / choiceUiScale->scale()) / choiceUiScale->parentScale());
			//}


			SHADER* shader = Image2dShader;
			MATRIX cameraWorld;
			cameraWorld.identity();
			Image2dCameraShader->setCameraWorld(cameraWorld);
			BEGIN_PATH_
				UiRoot->draw(shader);
			END_PATH_
				drawerManager->draw();
			g->present();
		}
	}
	delete uiScroll;
	delete mousePoint;
	delete mouseCircle;
	delete mouseRect;
	delete Image2dShader;
	delete Image2dCameraShader;
	delete c;
	delete drawerManager;
}
#endif
//３ｄ
#if(0)
void DebugRun() {
	WINDOW* w = WINDOW::instance();
	GRAPHIC* g = GRAPHIC::instance();
	INDEV* indev = INDEV::instance();
	DEBUG_STR* ds = DEBUG_STR::instance();
	CONTAINER* c = new CONTAINER("AssetsOrigin/MenuIcon.txt");
	CONTAINER* cPrimitive = new CONTAINER("Assets/primitive/Assets.txt");
	//シェーダー
	IMAGE_2D* Image2dShader = new IMAGE_2D();
	SOFT_SHADOW* SoftShadowShader = new SOFT_SHADOW(2048, 2048);
	CAMERA_DEBUG* Camera = new CAMERA_DEBUG();
	Camera->setDistanceFromLookatPos(6.0f);

	//SothShadowShaderの行列情報
	MATRIX LightView;
	MATRIX LightProj;
	LightView.set(VECTOR3(10.0f, 20.0f, 3.0f), VECTOR3(0, 0, 0), VECTOR3(0, 1, 0));//ライトから見た頂点群に変換するマトリックス
	LightProj.setOrtho(30.0f, 30.0f, -1.0f, -20.0f);//正投影（見たまんま＝遠いものを小さくしない）マトリックス
	MATRIX Proj;
	MATRIX View;
	Proj.setPers(3.141592f / 3.0f, g->aspect(), -0.1f, -50.1f);
	// Light
	VECTOR3 LightPos = VECTOR3(0.0f, 10.0f, 0.01f);
	float Ambient = 1.0f;
	COLOR Diffuse = COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// LightからのViewとProj
	LightView.set(LightPos, VECTOR3(0, 0, 0), VECTOR3(0, 1, 0));//ライトから見た頂点群に変換するマトリックス
	LightProj.setOrtho(10.0f, 10.0f, -1.0f, -20.0f);//正投影（見たまんま＝遠いものを小さくしない）マトリックス

	IMAGE2D_CAMERA* Image2dCameraShader = new IMAGE2D_CAMERA();

	DRAWER::MANAGER* drawerManager = new DRAWER::MANAGER();
	//2Dのレイヤー
	DRAWER::DRAWERS* drawers2d = new DRAWER::DRAWERS();
	drawers2d->setShader(Image2dShader);
	//3Dのレイヤー
	DRAWER::DRAWERS* drawers3d = new DRAWER::DRAWERS();
	drawers3d->setShader(SoftShadowShader);
	//レイヤーのレイアウト
	std::array<DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT, 2> layout = {
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("3d", drawers3d),
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("ui", drawers2d)
	};
	DRAWER::DRAWERS_LIST* drawersList = new DRAWER::DRAWERS_LIST();
	drawersList->create(layout);
	drawerManager->create(drawersList);
	{
		struct DebugDrawer {
			void draw(SHADER* shader) {
				Ds->draw(shader);
			};
			DEBUG_STR* Ds = nullptr;
		};
		DebugDrawer* debugDrawer = new DebugDrawer;
		debugDrawer->Ds = ds;
		auto image = new DRAWER::SAUCER(debugDrawer);
		drawerManager->drawerAdd("ui", image);
	}
	std::string str;
	float t = 0.0f;
	//マウスの判定
	COLLISION2D_POINT* mousePoint = new COLLISION2D_POINT;
	COLLISION2D_RECT* mouseRect = new COLLISION2D_RECT;
	mouseRect->setWh(c->texture("minusIcon")->wh());
	DRAWER::IMAGE2D* mouseRectImage = new DRAWER::IMAGE2D;
	mouseRectImage->setPivot(DRAWER::IMAGE2D::drawMethodCentered());
	mouseRectImage->setTexture(c->texture("minusIcon"));
	mouseRectImage->setPivot(DRAWER::IMAGE2D::drawMethodInvisible());
	drawerManager->drawerAdd("ui", mouseRectImage);
	COLLISION2D_CIRCLE* mouseCircle = new COLLISION2D_CIRCLE;
	mouseCircle->setR(c->texture("minusIcon")->width() * 0.5f);

	BATCH* box = cPrimitive->batch("PrimitiveBox");
	BATCH* cylinder = cPrimitive->batch("PrimitiveCylinder");
	{
		DRAWER::BATCH* drawerBatch = new DRAWER::BATCH;
		drawerBatch->setBatch(box);
		drawerManager->drawerAdd("3d", drawerBatch);
	}
	{
		DRAWER::BATCH* drawerBatch = new DRAWER::BATCH;
		drawerBatch->setBatch(cylinder);
		drawerManager->drawerAdd("3d", drawerBatch);
	}


	UI_SCROLL* uiScroll = new UI_SCROLL;
	uiScroll->create(c, 8);
	//UIレイアウト
	UI* UiRoot = uiScroll->rootUi();
	//UiRoot->execute([](UI* ui)->void{ui->setIsChildCollisionRestrict(true);});
	//ドラッグしているUI
	UI* choiceUi = nullptr;
	UI* choiceUiScale = nullptr;

	//FONT* libFont = new FONT;
	//libFont->addUserFont("Assets/font/02UtsukushiMincho.ttf", "02UtsukushiMincho");
	//libFont->create(FONT_SET_1, "?	弁	?	弃	弄	?	?	?	?	弉	弊	弋	弌	弍	?	式5F10	弐	弑	?	弓	弔	引	弖	弗	弘	?	?	弛	?	?	?	弟5F20	?	弡	?	?	?	弥	弦	弧	?	弩	?	?	?	弭	?	弯5F30	?	弱	?	?	弴	張	?	強	弸	?	?	?	弼	?	弾	?5F40	?	彁	?	?	?	彅	?	?	彈	?	彊	?	彌	?	彎	?",
	//	USER_FONT, 64);
	//libFont->releaseUserFont();

	while (w->msgProc()) {
		if (w->active()) {
			indev->getState();
			mouseRect->setPos(VECTOR2(indev->value(MOUSE_X), indev->value(MOUSE_Y)));
			mousePoint->setPos(mouseRect->pos());
			mouseRectImage->setPos(mouseRect->pos());
			mouseCircle->setPos(mouseRect->pos());
			ds->set("mx:%d my:%d", indev->value(MOUSE_X), indev->value(MOUSE_Y));
			g->clearTarget(COLOR(0.4f, 0.4f, 0.4f, 1.0f));
			ds->set("%f", t);

			uiScroll->update();
			if (indev->isTrigger(MOUSE_LBUTTON)) {
				UI* overlapUi = nullptr;
				UiRoot->OverlapUi(mousePoint, overlapUi);
				if (overlapUi != nullptr) {
					choiceUi = overlapUi;
				}
			}
			if (indev->isUp(MOUSE_LBUTTON)) {
				choiceUi = nullptr;
			}
			if (choiceUi != nullptr) {
				choiceUi->setPos(choiceUi->pos() + VECTOR2(indev->relativeValue(MOUSE_X), indev->relativeValue(MOUSE_Y)) / choiceUi->parentScale());
			}

			if (indev->isTrigger(MOUSE_RBUTTON)) {
				UI* overlapUi = nullptr;
				UiRoot->OverlapUi(mousePoint, overlapUi);
				if (overlapUi != nullptr) {
					choiceUiScale = overlapUi;
				}
			}
			if (indev->isUp(MOUSE_RBUTTON)) {
				choiceUiScale = nullptr;
			}
			if (choiceUiScale != nullptr) {
				choiceUiScale->setScale(
					choiceUiScale->scale() + VECTOR2(indev->relativeValue(MOUSE_X), indev->relativeValue(MOUSE_Y)) / (choiceUiScale->drawer()->wh() / choiceUiScale->scale()) / choiceUiScale->parentScale());
			}

			SHADER* shader = Image2dShader;
			MATRIX cameraWorld;
			cameraWorld.identity();
			Image2dCameraShader->setCameraWorld(cameraWorld);
				shader = SoftShadowShader;
			Camera->update(&View,VECTOR3(),0.0f);
			SoftShadowShader->setLightPosition(LightPos);
			SoftShadowShader->setLightAmbient(Ambient);
			SoftShadowShader->setDiffuse(Diffuse);
			SoftShadowShader->setProjView(Proj* View);
			SoftShadowShader->setLight_ProjView(LightProj* LightView);
			drawerManager->draw();
			shader = Image2dShader;
			BEGIN_PATH_
				UiRoot->draw(shader);
			END_PATH_
			g->present();
		}
	}
	delete cPrimitive;
	delete Camera;
	delete SoftShadowShader;
	delete uiScroll;
	delete mousePoint;
	delete mouseCircle;
	delete mouseRect;
	delete Image2dShader;
	delete Image2dCameraShader;
	delete c;
	delete drawerManager;
}
#endif
//IMM
#if(0)
void DebugRun() {
	WINDOW* w = WINDOW::instance();
	INDEV* indev = INDEV::instance();
	DEBUG_STR* ds = DEBUG_STR::instance();
	CONTAINER* c = new CONTAINER("AssetsOrigin/MenuIcon.txt");
	IMAGE_2D* Image2dShader = new IMAGE_2D();
	IMAGE2D_CAMERA* Image2dCameraShader = new IMAGE2D_CAMERA();
	DRAWER::MANAGER* drawerManager = new DRAWER::MANAGER();
	DRAWER::DRAWERS* drawers = new DRAWER::DRAWERS();
	drawers->setShader(Image2dShader);
	std::array<DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT, 1> layout = {
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("ui", drawers)
	};
	DRAWER::DRAWERS_LIST* drawersList = new DRAWER::DRAWERS_LIST();
	drawersList->create(layout);
	drawerManager->create(drawersList);
	{
		struct DebugDrawer {
			void draw(SHADER* shader) {
				Ds->draw(shader);
			};
			DEBUG_STR* Ds = nullptr;
		};
		DebugDrawer* debugDrawer = new DebugDrawer;
		debugDrawer->Ds = ds;
		auto image = new DRAWER::SAUCER(debugDrawer);
		drawerManager->drawerAdd("ui", image);
	}
	std::string str;
	GRAPHIC* g = GRAPHIC::instance();
	float t = 0.0f;
	//マウスの判定
	COLLISION2D_POINT* mousePoint = new COLLISION2D_POINT;
	COLLISION2D_RECT* mouseRect = new COLLISION2D_RECT;
	mouseRect->setWh(c->texture("minusIcon")->wh());
	DRAWER::IMAGE2D* mouseRectImage = new DRAWER::IMAGE2D;
	mouseRectImage->setPivot(DRAWER::IMAGE2D::drawMethodCentered());
	mouseRectImage->setTexture(c->texture("minusIcon"));
	mouseRectImage->setPivot(DRAWER::IMAGE2D::drawMethodInvisible());
	drawerManager->drawerAdd("ui", mouseRectImage);
	COLLISION2D_CIRCLE* mouseCircle = new COLLISION2D_CIRCLE;
	mouseCircle->setR(c->texture("minusIcon")->width() * 0.5f);



	UI_SCROLL* uiScroll = new UI_SCROLL;
	uiScroll->create(c, 8);
	//UIレイアウト
	UI* UiRoot = uiScroll->rootUi();
	//UiRoot->execute([](UI* ui)->void{ui->setIsChildCollisionRestrict(true);});
	//ドラッグしているUI
	UI* choiceUi = nullptr;
	UI* choiceUiScale = nullptr;

	//FONT* libFont = new FONT;
	//libFont->addUserFont("Assets/font/02UtsukushiMincho.ttf", "02UtsukushiMincho");
	//libFont->create(FONT_SET_1, "?	弁	?	弃	弄	?	?	?	?	弉	弊	弋	弌	弍	?	式5F10	弐	弑	?	弓	弔	引	弖	弗	弘	?	?	弛	?	?	?	弟5F20	?	弡	?	?	?	弥	弦	弧	?	弩	?	?	?	弭	?	弯5F30	?	弱	?	?	弴	張	?	強	弸	?	?	?	弼	?	弾	?5F40	?	彁	?	?	?	彅	?	?	彈	?	彊	?	彌	?	彎	?",
	//	USER_FONT, 64);
	//libFont->releaseUserFont();
	while (w->msgProc()) {
		if (w->active()) {
			indev->getState();
			mouseRect->setPos(VECTOR2(indev->value(MOUSE_X), indev->value(MOUSE_Y)));
			mousePoint->setPos(mouseRect->pos());
			mouseRectImage->setPos(mouseRect->pos());
			mouseCircle->setPos(mouseRect->pos());
			ds->set("mx:%d my:%d", indev->value(MOUSE_X), indev->value(MOUSE_Y));
			g->clearTarget(COLOR(0.4f, 0.4f, 0.4f, 1.0f));
			ds->set("%f", t);
			HIMC hImc = ImmGetContext(FindWindow(CLASS_NAME, 0));
			//hImc = ImmGetContext(GetDesktopWindow());
			char szBuf[1024] = { 0 }, szStr[1024] = {0};
			ImmGetCompositionString(hImc, GCS_COMPSTR, szBuf, 1024);
			DWORD dwSize = ImmGetCandidateList(hImc, 0, NULL, 0);
			//if (dwSize > 0) { MessageBox(NULL, "dwSize", "", MB_OK); }
			tagCANDIDATELIST tcdl[1024] = {0};
			LPCANDIDATELIST lpcdl = tcdl;
			ImmGetCandidateList(hImc, 0, lpcdl, dwSize);
			char szCandidate[256] = { 0 };
			strcpy(szCandidate, (char*)lpcdl + lpcdl->dwOffset[lpcdl->dwSelection]);
			DRAWER::FONT* immDrawer = new DRAWER::FONT(); 
			if (*szCandidate == '\0') { strcpy(szCandidate, "none"); }
			immDrawer->create("Assets/font/PixelMplus12-Bold.ttf", "PixelMplus12", szBuf, 64);
			immDrawer->setScale(VECTOR2(1.0f, 1.0f));
			immDrawer->setPos(VECTOR2(600.0f,600.0f));
			immDrawer->setMaxWidth(256.0f);
			immDrawer->setDrawMethod(DRAWER::FONT::drawMethodAdjustDraw_Over());
			uiScroll->update();
			//if (indev->isTrigger(MOUSE_LBUTTON)) {
			//	UI* overlapUi = nullptr;
			//	UiRoot->OverlapUi(mousePoint, overlapUi);
			//	if (overlapUi != nullptr) {
			//		choiceUi = overlapUi;
			//	}
			//}
			//if (indev->isUp(MOUSE_LBUTTON)) {
			//	choiceUi = nullptr;
			//}
			//if (choiceUi != nullptr) {
			//	choiceUi->setPos(choiceUi->pos() + VECTOR2(indev->relativeValue(MOUSE_X), indev->relativeValue(MOUSE_Y)) / choiceUi->parentScale());
			//}

			//if (indev->isTrigger(MOUSE_RBUTTON)) {
			//	UI* overlapUi = nullptr;
			//	UiRoot->OverlapUi(mousePoint, overlapUi);
			//	if (overlapUi != nullptr) {
			//		choiceUiScale = overlapUi;
			//	}
			//}
			//if (indev->isUp(MOUSE_RBUTTON)) {
			//	choiceUiScale = nullptr;
			//}
			//if (choiceUiScale != nullptr) {
			//	choiceUiScale->setScale(
			//		choiceUiScale->scale() + VECTOR2(indev->relativeValue(MOUSE_X), indev->relativeValue(MOUSE_Y)) / (choiceUiScale->drawer()->wh() / choiceUiScale->scale()) / choiceUiScale->parentScale());
			//}


			SHADER* shader = Image2dShader;
			MATRIX cameraWorld;
			cameraWorld.identity();
			Image2dCameraShader->setCameraWorld(cameraWorld);
			BEGIN_PATH_
				//UiRoot->draw(shader);
				immDrawer->draw(shader);
				delete immDrawer;
			END_PATH_
				drawerManager->draw();
			g->present();
		}
	}
	delete uiScroll;
	delete mousePoint;
	delete mouseCircle;
	delete mouseRect;
	delete Image2dShader;
	delete Image2dCameraShader;
	delete c;
	delete drawerManager;
}
#endif
//STATIC_FONT
#if(0)
void DebugRun() {
	WINDOW* w = WINDOW::instance();
	INDEV* indev = INDEV::instance();

	DEBUG_STR* ds = DEBUG_STR::instance();
	CONTAINER* c = new CONTAINER("AssetsOrigin/MenuIcon.txt");
	STATIC_FONT* StaticFont = new STATIC_FONT(64, "Assets/font/PixelMplus12-Regular.ttf", "PixelMplus12","ｽﾀﾃｨｯｸ");
	IMAGE_2D* Image2dShader = new IMAGE_2D();
	IMAGE2D_CAMERA* Image2dCameraShader = new IMAGE2D_CAMERA();
	DRAWER::MANAGER* drawerManager = new DRAWER::MANAGER();
	DRAWER::DRAWERS* drawers = new DRAWER::DRAWERS();
	drawers->setShader(Image2dShader);
	std::array<DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT, 1> layout = {
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("ui", drawers)
	};
	DRAWER::DRAWERS_LIST* drawersList = new DRAWER::DRAWERS_LIST();
	drawersList->create(layout);
	drawerManager->create(drawersList);
	{
		struct DebugDrawer {
			void draw(SHADER* shader) {
				Ds->draw(shader);
			};
			DEBUG_STR* Ds = nullptr;
		};
		DebugDrawer* debugDrawer = new DebugDrawer;
		debugDrawer->Ds = ds;
		auto image = new DRAWER::SAUCER(debugDrawer);
		drawerManager->drawerAdd("ui", image);
	}
	std::string str;
	GRAPHIC* g = GRAPHIC::instance();
	float t = 0.0f;
	//マウスの判定
	COLLISION2D_POINT* mousePoint = new COLLISION2D_POINT;
	COLLISION2D_RECT* mouseRect = new COLLISION2D_RECT;
	mouseRect->setWh(c->texture("minusIcon")->wh());
	DRAWER::IMAGE2D* mouseRectImage = new DRAWER::IMAGE2D;
	mouseRectImage->setPivot(DRAWER::IMAGE2D::drawMethodCentered());
	mouseRectImage->setTexture(c->texture("minusIcon"));
	mouseRectImage->setPivot(DRAWER::IMAGE2D::drawMethodInvisible());
	drawerManager->drawerAdd("ui", mouseRectImage);
	COLLISION2D_CIRCLE* mouseCircle = new COLLISION2D_CIRCLE;
	mouseCircle->setR(c->texture("minusIcon")->width() * 0.5f);



	UI_SCROLL* uiScroll = new UI_SCROLL;
	uiScroll->create(c, 8);
	//UIレイアウト
	UI* UiRoot = uiScroll->rootUi();
	//UiRoot->execute([](UI* ui)->void{ui->setIsChildCollisionRestrict(true);});
	//ドラッグしているUI
	UI* choiceUi = nullptr;
	UI* choiceUiScale = nullptr;

	//FONT* libFont = new FONT;
	//libFont->addUserFont("Assets/font/02UtsukushiMincho.ttf", "02UtsukushiMincho");
	//libFont->create(FONT_SET_1, "?	弁	?	弃	弄	?	?	?	?	弉	弊	弋	弌	弍	?	式5F10	弐	弑	?	弓	弔	引	弖	弗	弘	?	?	弛	?	?	?	弟5F20	?	弡	?	?	?	弥	弦	弧	?	弩	?	?	?	弭	?	弯5F30	?	弱	?	?	弴	張	?	強	弸	?	?	?	弼	?	弾	?5F40	?	彁	?	?	?	彅	?	?	彈	?	彊	?	彌	?	彎	?",
	//	USER_FONT, 64);
	//libFont->releaseUserFont();
	char szBuf[1024] = { 0 };
	std::string inputString;
	while (w->msgProc()) {
		if (w->active()) {
			indev->getState();
			mouseRect->setPos(VECTOR2(indev->value(MOUSE_X), indev->value(MOUSE_Y)));
			mousePoint->setPos(mouseRect->pos());
			mouseRectImage->setPos(mouseRect->pos());
			mouseCircle->setPos(mouseRect->pos());
			ds->set("mx:%d my:%d", indev->value(MOUSE_X), indev->value(MOUSE_Y));
			g->clearTarget(COLOR(0.4f, 0.4f, 0.4f, 1.0f));
			ds->set("%f", t);
			if (indev->isTrigger(KEY_ENTER)) {
				inputString += szBuf;
			}
			HIMC hImc = ImmGetContext(FindWindow(CLASS_NAME, 0));
			//hImc = ImmGetContext(GetDesktopWindow());
			memset(szBuf, 0, sizeof(szBuf));
			ImmGetCompositionString(hImc, GCS_COMPSTR, szBuf, 1024);

			//DRAWER::FONT* immDrawer = new DRAWER::FONT();
			//if (*szCandidate == '\0') { strcpy(szCandidate, "none"); }
			//immDrawer->create("Assets/font/PixelMplus12-Bold.ttf", "PixelMplus12", szBuf, 64);
			//immDrawer->setScale(VECTOR2(1.0f, 1.0f));
			//immDrawer->setPos(VECTOR2(600.0f, 600.0f));
			//immDrawer->setMaxWidth(256.0f);
			//immDrawer->setDrawMethod(DRAWER::FONT::drawMethodAdjustDraw_Over());
			uiScroll->update();
			//if (indev->isTrigger(MOUSE_LBUTTON)) {
			//	UI* overlapUi = nullptr;
			//	UiRoot->OverlapUi(mousePoint, overlapUi);
			//	if (overlapUi != nullptr) {
			//		choiceUi = overlapUi;
			//	}
			//}
			//if (indev->isUp(MOUSE_LBUTTON)) {
			//	choiceUi = nullptr;
			//}
			//if (choiceUi != nullptr) {
			//	choiceUi->setPos(choiceUi->pos() + VECTOR2(indev->relativeValue(MOUSE_X), indev->relativeValue(MOUSE_Y)) / choiceUi->parentScale());
			//}

			//if (indev->isTrigger(MOUSE_RBUTTON)) {
			//	UI* overlapUi = nullptr;
			//	UiRoot->OverlapUi(mousePoint, overlapUi);
			//	if (overlapUi != nullptr) {
			//		choiceUiScale = overlapUi;
			//	}
			//}
			//if (indev->isUp(MOUSE_RBUTTON)) {
			//	choiceUiScale = nullptr;
			//}
			//if (choiceUiScale != nullptr) {
			//	choiceUiScale->setScale(
			//		choiceUiScale->scale() + VECTOR2(indev->relativeValue(MOUSE_X), indev->relativeValue(MOUSE_Y)) / (choiceUiScale->drawer()->wh() / choiceUiScale->scale()) / choiceUiScale->parentScale());
			//}


			SHADER* shader = Image2dShader;
			MATRIX cameraWorld;
			cameraWorld.identity();
			Image2dCameraShader->setCameraWorld(cameraWorld);
			BEGIN_PATH_
				UiRoot->draw(shader);
				//immDrawer->draw(shader);
				//delete immDrawer;
				StaticFont->draw(shader, (inputString+ szBuf).c_str(), VECTOR2(200, 500));
				StaticFont->draw(shader, (inputString + szBuf).c_str(),VECTOR2(200, 600),VECTOR2(32,32));
				StaticFont->adjustDraw_Over(shader, (inputString + szBuf).c_str(), 8, VECTOR2(200, 700), VECTOR2(32, 32));
			END_PATH_
				drawerManager->draw();
			g->present();
		}
	}
	delete StaticFont;
	delete uiScroll;
	delete mousePoint;
	delete mouseCircle;
	delete mouseRect;
	delete Image2dShader;
	delete Image2dCameraShader;
	delete c;
	delete drawerManager;
}
#endif
//キーボード
#if(0)
void DebugRun() {
	WINDOW* w = WINDOW::instance();
	INDEV* indev = INDEV::instance();
	DEBUG_STR* ds = DEBUG_STR::instance();
	CONTAINER* c = new CONTAINER("AssetsOrigin/MenuIcon.txt");
	//STATIC_FONT* StaticFont = new STATIC_FONT(64, "Assets/font/PixelMplus12-Regular.ttf", "PixelMplus12", "ｽﾀﾃｨｯｸ");
	STATIC_FONT* StaticFont = new STATIC_FONT(64, "Assets/font/APJapanesefontT.ttf", "APJapanesefontT", "ｽﾀﾃｨｯｸ");
	IMAGE_2D* Image2dShader = new IMAGE_2D();
	IMAGE2D_CAMERA* Image2dCameraShader = new IMAGE2D_CAMERA();
	DRAWER::MANAGER* drawerManager = new DRAWER::MANAGER();
	DRAWER::DRAWERS* drawers = new DRAWER::DRAWERS();
	drawers->setShader(Image2dShader);
	std::array<DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT, 1> layout = {
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("ui", drawers)
	};
	DRAWER::DRAWERS_LIST* drawersList = new DRAWER::DRAWERS_LIST();
	drawersList->create(layout);
	drawerManager->create(drawersList);
	{
		struct DebugDrawer {
			void draw(SHADER* shader) {
				Ds->draw(shader);
			};
			DEBUG_STR* Ds = nullptr;
		};
		DebugDrawer* debugDrawer = new DebugDrawer;
		debugDrawer->Ds = ds;
		auto image = new DRAWER::SAUCER(debugDrawer);
		drawerManager->drawerAdd("ui", image);
	}
	std::string str;
	GRAPHIC* g = GRAPHIC::instance();
	float t = 0.0f;
	//マウスの判定
	COLLISION2D_POINT* mousePoint = new COLLISION2D_POINT;
	COLLISION2D_RECT* mouseRect = new COLLISION2D_RECT;
	mouseRect->setWh(c->texture("minusIcon")->wh());
	DRAWER::IMAGE2D* mouseRectImage = new DRAWER::IMAGE2D;
	mouseRectImage->setPivot(DRAWER::IMAGE2D::drawMethodCentered());
	mouseRectImage->setTexture(c->texture("minusIcon"));
	mouseRectImage->setPivot(DRAWER::IMAGE2D::drawMethodInvisible());
	drawerManager->drawerAdd("ui", mouseRectImage);
	COLLISION2D_CIRCLE* mouseCircle = new COLLISION2D_CIRCLE;
	mouseCircle->setR(c->texture("minusIcon")->width() * 0.5f);


	UI_SCROLL* uiScroll = new UI_SCROLL();
	uiScroll->create(c, 5);
	UI_KEYBOARD* uiKeyboad = new UI_KEYBOARD(c,StaticFont);
	PROCESS_NODE* processNode = new PROCESS_NODE(c, StaticFont);
	//UIレイアウト
	UI* UiRoot = uiKeyboad->rootUi();
	//UI_MANAGER uiManager(processNode->rootUi());
	UI_MANAGER uiManager(UiRoot);
	//UiRoot->execute([](UI* ui)->void{ui->setIsChildCollisionRestrict(true);});
	//ドラッグしているUI
	UI* choiceUi = nullptr;
	UI* choiceUiScale = nullptr;

	//FONT* libFont = new FONT;
	//libFont->addUserFont("Assets/font/02UtsukushiMincho.ttf", "02UtsukushiMincho");
	//libFont->create(FONT_SET_1, "?	弁	?	弃	弄	?	?	?	?	弉	弊	弋	弌	弍	?	式5F10	弐	弑	?	弓	弔	引	弖	弗	弘	?	?	弛	?	?	?	弟5F20	?	弡	?	?	?	弥	弦	弧	?	弩	?	?	?	弭	?	弯5F30	?	弱	?	?	弴	張	?	強	弸	?	?	?	弼	?	弾	?5F40	?	彁	?	?	?	彅	?	?	彈	?	彊	?	彌	?	彎	?",
	//	USER_FONT, 64);
	//libFont->releaseUserFont();
	char szBuf[1024] = { 0 };
	std::string inputString;
	while (w->msgProc()) {
		if (w->active()) {
			indev->getState();
			mouseRect->setPos(VECTOR2((float)indev->value(MOUSE_X), (float)indev->value(MOUSE_Y)));
			mousePoint->setPos(mouseRect->pos());
			mouseRectImage->setPos(mouseRect->pos());
			mouseCircle->setPos(mouseRect->pos());
			ds->set("mx:%d my:%d", indev->value(MOUSE_X), indev->value(MOUSE_Y));
			g->clearTarget(COLOR(0.4f, 0.4f, 0.4f, 1.0f));
			ds->set("%f", t);
			if (indev->isTrigger(KEY_ENTER)) {
				inputString += szBuf;
			}
			HIMC hImc = ImmGetContext(FindWindow(CLASS_NAME, 0));
			//hImc = ImmGetContext(GetDesktopWindow());
			memset(szBuf, 0, sizeof(szBuf));
			ImmGetCompositionString(hImc, GCS_COMPSTR, szBuf, 1024);

			//DRAWER::FONT* immDrawer = new DRAWER::FONT();
			//if (*szCandidate == '\0') { strcpy(szCandidate, "none"); }
			//immDrawer->create("Assets/font/PixelMplus12-Bold.ttf", "PixelMplus12", szBuf, 64);
			//immDrawer->setScale(VECTOR2(1.0f, 1.0f));
			//immDrawer->setPos(VECTOR2(600.0f, 600.0f));
			//immDrawer->setMaxWidth(256.0f);
			//immDrawer->setDrawMethod(DRAWER::FONT::drawMethodAdjustDraw_Over());
			uiManager.update();
			uiScroll->update();
			//if (indev->isTrigger(MOUSE_LBUTTON)) {
			//	UI* overlapUi = nullptr;
			//	UiRoot->OverlapUi(mousePoint, overlapUi);
			//	if (overlapUi != nullptr) {
			//		choiceUi = overlapUi;
			//	}
			//}
			//if (indev->isUp(MOUSE_LBUTTON)) {
			//	choiceUi = nullptr;
			//}
			//if (choiceUi != nullptr) {
			//	choiceUi->setPos(choiceUi->pos() + VECTOR2(indev->relativeValue(MOUSE_X), indev->relativeValue(MOUSE_Y)) / choiceUi->parentScale());
			//}
			//if (indev->isTrigger(MOUSE_RBUTTON)) {
			//	UI* overlapUi = nullptr;
			//	UiRoot->OverlapUi(mousePoint, overlapUi);
			//	if (overlapUi != nullptr) {
			//		choiceUiScale = overlapUi;
			//	}
			//}
			//if (indev->isUp(MOUSE_RBUTTON)) {
			//	choiceUiScale = nullptr;
			//}
			//if (choiceUiScale != nullptr) {
			//	choiceUiScale->setScale(
			//		choiceUiScale->scale() + VECTOR2(indev->relativeValue(MOUSE_X), indev->relativeValue(MOUSE_Y)) / (choiceUiScale->scale()) / choiceUiScale->parentScale());
			//}


			SHADER* shader = Image2dShader;
			MATRIX cameraWorld;
			cameraWorld.identity();
			Image2dCameraShader->setCameraWorld(cameraWorld);
			BEGIN_PATH_
				UiRoot->draw(shader);
				processNode->rootUi()->draw(shader);
				uiScroll->draw(shader);
			//immDrawer->draw(shader);
			//delete immDrawer;
			StaticFont->draw(shader, (inputString + szBuf).c_str(), VECTOR2(200, 500));
			StaticFont->draw(shader, uiKeyboad->inputString().c_str(), VECTOR2(200, 600), VECTOR2(32, 32));
			StaticFont->adjustDraw_Over(shader, (inputString + szBuf).c_str(), 8, VECTOR2(200, 700), VECTOR2(32, 32));
			END_PATH_
				drawerManager->draw();
			g->present();
		}
	}
	delete uiScroll;
	delete processNode;
	delete StaticFont;
	delete uiKeyboad;
	delete mousePoint;
	delete mouseCircle;
	delete mouseRect;
	delete Image2dShader;
	delete Image2dCameraShader;
	delete c;
	delete drawerManager;
}
#endif

//ノードとその他ウインドウ
#if(0)
void DebugRun() {
	WINDOW* w = WINDOW::instance();
	INDEV* indev = INDEV::instance();
	DEBUG_STR* ds = DEBUG_STR::instance();
	CONTAINER* c = new CONTAINER("AssetsOrigin/MenuIcon.txt");
	//STATIC_FONT* StaticFont = new STATIC_FONT(64, "Assets/font/PixelMplus12-Regular.ttf", "PixelMplus12", "ｽﾀﾃｨｯｸ");
	STATIC_FONT* StaticFont = new STATIC_FONT(64, "Assets/font/APJapanesefontT.ttf", "APJapanesefontT", "ｽﾀﾃｨｯｸ");
	IMAGE_2D* Image2dShader = new IMAGE_2D();
	IMAGE2D_CAMERA* Image2dCameraShader = new IMAGE2D_CAMERA();
	DRAWER::MANAGER* drawerManager = new DRAWER::MANAGER();
	DRAWER::DRAWERS* drawers = new DRAWER::DRAWERS();
	drawers->setShader(Image2dShader);
	DRAWER::DRAWERS* processNodeLineDrawers = new DRAWER::DRAWERS();
	processNodeLineDrawers->setShader(Image2dShader);
	DRAWER::DRAWERS* processNodeSelectField = new DRAWER::DRAWERS();
	processNodeSelectField->setShader(Image2dShader);
	DRAWER::DRAWERS* processNodeSelectRangeField = new DRAWER::DRAWERS();
	processNodeSelectRangeField->setShader(Image2dShader);

	std::array<DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT, 4> layout = {
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("ui", drawers),
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("processNodeLine", processNodeLineDrawers),
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("processNodeSelectField", processNodeSelectField),
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("processNodeSelectRangeField", processNodeSelectRangeField)
	};
	DRAWER::DRAWERS_LIST* drawersList = new DRAWER::DRAWERS_LIST();
	drawersList->create(layout);
	drawerManager->create(drawersList);
	
	struct DebugDrawer {
		void draw(SHADER* shader) {
			Ds->draw(shader);
		};
		DEBUG_STR* Ds = nullptr;
	};
	DebugDrawer* debugDrawer = new DebugDrawer;
	{
		debugDrawer->Ds = ds;
		auto image = new DRAWER::SAUCER(debugDrawer);
		drawerManager->drawerAdd("ui", image);
	}
	std::string str;
	GRAPHIC* g = GRAPHIC::instance();
	float t = 0.0f;
	//マウスの判定
	COLLISION2D_POINT* mousePoint = new COLLISION2D_POINT;
	COLLISION2D_RECT* mouseRect = new COLLISION2D_RECT;
	mouseRect->setWh(c->texture("minusIcon")->wh());
	DRAWER::IMAGE2D* mouseRectImage = new DRAWER::IMAGE2D;
	mouseRectImage->setPivot(DRAWER::IMAGE2D::drawMethodCentered());
	mouseRectImage->setTexture(c->texture("minusIcon"));
	mouseRectImage->setPivot(DRAWER::IMAGE2D::drawMethodInvisible());
	drawerManager->drawerAdd("ui", mouseRectImage);
	COLLISION2D_CIRCLE* mouseCircle = new COLLISION2D_CIRCLE;
	mouseCircle->setR(c->texture("minusIcon")->width() * 0.5f);

	PROCESS_NODE_MANAGER* ProcessNodeManager = new PROCESS_NODE_MANAGER(c, StaticFont, drawersList);
	//UIレイアウト
	UI* UiRoot = ProcessNodeManager->rootUi();
	//UI_MANAGER uiManager(processNode->rootUi());
	UI_MANAGER uiManager(UiRoot);
	//UiRoot->execute([](UI* ui)->void{ui->setIsChildCollisionRestrict(true);});

	//FONT* libFont = new FONT;
	//libFont->addUserFont("Assets/font/02UtsukushiMincho.ttf", "02UtsukushiMincho");
	//libFont->create(FONT_SET_1, "?	弁	?	弃	弄	?	?	?	?	弉	弊	弋	弌	弍	?	式5F10	弐	弑	?	弓	弔	引	弖	弗	弘	?	?	弛	?	?	?	弟5F20	?	弡	?	?	?	弥	弦	弧	?	弩	?	?	?	弭	?	弯5F30	?	弱	?	?	弴	張	?	強	弸	?	?	?	弼	?	弾	?5F40	?	彁	?	?	?	彅	?	?	彈	?	彊	?	彌	?	彎	?",
	//	USER_FONT, 64);
	//libFont->releaseUserFont();
	while (w->msgProc()) {
		if (w->active()) {
			indev->getState();
			mouseRect->setPos(INPUT_COMMON::MousePosition(indev));
			mousePoint->setPos(mouseRect->pos());
			mouseRectImage->setPos(mouseRect->pos());
			mouseCircle->setPos(mouseRect->pos());
			ds->set("mx:%d my:%d", indev->value(MOUSE_X), indev->value(MOUSE_Y));
			g->clearTarget(COLOR(0.4f, 0.4f, 0.4f, 1.0f));
			ds->set("%f", t);
			uiManager.update();
			SHADER* shader = Image2dShader;
			MATRIX cameraWorld;
			cameraWorld.identity();
			Image2dCameraShader->setCameraWorld(cameraWorld);
			BEGIN_PATH_
				UiRoot->draw(shader);
			END_PATH_
				drawerManager->draw();
			g->present();
		}
	}
	delete debugDrawer;
	delete ProcessNodeManager;
	delete StaticFont;
	delete mousePoint;
	delete mouseCircle;
	delete mouseRect;
	delete Image2dShader;
	delete Image2dCameraShader;
	delete c;
	delete drawerManager;
}
#endif

//３ｄ当たり判定
#if(0)
class PHYSICS {
public:
	PHYSICS() {};
	~PHYSICS() {};
	template<class T>
	void update(const T& obj) {
		Velo.y += -0.068f;
		Velo *= 0.98f;
		obj(Velo);
	};
	void collide(const VECTOR3& norm) {
		if (norm.x != 0.0f) {
			Velo.x = 0.0f;
		}
		if (norm.y != 0.0f) {
			Velo.y = 0.0f;
		}
		if (norm.z != 0.0f) {
			Velo.z = 0.0f;
		}
	};
	VECTOR3 velo() { return Velo; }
	void setVelo(const VECTOR3 velo) { Velo = velo; }
	void addForce(const VECTOR3 velo) { Velo += velo; }
private:
	VECTOR3 Velo;
};
void DebugRun() {
	WINDOW* w = WINDOW::instance();
	GRAPHIC* g = GRAPHIC::instance();
	INDEV* indev = INDEV::instance();
	DEBUG_STR* ds = DEBUG_STR::instance();
	CONTAINER* c = new CONTAINER("AssetsOrigin/MenuIcon.txt");
	CONTAINER* cPrimitive = new CONTAINER("Assets/primitive/Assets.txt");
	//シェーダー
	IMAGE_2D* Image2dShader = new IMAGE_2D();
	SOFT_SHADOW* SoftShadowShader = new SOFT_SHADOW(2048, 2048);
	CAMERA_DEBUG* Camera = new CAMERA_DEBUG();
	Camera->setDistanceFromLookatPos(6.0f);
	mt19937 rng;
	class PRIMITIVE:public COLLISION3D_CALLBACK{
	public:
		PRIMITIVE() {};
		virtual ~PRIMITIVE() {};
		virtual void update() = 0;
	private:

	};
	class PRIMITIVE_AABB:public PRIMITIVE{
	public:
		PRIMITIVE_AABB(CONTAINER* c, DRAWER::DRAWERS* drawers, COLLISION_MANAGER::COLLISION_LIST* collisionList){
			create(c, drawers, collisionList, VECTOR3(), VECTOR3::one());
		}
		PRIMITIVE_AABB(CONTAINER* c, DRAWER::DRAWERS* drawers, COLLISION_MANAGER::COLLISION_LIST* collisionList, const VECTOR3& pos) {
			create(c, drawers, collisionList, pos, VECTOR3::one());
		}
		PRIMITIVE_AABB(CONTAINER* c, DRAWER::DRAWERS* drawers, COLLISION_MANAGER::COLLISION_LIST* collisionList, const VECTOR3& pos,const VECTOR3& scale) {
			create(c, drawers, collisionList, pos, scale);
		}
		~PRIMITIVE_AABB() {
			Drawer->Delete();
			CollisionList->erase(this);
			delete Collision;
		};
		void update() override {
			Drawer->setPos(Drawer->pos() + INPUT_COMMON::Debug3dObjectMove(INDEV::instance()) * 0.1f);
			if (INDEV::instance()->isTrigger(KEY_SPACE)) { Physics.addForce(VECTOR3(0.0f, 1.0f, 0.0f)); }
			Physics.update([this](const VECTOR3& velo) {this->Drawer->setPos(this->Drawer->pos() + velo);});
			collisionUpdate();
		}
		void collisionUpdate() {
			Collision->setPos(Drawer->pos() - Drawer->scale() * 0.5f);
			Collision->setD(Drawer->scale());
		}
		void onCollision(COLLISION3D* collision) {};
		void onCollisionExtrude(VECTOR3 norm) {
			Drawer->setPos(Drawer->pos() + norm); 
			Physics.collide(norm);
		}
		DRAWER::BATCH* drawer(){ return Drawer; }
		COLLISION3D* collision()const { return Collision; }
		COLLISION3D_AABB* collision() { return Collision; }
		PHYSICS* physics() {return &Physics;}
	private:
		void create(CONTAINER* c, DRAWER::DRAWERS* drawers, COLLISION_MANAGER::COLLISION_LIST* collisionList, const VECTOR3& pos, const VECTOR3& scale) {
			Drawer = new DRAWER::BATCH();
			Drawer->setBatch(c->batch("PrimitiveBox"));
			drawers->add(Drawer);
			Collision = new COLLISION3D_AABB();
			CollisionList = collisionList;
			CollisionList->insert({ this,this });
			Drawer->setPos(pos);
			Drawer->setScale(scale);
			collisionUpdate();
		}
		PHYSICS Physics;
		COLLISION3D_AABB* Collision = nullptr;
		DRAWER::BATCH* Drawer = nullptr;
		COLLISION_MANAGER::COLLISION_LIST* CollisionList = nullptr;
	};
	class PRIMITIVE_CYLINDER :public PRIMITIVE {
	public:
		PRIMITIVE_CYLINDER(CONTAINER* c, DRAWER::DRAWERS* drawers, COLLISION_MANAGER::COLLISION_LIST* collisionList){
			create(c, drawers, collisionList, VECTOR3(), VECTOR3::one());
		}
		PRIMITIVE_CYLINDER(CONTAINER* c, DRAWER::DRAWERS* drawers, COLLISION_MANAGER::COLLISION_LIST* collisionList, const VECTOR3& pos) {
			create(c, drawers, collisionList, pos, VECTOR3::one());
		}
		PRIMITIVE_CYLINDER(CONTAINER* c, DRAWER::DRAWERS* drawers, COLLISION_MANAGER::COLLISION_LIST* collisionList, const VECTOR3& pos, const VECTOR3& scale) {
			create(c, drawers, collisionList, pos, scale);
		}

		~PRIMITIVE_CYLINDER() {
			CollisionList->erase(this);
			delete Collision;
		};
		void update() override {
			
			Drawer->setPos(Drawer->pos() + INPUT_COMMON::Debug3dObjectMove(INDEV::instance()) * 0.1f);
			if (INDEV::instance()->isTrigger(KEY_SPACE)) { Physics.addForce(VECTOR3(0.0f, 1.0f, 0.0f)); }
			Physics.update([this](const VECTOR3& velo) {this->Drawer->setPos(this->Drawer->pos() + velo);});
			collisionUpdate();
		}
		void collisionUpdate() {
			Collision->setPos(Drawer->pos() - VECTOR3(0.0f, Drawer->scale().y * 0.5f, 0.0f));
			Collision->setR(Drawer->scale().x);
			Collision->setHeight(Drawer->scale().y);
		}
		void onCollision(COLLISION3D* collision) {};
		void onCollisionExtrude(VECTOR3 norm) { 
			Drawer->setPos(Drawer->pos() + norm); 
			Physics.collide(norm);
		}
		DRAWER::BATCH* drawer() { return Drawer; }
		COLLISION3D* collision()const { return Collision; }
		COLLISION3D_CYLINDER_YAA* collision() { return Collision; }
		PHYSICS* physics() { return &Physics; }
	private:
		void create(CONTAINER* c, DRAWER::DRAWERS* drawers, COLLISION_MANAGER::COLLISION_LIST* collisionList, const VECTOR3& pos, const VECTOR3& scale) {
			Drawer = new DRAWER::BATCH();
			Drawer->setBatch(c->batch("PrimitiveCylinder"));
			drawers->add(Drawer);
			Collision = new COLLISION3D_CYLINDER_YAA();
			CollisionList = collisionList;
			CollisionList->insert({ this,this });
			Drawer->setPos(pos);
			Drawer->setScale(scale);
			collisionUpdate();
		};
		PHYSICS Physics;
		COLLISION3D_CYLINDER_YAA* Collision = nullptr;
		DRAWER::BATCH* Drawer = nullptr;
		COLLISION_MANAGER::COLLISION_LIST* CollisionList = nullptr;
	};

	class TERRAIN :public COLLISION3D_CALLBACK {
	public:
		TERRAIN(CONTAINER* c, DRAWER::DRAWERS* drawers, COLLISION_MANAGER::COLLISION_LIST* collisionList) {
			Drawer = new DRAWER::BATCH();
			Drawer->setBatch(c->batch("PrimitivePlane"));
			Drawer->setScale({ 100.0f,0.0f,100.0f });
			drawers->add(Drawer);
			Collision = new COLLISION3D_TERRAIN();
			CollisionList = collisionList;
			CollisionList->insert({ this,this });
		}
		TERRAIN(CONTAINER* c, DRAWER::DRAWERS* drawers, COLLISION_MANAGER::COLLISION_LIST* collisionList, const VECTOR3& pos) {
			Drawer = new DRAWER::BATCH();
			Drawer->setBatch(c->batch("PrimitivePlane"));
			Drawer->setScale({ 100.0f,0.0f,100.0f });
			drawers->add(Drawer);
			Collision = new COLLISION3D_TERRAIN();
			CollisionList = collisionList;
			CollisionList->insert({ this,this });
			Drawer->setPos(pos);
		}
		~TERRAIN() {
			CollisionList->erase(this);
			delete Collision;
		};
		void onCollision(COLLISION3D* collision) {};
		void onCollisionExtrude(VECTOR3 norm) { Drawer->setPos(Drawer->pos() + norm); }
		COLLISION3D* collision()const { return Collision; }
		COLLISION3D_TERRAIN* collision() { return Collision; }
	private:
		COLLISION3D_TERRAIN* Collision = nullptr;
		DRAWER::BATCH* Drawer = nullptr;
		COLLISION_MANAGER::COLLISION_LIST* CollisionList = nullptr;
	};
	//SothShadowShaderの行列情報
	MATRIX LightView;
	MATRIX LightProj;
	LightView.set(VECTOR3(10.0f, 20.0f, 3.0f), VECTOR3(0, 0, 0), VECTOR3(0, 1, 0));//ライトから見た頂点群に変換するマトリックス
	LightProj.setOrtho(30.0f, 30.0f, -1.0f, -20.0f);//正投影（見たまんま＝遠いものを小さくしない）マトリックス
	MATRIX Proj;
	MATRIX View;
	Proj.setPers(3.141592f/3.0f, g->aspect(), -0.1f, -100.1f);
	// Light
	VECTOR3 LightPos = VECTOR3(0.0f, 10.0f, 0.01f);
	float Ambient = 1.0f;
	COLOR Diffuse = COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// LightからのViewとProj
	LightView.set(LightPos, VECTOR3(0, 0, 0), VECTOR3(0, 1, 0));//ライトから見た頂点群に変換するマトリックス
	LightProj.setOrtho(10.0f, 10.0f, -1.0f, -20.0f);//正投影（見たまんま＝遠いものを小さくしない）マトリックス

	IMAGE2D_CAMERA* Image2dCameraShader = new IMAGE2D_CAMERA();

	DRAWER::MANAGER* drawerManager = new DRAWER::MANAGER();
	//2Dのレイヤー
	DRAWER::DRAWERS* drawers2d = new DRAWER::DRAWERS();
	drawers2d->setShader(Image2dShader);
	//3Dのレイヤー
	DRAWER::DRAWERS* drawers3d = new DRAWER::DRAWERS();
	drawers3d->setShader(SoftShadowShader);
	DRAWER::DRAWERS* processNodeLineDrawers = new DRAWER::DRAWERS();
	processNodeLineDrawers->setShader(Image2dShader);
	DRAWER::DRAWERS* processNodeSelectField = new DRAWER::DRAWERS();
	processNodeSelectField->setShader(Image2dShader);
	//レイヤーのレイアウト
	std::array<DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT, 4> layout = {
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("3d", drawers3d),
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("ui", drawers2d),
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("processNodeLine", processNodeLineDrawers),
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("processNodeSelectField", processNodeSelectField)
	};
	DRAWER::DRAWERS_LIST* drawersList = new DRAWER::DRAWERS_LIST();
	drawersList->create(layout);
	drawerManager->create(drawersList);
	{
		struct DebugDrawer {
			void draw(SHADER* shader) {
				Ds->draw(shader);
			};
			DEBUG_STR* Ds = nullptr;
		};
		DebugDrawer* debugDrawer = new DebugDrawer;
		debugDrawer->Ds = ds;
		auto image = new DRAWER::SAUCER(debugDrawer);
		drawerManager->drawerAdd("ui", image);
	}
	std::string str;
	//マウスの判定
	COLLISION2D_POINT* mousePoint = new COLLISION2D_POINT;

	COLLISION_MANAGER CollisionManager;
	TERRAIN* terrain = new TERRAIN(cPrimitive,drawers3d, CollisionManager.staticCollisions());
	std::vector<PRIMITIVE*> staticPrimitives = {
		new PRIMITIVE_CYLINDER(cPrimitive, drawers3d, CollisionManager.staticCollisions(),VECTOR3(5.0f,0.5f,1.0f)),
		new PRIMITIVE_AABB(cPrimitive, drawers3d, CollisionManager.staticCollisions(),VECTOR3(5.0f,0.5f,8.0f)),
		new PRIMITIVE_AABB(cPrimitive, drawers3d, CollisionManager.staticCollisions(),VECTOR3(10.0f,0.5f,-8.0f),VECTOR3(5.0f,5.0f,5.0f)),
		new PRIMITIVE_AABB(cPrimitive, drawers3d, CollisionManager.staticCollisions(),VECTOR3(10.0f,0.5f,15.0f),VECTOR3(5.0f,10.0f,5.0f)),
		new PRIMITIVE_AABB(cPrimitive, drawers3d, CollisionManager.staticCollisions(),VECTOR3(-10.0f,0.5f,12.0f),VECTOR3(5.0f,2.0f,15.0f)),
		new PRIMITIVE_AABB(cPrimitive, drawers3d, CollisionManager.staticCollisions(),VECTOR3(-18.0f,0.5f,-18.0f),VECTOR3(40.0f,6.0f,20.0f)),
		new PRIMITIVE_CYLINDER(cPrimitive, drawers3d, CollisionManager.staticCollisions(),VECTOR3(25.0f,0.0f,25.0f),VECTOR3(20.0f,60.0f,20.0f)),
	};

	std::vector<PRIMITIVE*> primitives ={ 
		new PRIMITIVE_CYLINDER(cPrimitive, drawers3d, CollisionManager.collisions()),
		new PRIMITIVE_AABB(cPrimitive, drawers3d, CollisionManager.collisions()) 
	};
	PRIMITIVE_AABB* Cursol = new PRIMITIVE_AABB(cPrimitive, drawers3d, CollisionManager.collisions());
	primitives.push_back(Cursol);

	float z = 0.0f;
	STATIC_FONT* StaticFont = new STATIC_FONT(64, "Assets/font/APJapanesefontT.ttf", "APJapanesefontT", "ｽﾀﾃｨｯｸ");
	PROCESS_NODE_MANAGER* ProcessNodeManager = new PROCESS_NODE_MANAGER(c, StaticFont, drawersList);
	//UIレイアウト
	UI* UiRoot = ProcessNodeManager->rootUi();
	//UI_MANAGER uiManager(processNode->rootUi());
	UI_MANAGER uiManager(UiRoot);
	while (w->msgProc()) {
		if (w->active()) {
			/*
			auto outMatrixDebug = [&](const MATRIX& m) {
				ds->set("%8.2f %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f",
					m._11, m._12, m._13, m._14, m._21, m._22, m._23, m._24, m._31, m._32, m._33, m._34, m._41, m._42, m._43, m._44);};
			auto outVector3Debug = [&](const VECTOR3& v) {
				ds->set("%8.2f %8.2f %8.2f",
					v.x, v.y, v.z);};
			{
				{
					MATRIX m_w;
					m_w.mulTranslate(VECTOR3(5.0f, 3.0f, -6.0));
					MATRIX m_p;
					m_p = Proj;
					MATRIX m_pInv;
					inverseMatrix(&m_pInv, m_p);
					::Effekseer::Matrix44 e_m_pInv;
					::Effekseer::Matrix44::Inverse(e_m_pInv, EFFEKSEER::cvtMatrix(m_p));
					MATRIX m_s = m_w * m_p;
					MATRIX m_sInv = m_s * EFFEKSEER::uncvtMatrix(e_m_pInv);

					m_s = m_s;
				}
				MATRIX m_w;
				m_w.mulTranslate(VECTOR3(5.0f, 3.0f, -6.0));
				MATRIX m_p;
				m_p = Proj;
				MATRIX m_v;
				m_v = View;
				MATRIX m_s = m_w * Proj * View;

				MATRIX m_wInv;
				MATRIX m_pInv;
				m_pInv = EFFEKSEER::inverseMatrix(m_p);
				MATRIX m_vInv;
				m_vInv = EFFEKSEER::inverseMatrix(m_v);
				MATRIX m_pvInv = EFFEKSEER::inverseMatrix(Proj * View);
				MATRIX m_sInv = m_s * m_pInv * m_vInv;
				MATRIX m_sInv2 = m_s * m_pvInv;
				m_sInv = m_sInv;
			}
			{
				//outMatrixDebug(View);
				//outMatrixDebug(EFFEKSEER::uncvtMatrix(EFFEKSEER::cvtMatrix(View)));
				//outMatrixDebug(View* EFFEKSEER::inverseMatrix(View));
				//outMatrixDebug(EFFEKSEER::inverseMatrix(View) * View);
				//MATRIX inv;
				//inverseMatrix(&inv, View);
				//outMatrixDebug(inv * View);
				//outMatrixDebug(View * inv);
				VECTOR3 wPos = VECTOR3(6.0, 7.0f, -2.0f);
				MATRIX m;
				m.mulTranslate(wPos);
				outMatrixDebug(m);
				m = m*(View);
				outMatrixDebug(m);
				m = m * inverseMatrix(View);
				outMatrixDebug(m);

				m.identity();
				m.mulTranslate(wPos);
				outMatrixDebug(Proj);
				m = m * (Proj);
				outMatrixDebug(m* EFFEKSEER::inverseMatrix(Proj));
			}
			*/
			indev->getState();
			mousePoint->setPos(VECTOR2(indev->value(MOUSE_X), indev->value(MOUSE_Y)));
			ds->set("mx:%d my:%d", indev->value(MOUSE_X), indev->value(MOUSE_Y));
			ds->set("mouseWheel:%d", indev->value(MOUSE_WHEEL));

			if (indev->isTrigger(KEY_L)) {
				uniform_real_distribution<float> dist(-0.5f, 0.5f);
				PRIMITIVE_AABB* p = new PRIMITIVE_AABB(cPrimitive, drawers3d, CollisionManager.collisions(), VECTOR3(0, 3.0f, 0));
				p->physics()->addForce(VECTOR3(dist(rng), dist(rng)+1.0f, dist(rng)));
				primitives.push_back(p);
			}
			if (indev->isPress(KEY_UP)) {
				z += 0.1f;
			}
			if (indev->isPress(KEY_DOWN)) {
				z += -0.1f;
			}
			uiManager.update();
			VECTOR2 MousePos = INPUT_COMMON::MousePosition(indev);
			VECTOR2 pos = VECTOR2((MousePos.x / (g->baseWidth()) - 0.5f) * 2.0f, -(MousePos.y / (g->baseHeight()) - 0.5f) * 2.0f);
			Cursol->drawer()->setPos(VECTOR3(0.0f,Cursol->drawer()->scale().y*0.5f,0.0f) + CalcFloorAndLineHitPoint(0.0f, Camera->cameraPos(), DRAWER::ScreenToWorldPoint(Proj, View, INPUT_COMMON::MousePosition(indev), 1.0f) - Camera->cameraPos()));
			if (indev->isTrigger(MOUSE_LBUTTON)) {
				PRIMITIVE_AABB* p = new PRIMITIVE_AABB(cPrimitive, drawers3d, CollisionManager.collisions(), Camera->cameraPos());
				p->physics()->addForce(normalize( DRAWER::ScreenToWorldPoint(Proj, View, INPUT_COMMON::MousePosition(indev), 1.0f)-Camera->cameraPos()));
				primitives.push_back(p);
			}
			for (auto& i : primitives) {
				i->update();
			}
			CollisionManager.exeCollisionExtrude();
			g->clearTarget(COLOR(0.4f, 0.4f, 0.4f, 1.0f));
			SHADER* shader = Image2dShader;
			MATRIX cameraWorld;
			cameraWorld.identity();
			Image2dCameraShader->setCameraWorld(cameraWorld);
			shader = SoftShadowShader;
			Camera->update(&View, VECTOR3(), 0.0f);
			SoftShadowShader->setLightPosition(LightPos);
			SoftShadowShader->setLightAmbient(Ambient);
			SoftShadowShader->setDiffuse(Diffuse);
			SoftShadowShader->setProjView(Proj * View);
			SoftShadowShader->setLight_ProjView(LightProj * LightView);
			shader = Image2dShader;
			BEGIN_PATH_
				UiRoot->draw(shader);
			END_PATH_
			drawerManager->draw();
			g->present();
		}
	}
	for (auto& i : primitives) {
		delete i;
	}
	for (auto& i : staticPrimitives) {
		delete i;
	}
	delete ProcessNodeManager;
	delete StaticFont;
	delete terrain;
	delete cPrimitive;
	delete Camera;
	delete SoftShadowShader;
	delete mousePoint;
	delete Image2dShader;
	delete Image2dCameraShader;
	delete c;
	delete drawerManager;
}
#endif

//エンティティ
#if(0)
#include "TERRAIN_AABB.h"
#include "TERRAIN_CYLINDER.h"
#include "TERRAIN_FLOOR.h"
#include "UPDATER.h"
#include "UPDATER_MANAGER.h"
void DebugRun() {
	WINDOW* w = WINDOW::instance();
	GRAPHIC* g = GRAPHIC::instance();
	INDEV* indev = INDEV::instance();
	DEBUG_STR* ds = DEBUG_STR::instance();
	CONTAINER* c = new CONTAINER("AssetsOrigin/MenuIcon.txt");
	CONTAINER* cPrimitive = new CONTAINER("Assets/primitive/Assets.txt");
	//シェーダー
	IMAGE_2D* Image2dShader = new IMAGE_2D();
	SOFT_SHADOW* SoftShadowShader = new SOFT_SHADOW(2048, 2048);
	CAMERA_DEBUG* Camera = new CAMERA_DEBUG();
	Camera->setDistanceFromLookatPos(6.0f);
	mt19937 rng;
	//SothShadowShaderの行列情報
	MATRIX LightView;
	MATRIX LightProj;
	LightView.set(VECTOR3(10.0f, 20.0f, 3.0f), VECTOR3(0, 0, 0), VECTOR3(0, 1, 0));//ライトから見た頂点群に変換するマトリックス
	LightProj.setOrtho(30.0f, 30.0f, -1.0f, -20.0f);//正投影（見たまんま＝遠いものを小さくしない）マトリックス
	MATRIX Proj;
	MATRIX View;
	Proj.setPers(3.141592f / 3.0f, g->aspect(), -0.1f, -100.1f);
	// Light
	VECTOR3 LightPos = VECTOR3(0.0f, 10.0f, 0.01f);
	float Ambient = 1.0f;
	COLOR Diffuse = COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// LightからのViewとProj
	LightView.set(LightPos, VECTOR3(0, 0, 0), VECTOR3(0, 1, 0));//ライトから見た頂点群に変換するマトリックス
	LightProj.setOrtho(10.0f, 10.0f, -1.0f, -20.0f);//正投影（見たまんま＝遠いものを小さくしない）マトリックス

	IMAGE2D_CAMERA* Image2dCameraShader = new IMAGE2D_CAMERA();

	DRAWER::MANAGER* drawerManager = new DRAWER::MANAGER();
	//2Dのレイヤー
	DRAWER::DRAWERS* drawers2d = new DRAWER::DRAWERS();
	drawers2d->setShader(Image2dShader);
	//3Dのレイヤー
	DRAWER::DRAWERS* drawers3d = new DRAWER::DRAWERS();
	drawers3d->setShader(SoftShadowShader);
	DRAWER::DRAWERS* processNodeLineDrawers = new DRAWER::DRAWERS();
	processNodeLineDrawers->setShader(Image2dShader);
	DRAWER::DRAWERS* processNodeSelectField = new DRAWER::DRAWERS();
	processNodeSelectField->setShader(Image2dShader);
	//レイヤーのレイアウト
	std::array<DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT, 4> layout = {
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("3d", drawers3d),
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("ui", drawers2d),
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("processNodeLine", processNodeLineDrawers),
		DRAWER::DRAWERS_LIST::DRAWERS_LIST_LAYOUT("processNodeSelectField", processNodeSelectField)
	};
	DRAWER::DRAWERS_LIST* drawersList = new DRAWER::DRAWERS_LIST();
	drawersList->create(layout);
	drawerManager->create(drawersList);
	
	struct DebugDrawer {
		void draw(SHADER* shader) {
			Ds->draw(shader);
		};
		void test() {

		}
		DEBUG_STR* Ds = nullptr;
	};
	DebugDrawer* debugDrawer = new DebugDrawer;
	{
		debugDrawer->Ds = ds;
		auto image = new DRAWER::SAUCER(debugDrawer);
		drawerManager->drawerAdd("ui", image);
	}
	std::string str;
	//マウスの判定
	COLLISION2D_POINT* mousePoint = new COLLISION2D_POINT;
	std::vector<pair<ENTITY::ENTITY*,int>> EntityList;
	UPDATER_MANAGER UpdaterManager;
	COLLISION_MANAGER CollisionManager;
	float z = 0.0f;
	STATIC_FONT* StaticFont = new STATIC_FONT(64, "Assets/font/APJapanesefontT.ttf", "APJapanesefontT", "ｽﾀﾃｨｯｸ");
	ENTITY::TERRAIN_FLOOR* TerrainFloor = new ENTITY::TERRAIN_FLOOR(cPrimitive, drawers3d, CollisionManager.staticCollisions());
	TerrainFloor->setScale(VECTOR3(100.0f, 1.0f, 100.0f));
	while (w->msgProc()) {
		if (w->active()) {
			indev->getState();
			mousePoint->setPos(VECTOR2(indev->value(MOUSE_X), indev->value(MOUSE_Y)));
			VECTOR2 MousePos = INPUT_COMMON::MousePosition(indev);
			VECTOR2 pos = VECTOR2((MousePos.x / (g->baseWidth()) - 0.5f) * 2.0f, -(MousePos.y / (g->baseHeight()) - 0.5f) * 2.0f);
			if (indev->isTrigger(MOUSE_LBUTTON)) {
				ENTITY::TERRAIN_AABB* p = new ENTITY::TERRAIN_AABB(cPrimitive, drawers3d, CollisionManager.collisions(), &UpdaterManager);
				p->setPos(Camera->cameraPos());
				p->physics()->addForce(normalize(DRAWER::ScreenToWorldPoint(Proj, View, INPUT_COMMON::MousePosition(indev), 1.0f) - Camera->cameraPos()));
				EntityList.push_back({ p ,0});
			}
			if (indev->isTrigger(MOUSE_RBUTTON)) {
				ENTITY::TERRAIN_CYLINDER* p = new ENTITY::TERRAIN_CYLINDER(cPrimitive, drawers3d, CollisionManager.collisions(), &UpdaterManager);
				p->setPos(Camera->cameraPos());
				p->physics()->addForce(normalize(DRAWER::ScreenToWorldPoint(Proj, View, INPUT_COMMON::MousePosition(indev), 1.0f) - Camera->cameraPos()));
				EntityList.push_back({ p ,0 });
			}
			ds->set("mx:%d my:%d", indev->value(MOUSE_X), indev->value(MOUSE_Y));
			ds->set("mouseWheel:%d", indev->value(MOUSE_WHEEL));
			for (int i = 0;i < EntityList.size();) {
				EntityList[i].second++;
				if (EntityList[i].second > 600) {
					delete EntityList[i].first;
					EntityList[i] = EntityList.back();
					EntityList.pop_back();
					continue;
				}
				i++;
			}
			UpdaterManager.update();
			CollisionManager.exeCollisionExtrude();
			CollisionManager.exeCollision();

			g->clearTarget(COLOR(0.4f, 0.4f, 0.4f, 1.0f));
			SHADER* shader = Image2dShader;
			MATRIX cameraWorld;
			cameraWorld.identity();
			Image2dCameraShader->setCameraWorld(cameraWorld);
			shader = SoftShadowShader;
			Camera->update(&View, VECTOR3(), 0.0f);
			SoftShadowShader->setLightPosition(LightPos);
			SoftShadowShader->setLightAmbient(Ambient);
			SoftShadowShader->setDiffuse(Diffuse);
			SoftShadowShader->setProjView(Proj * View);
			SoftShadowShader->setLight_ProjView(LightProj * LightView);
			shader = Image2dShader;
			BEGIN_PATH_

			END_PATH_
				drawerManager->draw();
			g->present();
		}
	}
	for (auto& i : EntityList) {
		delete i.first;
	}
	delete debugDrawer;
	delete TerrainFloor;
	delete StaticFont;
	delete cPrimitive;
	delete Camera;
	delete SoftShadowShader;
	delete mousePoint;
	delete Image2dShader;
	delete Image2dCameraShader;
	delete c;
	delete drawerManager;
}
#endif

#if(0)
#include "CLIENT.h"
void DebugRun() {
	//シェーダー
	IMAGE_2D* Image2dShader = new IMAGE_2D();
	WINDOW* w = WINDOW::instance();
	GRAPHIC* g = GRAPHIC::instance();
	INDEV* indev = INDEV::instance();
	DEBUG_STR* ds = DEBUG_STR::instance();
	CONTAINER* c = new CONTAINER("AssetsOrigin/MenuIcon.txt");
	CLIENT Client;
	while (w->msgProc()) {
		if (w->active()) {
			indev->getState();
			Client.update();

			g->clearTarget(COLOR(0.4f, 0.4f, 0.4f, 1.0f));
			SHADER* shader = Image2dShader;
			shader = Image2dShader;
			BEGIN_PATH_
			Client.draw();
			END_PATH_

			g->present();
		}
	}
}
#endif