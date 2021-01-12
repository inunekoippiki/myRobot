#include  <algorithm>
#include <string>
#include "../Library/CONTAINER.h"
#include "../Library/INDEV.h"
#include "../Library/DEBUG_STR.h"
#include "INPUT_COMMON.h"
#include "COLLISION2D_POINT.h"
#include "UI.h"
#include "UI_FACTORY.h"
#include "UI_SCROLL.h"
UI_SCROLL::UI_SCROLL() {
}

UI_SCROLL::~UI_SCROLL() {
	ListBackUi->child()->clear();
	SAFE_DELETE( RootUi);
	for (auto& i : ListUi) {
		SAFE_DELETE (i);
	}
}

//���ۂ͐e��RootUi���X�ɐe�ɓo�^���邱�Ƃŕ`�悷�邱�ƂɂȂ肻��
void UI_SCROLL::draw(SHADER* shader){
	RootUi->draw(shader);
}

void UI_SCROLL::create(CONTAINER* c, int maxStepNum){
	int num = 256;
	ListUi.reserve(num);
	for (int i = 0;i < num;i++) {
		UI* fontUi = new UI;
		DRAWER::FONT* font = new DRAWER::FONT;
		font->create("Assets/font/PixelMplus12-Bold.ttf", "PixelMplus12", std::to_string(i).c_str(), 64);
		font->setScale(VECTOR2(1.0f, 1.0f));
		font->setPos(VECTOR2(0.0f, 0.0f));
		font->setMaxWidth(64.0f);
		font->setDrawMethod(DRAWER::FONT::drawMethodAdjustDraw_Over());
		fontUi->create(font);
		fontUi->setOverlapIn([font]() {font->setColor(COLOR(1.0f, 0.0f, 0.0f, 1.0f));});
		fontUi->setOverlapOut([font]() {font->setColor(COLOR(1.0f, 1.0f, 1.0f, 1.0f));});
		UI* backUi = UI_FACTORY::instance(c->texture("enterIcon"), VECTOR2(0, 0), VECTOR2::one());
		backUi->addChilds(fontUi);
		ListUi.push_back(backUi);
	}

	ScrollDownUi = UI_FACTORY::instance(c->texture("noIcon"), VECTOR2(500, 0), VECTOR2::one());
	ScrollUpUi = UI_FACTORY::instance(c->texture("noIcon"), VECTOR2(500, 300), VECTOR2::one());
	SeekBarUi = UI_FACTORY::instance(c->texture("plusIcon"), VECTOR2(100, 110), VECTOR2::one());
	SeekBarBackUi = UI_FACTORY::instance(c->texture("SkillStringIcon"), VECTOR2(300, 100), VECTOR2::one());
	ListBackUi = UI_FACTORY::instance(c->texture("statusStringIcon"), VECTOR2(100, 100), VECTOR2::one());
	RootUi = UI_FACTORY::instance(c->texture("skillIcon1"), VECTOR2(50, 50), VECTOR2::one());
	create(RootUi, SeekBarBackUi, SeekBarUi, ListBackUi, ScrollUpUi, ScrollDownUi, std::move(ListUi), maxStepNum);
}

void UI_SCROLL::create(UI* rootUi, UI* seekBarBackUi, UI* seekBarUi, UI* listBackUi, UI* scrollUpUi, UI* scrollDownUi, std::vector<UI*>&& listUi, int maxStepNum){
	MaxStepNum = maxStepNum;
	RootUi = rootUi;
	RootUi->setIsChildCollisionRestrict(true);
	RootUi->setIsReleaseDisable(true);
	SeekBarBackUi = seekBarBackUi;
	SeekBarUi = seekBarUi;
	ListBackUi = listBackUi;
	ScrollUpUi = scrollUpUi;
	ScrollDownUi = scrollDownUi;
	ListUi = std::move(listUi);
	ScrollSpeedAdd = 0.01f;
	setSeekBarFunc_1();
	ScrollUpUi->setDragUpdate([this]() {
		this->ScrollSpeed += this->ScrollSpeedAdd;
		ScrollFraction += this->ScrollSpeed;
		this->scrollUpdate(this->stepNum() - (int)ScrollFraction);
		ScrollFraction -= (int)ScrollFraction;}
	);
	ScrollDownUi->setDragUpdate([this]() {
		this->ScrollSpeed += this->ScrollSpeedAdd;
		ScrollFraction += this->ScrollSpeed;
		this->scrollUpdate(this->stepNum() + (int)ScrollFraction);
		ScrollFraction -= (int)ScrollFraction;}
	);
	ScrollUpUi->setPushFunc([this]() {
		this->ScrollSpeed = 0.0f;
		ScrollFraction = 0.0f;
		this->scrollUpdate(this->stepNum() - 1);}
	);
	ScrollDownUi->setPushFunc([this]() {
		this->ScrollSpeed = 0.0f;
		ScrollFraction = 0.0f;
		this->scrollUpdate(this->stepNum() + 1);}
	);
	SeekBarBackUi->addChilds(SeekBarUi);
	RootUi->child()->reserve(4);
	RootUi->addChilds(SeekBarBackUi);
	RootUi->addChilds(ListBackUi);
	RootUi->addChilds(ScrollDownUi);
	RootUi->addChilds(ScrollUpUi);
	scrollUpdate(0);

}

