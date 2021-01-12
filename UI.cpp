#include "../Library/common.h"
#include "../Library/VECTOR2.h"
#include "../Library/TEXTURE.h"
#include "UI_MANAGER.h"
#include "COLLISION2D_RECT.h"
#include "UI.h"
UI::UI() :
	Scale(VECTOR2(1.0f,1.0f)),
	ParentScale(VECTOR2(1.0f,1.0f)){

}

UI::~UI() {
	SAFE_DELETE(Drawer);
	SAFE_DELETE(Collision);
	if (Parent != nullptr) {
		Parent->removeChilds(this);//親に自分が死んだことを通知
		Parent = nullptr;
	}
	for (auto& i : Childs) {
		i->setParent(nullptr);//子に親が死んだことを通知
		if (!i->isReleaseDisable() || i->isDelete()) {
			SAFE_DELETE(i);
		}
	}
	//登録元のマネージャーに通知
	if (UiManager != nullptr) {
		UiManager->uiDelete(this);
	}
}

void UI::init(){
	DownFunc = nullptr;
	UpFunc = nullptr;
	PushFunc = nullptr;
	DragUpdate = nullptr;
	DragEndFunc = nullptr;
	OverlapIn = nullptr;
	OverlapOut = nullptr;
	IdelUpdate = nullptr;
	ParentPos = VECTOR2();
	ParentScale = VECTOR2::one();
	Pos = VECTOR2();
	Scale = VECTOR2::one();
	Parent = nullptr;
	IsDisable = false;
	IsChildCollisionRestrict = false;
	IsCollisionDisable = false;
	IsUnconditionalCollisionHit = false;
	IsReleaseDisable = false;
	IsDelete = false;
	SAFE_DELETE(Drawer);
	SAFE_DELETE(Collision);
	for (auto& i : Childs) {
		if (!i->isReleaseDisable() || i->isDelete()) {
			delete i;
		}
	}
	Childs.clear();
}

void UI::draw(SHADER* shader) {
	if (IsDisable) return;
	Drawer->draw(shader);
	for (auto& i : Childs) {
		i->draw(shader);
	}
}

void UI::setPos(const VECTOR2& pos){
	Pos = pos;
	VECTOR2 p = Pos * ParentScale + ParentPos;
	Collision->setPos(p);
	Drawer->setPos(p);
	for (auto& i : Childs) {
		i->setPosChild(p);
	}
}

void UI::setScale(const VECTOR2& scale){
	Scale = scale;
	VECTOR2 wh = Scale * ParentScale;
	Collision->setWh(wh * Drawer->wh());
	Drawer->setScale(wh);
	for (auto& i : Childs) {
		i->setScaleChild(wh);
	}
	setPos(Pos);
}

void UI::setScale(const VECTOR2& scale, const VECTOR2& localPos){
	VECTOR2 scaleAmout = scale - Scale;
	Scale = scale;
	VECTOR2 wh = Scale * ParentScale;
	Collision->setWh(wh * Drawer->wh());
	Drawer->setScale(wh);
	for (auto& i : Childs) {
		i->setScaleChild(wh);
	}
	setPos(Pos- localPos* scaleAmout);
}

bool UI::OverlapUi(const COLLISION2D* p, UI*& out_overlapUi) {
	
	if (IsDisable) return false;
	if (IsCollisionDisable) return false;
	if (IsUnconditionalCollisionHit || Collision->dispatch(p)) {
		out_overlapUi = this;
		for (auto i = Childs.crbegin();i != Childs.crend();i++) {
			if ((*i)->OverlapUi(p, out_overlapUi)) return true;
		}
		return true;
	}
	else {
		if (!IsChildCollisionRestrict) {
			for (auto i = Childs.crbegin();i != Childs.crend();i++) {
				if((*i)->OverlapUi(p, out_overlapUi)) return true;
			}
		}
	}
	return false;
}

void UI::addChilds(UI* child) {
	Childs.push_back(child);
	child->setParent(this);
	child->setScaleChild(Scale * ParentScale);
	child->setPosChild(Pos * ParentScale + ParentPos);
}

void UI::removeChilds(UI* child){
	for (size_t i = 0;i < Childs.size();i++) {
		if (Childs[i] == child) {
			Childs[i]->setParent(nullptr);
			Childs[i] = Childs.back();
			Childs.pop_back();
		}
	}
}

void UI::DeleteUpdate(){
	for (size_t i = 0;i < Childs.size();i++) {
		if (Childs[i]->isDelete()) {
			SAFE_DELETE(Childs[i]);
		}
		else{
			Childs[i]->DeleteUpdate();
		}
	}
}

//絶対位置でコリジョンの中心の位置を返す
VECTOR2 UI::centerPos() const {
	return absolutePos() + drawer()->wh() * absoluteScale() * 0.5f;
}

VECTOR2 UI::localPosToWorldPos(const VECTOR2& localPos) const{
	return ParentScale * Scale * ParentPos + localPos * ParentScale * Scale + Pos;
	//return (Pos+ localPos) * ParentScale* Scale + ParentPos;
}

VECTOR2 UI::worldPosToLocalPos(const VECTOR2& worldPos) const{
	return (worldPos - Pos) / ParentScale / Scale - ParentPos;
}

void UI::Delete(){
	IsDelete = true;
}

void UI::setPosChild(const VECTOR2& pos){
	ParentPos = pos;
	VECTOR2 p = Pos * ParentScale + ParentPos;
	Drawer->setPos(p);
	Collision->setPos(p);
	for (auto& i : Childs) {
		i->setPosChild(p);
	}
}

void UI::setScaleChild(const VECTOR2& scale){
	ParentScale = scale;
	VECTOR2 wh;
	wh.x = scale.x * Scale.x;
	wh.y = scale.y * Scale.y;
	Collision->setWh(wh*Drawer->wh());
	Drawer->setScale(wh);
	for (auto& i : Childs) {
		i->setScaleChild(wh);
	}
}
