#pragma once
#include <vector>
#include <functional>
#include <string>
#include <type_traits>
#include "../Library/VECTOR2.h"
#include "UI_ANNOTATION.h"
#include "DRAWER_IMAGE2D.h"
#include "DRAWER_FONT.h"
#include "COLLISION2D_RECT.h"
class SHADER;
class COLLISION2D;
class TEXTURE;
class UI_MANAGER;
//UIのドロワーのインターフェース
class UI_DRAWER {
public:
	virtual ~UI_DRAWER() {};
	virtual VECTOR2 pos() = 0;//矩形の左上のスクリーン座標を返さなければなりません
	virtual VECTOR2 scale() = 0;//矩形の幅と高さを返さなければなりません
	virtual void setPos(const VECTOR2& pos) = 0;//pos()が返す値とここで設定した値と同じ値にならなければなりません(setPos(pos())=不変)
	virtual void setScale(const VECTOR2& scale) = 0;//scale()が返す値とここで設定した値と同じ値にならなければなりません(setScale(scale())=不変)
	virtual VECTOR2 wh() = 0;//矩形のscale()を掛ける前の元のサイズを返さなければなりません
	virtual void draw(SHADER* shader) = 0;//pos()が左上でwh()*scale()のサイズの画像が描画されなければなりません
};

template<class T>
class UI_DRAWER_ :public UI_DRAWER{
public:
	using value_type = T;
	UI_DRAWER_(T* obj):Obj(obj){}
	~UI_DRAWER_() { delete Obj; }
	VECTOR2 pos() { return Obj->pos(); }
	VECTOR2 scale() { return Obj->scale(); }
	void setPos(const VECTOR2& pos) { Obj->setPos(pos); }
	void setScale(const VECTOR2& scale) { Obj->setScale(scale); }
	VECTOR2 wh() { return Obj->wh(); }
	void draw(SHADER* shader) { Obj->draw(shader); }
	T* obj() { return Obj; }
private:
	T* Obj = nullptr;
};
/*
基本、UIの描画順はaddする順番じゃなく親子の関係で行う
*/
class UI{
public:
	UI();
	~UI();
	void init();

	template<class T>
	void create(T* drawer) {
		Drawer = new UI_DRAWER_(drawer);
		Pos = Drawer->pos();
		Scale = Drawer->scale();
		Collision = new COLLISION2D_RECT;
		Collision->setPos(Pos);
		Collision->setWh(drawer->wh());
		setPos(Pos);
		setScale(Scale);
	}

	void draw(SHADER* shader);
	void setPos(const VECTOR2& pos);
	void setScale(const VECTOR2& scale);
	void setScale(const VECTOR2& scale,const VECTOR2& localPos);
	//重なっている一番手前のUIを探す
	bool OverlapUi(const COLLISION2D* p, UI*& out_overlapUi);
	void downFunc() { if (DownFunc != nullptr) DownFunc(); }
	void upFunc() { if (UpFunc != nullptr) UpFunc(); }
	void pushFunc() { if (PushFunc != nullptr) PushFunc(); }
	void dragUpdate() { if (DragUpdate != nullptr) DragUpdate(); }
	void dragEndFunc() { if (DragEndFunc != nullptr) DragEndFunc(); }
	void overlapIn() { if (OverlapIn != nullptr) OverlapIn(); }
	void overlapUpdate() { if (OverlapUpdate != nullptr) OverlapUpdate(); }
	void overlapOut() { if (OverlapOut != nullptr) OverlapOut(); }
	void idelUpdate() { if (IdelUpdate != nullptr) IdelUpdate(); }
	void setParentPos(const VECTOR2& parentPos) { ParentPos = parentPos; }
	void setIndependentPos(const VECTOR2& pos) { Pos = pos; }

