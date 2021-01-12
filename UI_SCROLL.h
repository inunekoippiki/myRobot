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
	//�w��i���ōX�V����
	void scrollUpdate(int stepNum);
	//�w�荂���ōX�V����
	void scrollUpdate(float height);
	UI* rootUi() { return RootUi; }
	UI* seekBarBackUi() { return SeekBarBackUi; }
	UI* seekBarUi() { return SeekBarUi; }
	UI* listBackUi() { return ListBackUi; }
	UI* scrollUpUi() { return ScrollUpUi; }
	UI* scrollDownUi() { return ScrollDownUi; }
	std::vector<UI*>* listUi() { return &ListUi; }
	int stepNum()const { return StepNum; }
	//�X�N���[���ɗv�f��ǉ�����
	void add(UI* ui);
	//�X�N���[������Y������UI������
	void remove(UI* ui);
	using NODE_LIST = std::vector<UI*>;
private:
	//�V�[�N�o�[�̋����ݒ�i�}�E�X�̈ړ��ʂŌv�Z�j
	void setSeekBarFunc_0();
	//�V�[�N�o�[�̋����ݒ�(���������ꏊ����̑��΋����Ōv�Z)
	void setSeekBarFunc_1();
	//�\���ł���i��
	int MaxStepNum = 0;
	//���ݕ\����i��
	int StepNum = 0;
	//�X�N���[���X�s�[�h
	float ScrollSpeed = 0.0f;
	//���t���[���X�N���[���X�s�[�h���Z��
	float ScrollSpeedAdd = 0.0f;
	//
	float ScrollFraction = 0.0f;
	UI* RootUi = nullptr;
	UI* SeekBarBackUi = nullptr;
	UI* SeekBarUi = nullptr;
	UI* ListBackUi = nullptr;
	UI* ScrollUpUi = nullptr;
	UI* ScrollDownUi = nullptr;
	//�X�N���[�����X�g�̑S�Ă̗v�f
	NODE_LIST ListUi;
	//�}�E�X���������ꂽ�ʒu
	VECTOR2 MouseDownPos;
	//�}�E�X���������ꂽ�Ƃ��̕\���i��
	int MouseDownStepNum = 0;
	UI* ChoiceUi = nullptr;
	UI* DownUi = nullptr;
	
};

