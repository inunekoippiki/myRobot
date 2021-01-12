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
//UI�̃h�����[�̃C���^�[�t�F�[�X
class UI_DRAWER {
public:
	virtual ~UI_DRAWER() {};
	virtual VECTOR2 pos() = 0;//��`�̍���̃X�N���[�����W��Ԃ��Ȃ���΂Ȃ�܂���
	virtual VECTOR2 scale() = 0;//��`�̕��ƍ�����Ԃ��Ȃ���΂Ȃ�܂���
	virtual void setPos(const VECTOR2& pos) = 0;//pos()���Ԃ��l�Ƃ����Őݒ肵���l�Ɠ����l�ɂȂ�Ȃ���΂Ȃ�܂���(setPos(pos())=�s��)
	virtual void setScale(const VECTOR2& scale) = 0;//scale()���Ԃ��l�Ƃ����Őݒ肵���l�Ɠ����l�ɂȂ�Ȃ���΂Ȃ�܂���(setScale(scale())=�s��)
	virtual VECTOR2 wh() = 0;//��`��scale()���|����O�̌��̃T�C�Y��Ԃ��Ȃ���΂Ȃ�܂���
	virtual void draw(SHADER* shader) = 0;//pos()�������wh()*scale()�̃T�C�Y�̉摜���`�悳��Ȃ���΂Ȃ�܂���
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
��{�AUI�̕`�揇��add���鏇�Ԃ���Ȃ��e�q�̊֌W�ōs��
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
	//�d�Ȃ��Ă����Ԏ�O��UI��T��
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

	//true�ł���UI�𖳌��ɂ���
	void setIsDisable(bool isDisable) { IsDisable = isDisable; }
	//true�ł���UI�̎q��e�̓����蔻��Ő�������
	void setIsChildCollisionRestrict(bool isChildCollisionRestrict) { IsChildCollisionRestrict = isChildCollisionRestrict; }
	//true�ł���UI�̓����蔻��𖳌��ɂ���
	void setIsCollisionDisable(bool isCollisionDisable) { IsCollisionDisable = isCollisionDisable; }
	//true�ł���UI�̔��肪�S���ɂȂ�
	void setIsUnconditionalCollisionHit(bool isUnconditionalCollisionHit) { IsUnconditionalCollisionHit = isUnconditionalCollisionHit; }
	//true�Őe���玩���J������Ȃ��悤�ɂȂ�
	void setIsReleaseDisable(bool isReleaseDisable) { IsReleaseDisable = isReleaseDisable; }
	//�e��ݒ肷��
	void setParent(UI* parent) { Parent = parent; }
	//�x�N�^�[�d�l�ɂ��d���Ȃ�\������
	void addChilds(UI* child);
	//�x�N�^�[�d�l�ɂ��v�f���������Əd���Ȃ�\������B�܂��A���Ԃ�����ւ��
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
	//UiManager�����Ƃ���delete�̍ۂ�UiManager�ʒm����
	void setUiManager(UI_MANAGER* uiManager) { UiManager = uiManager; }
	//�폜
	void Delete();
	//���ۂɊJ������
	void DeleteUpdate();

	//�Q�b�^�[
	bool isDisable()const { return IsDisable; }
	bool isChildCollisionRestrict()const { return IsChildCollisionRestrict; }
	bool isCollisionDisable()const { return IsCollisionDisable; }
	bool isUnconditionalCollisionHit()const { return IsUnconditionalCollisionHit; }
	bool isReleaseDisable()const { return IsReleaseDisable; }
	VECTOR2 pos() const{ return Pos; }
	VECTOR2 parentPos()const { return ParentPos; }
	//��Έʒu
	VECTOR2 absolutePos()const { return Pos * ParentScale + ParentPos; }
	//��Έʒu�ŃR���W�����̒��S�̈ʒu��Ԃ�
	VECTOR2 centerPos()const;

	VECTOR2 scale() const{ return Scale; }
	VECTOR2 parentScale() const{ return ParentScale; }
	//����UI��`�悷��ۂ̃X�P�[���̗݌v
	VECTOR2 absoluteScale()const { return Scale* ParentScale; }
	//����UI��̍��W����ʑS�̂̍��W�ɕϊ�����
	VECTOR2 localPosToWorldPos(const VECTOR2& localPos)const;
	//��ʑS�̂̍��W������UI��̍��W�ɕϊ�����
	VECTOR2 worldPosToLocalPos(const VECTOR2& worldPos)const;
	UI_DRAWER* drawer() const { return Drawer; }
	COLLISION2D_RECT* collision()const { return Collision;}
	std::vector<UI*>* child() { return &Childs;}
	bool isDelete() { return IsDelete; }
	UI* parent() { return Parent; }
	UI_ANNOTATION* annotation() { return &Annotation; }
private:
	//�q�̈ʒu���X�V
	void setPosChild(const VECTOR2& pos);
	//�q�̃X�P�[�����X�V
	void setScaleChild(const VECTOR2& scale);
	//�e����̈ʒu�i�݌v�j(�e�̂���̃X�P�[����Z�ς�)
	VECTOR2 ParentPos;
	//�e����̃X�P�[���i�݌v�j
	VECTOR2 ParentScale;
	//���Έʒu
	VECTOR2 Pos;
	//�����ɂ�����X�P�[��
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
	//�񊈐����H�itrue���ƕ`��Ɣ��肪�����ɂȂ�j
	bool IsDisable = false;
	//�e�̓����蔻��Ŏq�̔���𐧌����邩�H
	bool IsChildCollisionRestrict = false;
	//�����̓����蔻�肪�������H
	bool IsCollisionDisable = false;
	//true�Ő�Γ�����悤�ɂȂ�i�����N���b�N���ė~�����Ȃ����Ƃ��ɂ������ꂽUI�����ށj
	bool IsUnconditionalCollisionHit = false;
	//�e���玩���J������Ȃ��悤�ɂ���
	bool IsReleaseDisable = false;
	//����ς݂�
	bool IsDelete = false;
	//�o�^������Ă���}�l�[�W���[
	UI_MANAGER* UiManager = nullptr;
	std::string Id;
};