	//trueでこのUIを無効にする
	void setIsDisable(bool isDisable) { IsDisable = isDisable; }
	//trueでこのUIの子を親の当たり判定で制限する
	void setIsChildCollisionRestrict(bool isChildCollisionRestrict) { IsChildCollisionRestrict = isChildCollisionRestrict; }
	//trueでこのUIの当たり判定を無効にする
	void setIsCollisionDisable(bool isCollisionDisable) { IsCollisionDisable = isCollisionDisable; }
	//trueでこのUIの判定が全部になる
	void setIsUnconditionalCollisionHit(bool isUnconditionalCollisionHit) { IsUnconditionalCollisionHit = isUnconditionalCollisionHit; }
	//trueで親から自動開放されないようになる
	void setIsReleaseDisable(bool isReleaseDisable) { IsReleaseDisable = isReleaseDisable; }
	//親を設定する
	void setParent(UI* parent) { Parent = parent; }
	//ベクター仕様により重くなる可能性あり
	void addChilds(UI* child);
	//ベクター仕様により要素数が多いと重くなる可能性あり。また、順番が入れ替わる
	void removeChilds(UI* child);
	void setDownFunc(const std::function<void()>& downFunc) { DownFunc = downFunc; }
	void setUpFunc(const std::function<void()>& upFunc) { UpFunc = upFunc; }
	void setPushFunc(const std::function<void()>& pushFunc) { PushFunc = pushFunc; }
	void setDragUpdate(const std::function<void()>& dragUpdate) { DragUpdate = dragUpdate; }
	void setDragEndFunc(const std::function<void()>& dragEndFunc) { DragEndFunc = dragEndFunc; }
	void setOverlapIn(const std::function<void()>& overlapIn) { OverlapIn = overlapIn; }
	void setOverlapUpdate(const std::function<void()>& overlapUpdate) { OverlapUpdate = overlapUpdate; }
	void setOverlapOut(const std::function<void()>& overlapOut) { OverlapOut = overlapOut; }
	void setIdelUpdate(const std::function<void()>& idelUpdate) { IdelUpdate = idelUpdate; }
	//UiManagerを入れとくとdeleteの際にUiManager通知する
	void setUiManager(UI_MANAGER* uiManager) { UiManager = uiManager; }
	//削除
	void Delete();
	//実際に開放する
	void DeleteUpdate();

	//ゲッター
	bool isDisable()const { return IsDisable; }
	bool isChildCollisionRestrict()const { return IsChildCollisionRestrict; }
	bool isCollisionDisable()const { return IsCollisionDisable; }
	bool isUnconditionalCollisionHit()const { return IsUnconditionalCollisionHit; }
	bool isReleaseDisable()const { return IsReleaseDisable; }
	VECTOR2 pos() const{ return Pos; }
	VECTOR2 parentPos()const { return ParentPos; }
	//絶対位置
	VECTOR2 absolutePos()const { return Pos * ParentScale + ParentPos; }
	//絶対位置でコリジョンの中心の位置を返す
	VECTOR2 centerPos()const;

	VECTOR2 scale() const{ return Scale; }
	VECTOR2 parentScale() const{ return ParentScale; }
	//このUIを描画する際のスケールの累計
	VECTOR2 absoluteScale()const { return Scale* ParentScale; }
	//このUI上の座標を画面全体の座標に変換する
	VECTOR2 localPosToWorldPos(const VECTOR2& localPos)const;
	//画面全体の座標をこのUI上の座標に変換する
	VECTOR2 worldPosToLocalPos(const VECTOR2& worldPos)const;
	UI_DRAWER* drawer() const { return Drawer; }
	COLLISION2D_RECT* collision()const { return Collision;}
	std::vector<UI*>* child() { return &Childs;}
	bool isDelete() { return IsDelete; }
	UI* parent() { return Parent; }
	UI_ANNOTATION* annotation() { return &Annotation; }
private:
	//子の位置を更新
	void setPosChild(const VECTOR2& pos);
	//子のスケールを更新
	void setScaleChild(const VECTOR2& scale);
	//親からの位置（累計）(親のからのスケール乗算済み)
	VECTOR2 ParentPos;
	//親からのスケール（累計）
	VECTOR2 ParentScale;
	//相対位置
	VECTOR2 Pos;
	//自分にかかるスケール
	VECTOR2 Scale;
	UI_DRAWER* Drawer = nullptr;

	std::function<void()> DownFunc = nullptr;
	std::function<void()> UpFunc = nullptr;
	std::function<void()> PushFunc = nullptr;
	std::function<void()> DragUpdate = nullptr;
	std::function<void()> DragEndFunc = nullptr;
	std::function<void()> OverlapIn = nullptr;
	std::function<void()> OverlapUpdate = nullptr;
	std::function<void()> OverlapOut = nullptr;
	std::function<void()> IdelUpdate = nullptr;

	COLLISION2D_RECT* Collision = nullptr;
	UI* Parent = nullptr;
	std::vector<UI*> Childs;
	UI_ANNOTATION Annotation;
	//非活性か？（trueだと描画と判定が無効になる）
	bool IsDisable = false;
	//親の当たり判定で子の判定を制限するか？
	bool IsChildCollisionRestrict = false;
	//自分の当たり判定が無効か？
	bool IsCollisionDisable = false;
	//trueで絶対当たるようになる（後ろをクリックして欲しくない時とかにこれを入れたUIを挟む）
	bool IsUnconditionalCollisionHit = false;
	//親から自動開放されないようにする
	bool IsReleaseDisable = false;
	//解放済みか
	bool IsDelete = false;
	//登録中されているマネージャー
	UI_MANAGER* UiManager = nullptr;
	std::string Id;
};

