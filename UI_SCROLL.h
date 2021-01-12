#pragma once
#include <vector>
class CONTAINER;
class UI;
class SHADER;
class UI_SCROLL{
public:
	UI_SCROLL();
	~UI_SCROLL();
	void draw(SHADER* shader);
	void create(CONTAINER* c, int maxStepNum);
	void create(
		UI* rootUi,
		UI* seekBarBackUi,
		UI* seekBarUi, 
		UI* listBackUi, 
		UI* scrollUpUi,
		UI* scrollDownUi,
		std::vector<UI*>&& listUi, 
		int maxStepNum);
	void update();
	//指定段数で更新する
	void scrollUpdate(int stepNum);
	//指定高さで更新する
	void scrollUpdate(float height);
	UI* rootUi() { return RootUi; }
	UI* seekBarBackUi() { return SeekBarBackUi; }
	UI* seekBarUi() { return SeekBarUi; }
	UI* listBackUi() { return ListBackUi; }
	UI* scrollUpUi() { return ScrollUpUi; }
	UI* scrollDownUi() { return ScrollDownUi; }
	std::vector<UI*>* listUi() { return &ListUi; }
	int stepNum()const { return StepNum; }
	//スクロールに要素を追加する
	void add(UI* ui);
	//スクロールから該当するUIを除く
	void remove(UI* ui);
	using NODE_LIST = std::vector<UI*>;
private:
	//シークバーの挙動設定（マウスの移動量で計算）
	void setSeekBarFunc_0();
	//シークバーの挙動設定(押下した場所からの相対距離で計算)
	void setSeekBarFunc_1();
	//表示できる段数
	int MaxStepNum = 0;
	//現在表示基準段数
	int StepNum = 0;
	//スクロールスピード
	float ScrollSpeed = 0.0f;
	//毎フレームスクロールスピード加算量
	float ScrollSpeedAdd = 0.0f;
	//
	float ScrollFraction = 0.0f;
	UI* RootUi = nullptr;
	UI* SeekBarBackUi = nullptr;
	UI* SeekBarUi = nullptr;
	UI* ListBackUi = nullptr;
	UI* ScrollUpUi = nullptr;
	UI* ScrollDownUi = nullptr;
	//スクロールリストの全ての要素
	NODE_LIST ListUi;
	//マウスが押下された位置
	VECTOR2 MouseDownPos;
	//マウスが押下されたときの表示段数
	int MouseDownStepNum = 0;
	UI* ChoiceUi = nullptr;
	UI* DownUi = nullptr;
	
};