//�I��UI�͈�ӂɑI�΂��B���ێg���Ƃ���RootUi�ɂ͐e�����݂��邾�낤�����̏ꍇ�����ɂ��̊֐�������̂͂�������
void UI_SCROLL::update(){
	INDEV* indev = INDEV::instance();
	COLLISION2D_POINT mousePoint;
	mousePoint.setPos(INPUT_COMMON::MousePosition(indev));
	UI* overlapUi = nullptr;
	RootUi->OverlapUi(&mousePoint, overlapUi);

	if (overlapUi != ChoiceUi) {
		if (overlapUi != nullptr) {
			overlapUi->overlapIn();
		}
		if (ChoiceUi != nullptr) {
			ChoiceUi->overlapOut();
		}
		ChoiceUi = overlapUi;
	}
	if (indev->isTrigger(MOUSE_LBUTTON)) {
		DownUi = overlapUi;
	}
	if (DownUi != nullptr) {
		DownUi->dragUpdate();
	}
	if (indev->isUp(MOUSE_LBUTTON)) {
		if (DownUi == overlapUi) {
			if (overlapUi != nullptr) {
				overlapUi->pushFunc();
			}
		}
		DownUi = nullptr;
	}
}

void UI_SCROLL::scrollUpdate(int stepNum) {
	if (stepNum < 0) { stepNum = 0; }
	if (ListUi.size() < stepNum + MaxStepNum) { stepNum = (int)ListUi.size() - MaxStepNum; }
	int loop = MaxStepNum;
	if (ListUi.size() < MaxStepNum) { 
		loop = (int)ListUi.size();
		stepNum = 0; 
	}
	StepNum = stepNum;
	float py = 0;
	ListBackUi->child()->clear();
	for (int i = 0;i < loop;i++) {
		int idx = i + stepNum;
		ListBackUi->addChilds(ListUi[idx]);
		ListUi[idx]->setPos(VECTOR2(0.0f, py));
		py += ListUi[idx]->drawer()->wh().y * ListUi[idx]->scale().y;
	}
	SeekBarUi->setPos(VECTOR2(0.0f, (float)stepNum / (ListUi.size() - MaxStepNum) * (SeekBarBackUi->drawer()->wh().y- SeekBarUi->drawer()->wh().y)));
}

void UI_SCROLL::scrollUpdate(float height){
	//�X�N���[���o�[�̓������镝
	float scrollBerHeight = (SeekBarBackUi->drawer()->wh().y * SeekBarBackUi->drawer()->scale().y - SeekBarUi->drawer()->wh().y * SeekBarUi->drawer()->scale().y);
	//�}�E�X���������ꂽ�ꏊ����̈ړ���
	float moveAmount = height - MouseDownPos.y;
	//��ԏォ���ԉ��܂ŃX�N���[���ł���i��
	int scrollElement = ListUi.size() - MaxStepNum;
	//�i����1�Ƃ��ă}�E�X�̈ړ��ʂ�ϊ�����
	height = moveAmount * scrollElement / scrollBerHeight;
	int stepNum = (int)height;
	//�}�E�X�������������_�̒i�������Z
	stepNum = stepNum + MouseDownStepNum;

	if (stepNum < 0) { stepNum = 0; }
	if (ListUi.size() < stepNum + MaxStepNum) { 
		stepNum = (int)ListUi.size() - MaxStepNum;
	}
	int loop = MaxStepNum;
	if (ListUi.size() < MaxStepNum) {
		loop = (int)ListUi.size();
		stepNum = 0;
	}
	StepNum = stepNum;
	float py = 0;
	//�\������v�f���X�V
	ListBackUi->child()->clear();
	for (int i = 0;i < loop;i++) {
		int idx = i + stepNum;
		ListBackUi->addChilds(ListUi[idx]);
		ListUi[idx]->setPos(VECTOR2(0.0f, py));
		py += ListUi[idx]->drawer()->wh().y * ListUi[idx]->scale().y;
	}
	height = std::clamp((height + MouseDownStepNum), 0.0f, (float)(ListUi.size() - MaxStepNum));
	SeekBarUi->setPos(VECTOR2(0.0f, height / (ListUi.size() - MaxStepNum) * (SeekBarBackUi->drawer()->wh().y - SeekBarUi->drawer()->wh().y)));

}

void UI_SCROLL::add(UI* ui){
	ListUi.push_back(ui);
	scrollUpdate(StepNum);
}

void UI_SCROLL::remove(UI* ui){
	for (auto iterator = ListUi.begin();iterator != ListUi.end();iterator++) {
		if (*iterator == ui) {
			ListUi.erase(iterator);
			break;
		}
	}
	scrollUpdate(StepNum);
}

void UI_SCROLL::setSeekBarFunc_0(){
	SeekBarUi->setDragUpdate([this]() {
		//�X�N���[���o�[�̓������镝
		float scrollBerHeight = (SeekBarBackUi->drawer()->wh().y * SeekBarBackUi->drawer()->scale().y - SeekBarUi->drawer()->wh().y * SeekBarUi->drawer()->scale().y);
		//��ԏォ���ԉ��܂ŃX�N���[���ł���i��
		int scrollElement = ListUi.size() - MaxStepNum;
		float scrollAmount = (INPUT_COMMON::MouseRelativeValueY(INDEV::instance()) * scrollElement / scrollBerHeight);
		ScrollFraction += scrollAmount;
		this->scrollUpdate(this->stepNum() + (int)(ScrollFraction));
		ScrollFraction -= (int)ScrollFraction;}
	);
}

void UI_SCROLL::setSeekBarFunc_1(){
	SeekBarUi->setDownFunc([this]() {
		MouseDownPos = INPUT_COMMON::MousePosition(INDEV::instance());
		MouseDownStepNum = StepNum;}
	);
	SeekBarUi->setDragUpdate([this]() {
		this->scrollUpdate(INPUT_COMMON::MousePositionY(INDEV::instance()));
	});
	SeekBarUi->setDragEndFunc([this]() {
		this->scrollUpdate(this->stepNum());
	});
}
