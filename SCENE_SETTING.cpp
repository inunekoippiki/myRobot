#include "../Library/WINDOW.h"
#include "../Library/GRAPHIC.h"
#include "../Library/INDEV.h"
#include "../Library/DEBUG_STR.h"
#include "SCENE_FACTORY.h"
#include "FADE.h"
#include "UI_FACTORY.h"
#include "SCENE_MANAGER.h"
#include "SOUND_MANAGER.h"
#include "SCENE_SETTING.h"
SCENE_SETTING::SCENE_SETTING(SCENE_MANAGER* sceneManager) :
	SceneManager(sceneManager) {
	UiRoot = UI_FACTORY::instanceEmpty();

	//UI�}�l�[�W���[�Ƀ��[�gUI���Z�b�g
	UiManager.setRootUi(UiRoot);
	//���j���[UI�����
	UiMenu.create(c(), font());
	UiMenu.listAdd(c(), font(), "�^�C�g����", [this]() {onClickToTitle(); });
	UiRoot->addChilds(UiMenu.rootUi());
	//�e�ݒ荀�ڂ�UI�����
	{
		VECTOR2 offset = VECTOR2(256.0f, 96.0f);
		VECTOR2 shift = VECTOR2(0.0f, 128.0f);

		SETTING* setting = commonData()->setting();
		VolumeSlider.create(c(), font(), "�S�̉���", setting->volume(), true);
		VolumeSlider.rootUi()->setPos(offset + shift * 0.0f);
		UiRoot->addChilds(VolumeSlider.rootUi());

		SoundVolumeSlider.create(c(), font(), "SE����", setting->soundVolume(), true);
		SoundVolumeSlider.rootUi()->setPos(offset + shift * 1.0f);
		UiRoot->addChilds(SoundVolumeSlider.rootUi());

		BgmVolumeSlider.create(c(), font(), "BGM����", setting->bgmVolume(), true);
		BgmVolumeSlider.rootUi()->setPos(offset + shift * 2.0f);
		UiRoot->addChilds(BgmVolumeSlider.rootUi());

		AimSensitivitySlider.create(c(), font(), "���_���x", setting->aimSensitivity(), true);
		AimSensitivitySlider.rootUi()->setPos(offset + shift * 3.0f);
		UiRoot->addChilds(AimSensitivitySlider.rootUi());

		OneFrameProcessSlider.create(c(), font(), "1�t���[���v���Z�X�����", setting->oneFrameProcess(), true);
		OneFrameProcessSlider.rootUi()->setPos(offset + shift * 4.0f);
		UiRoot->addChilds(OneFrameProcessSlider.rootUi());

		DebugDispCheckBox.create(c(), font(), "�f�o�b�O�\��");
		DebugDispCheckBox.rootUi()->setPos(offset + shift * 5.0f);
		UiRoot->addChilds(DebugDispCheckBox.rootUi());
		DebugDispCheckBox.setCheck(setting->debugDisp()->isCheck());
	}
	//��
	SoundButton = c()->sound("button");
	//�t�F�[�h�C��
	SceneManager->fade()->inTrigger();
}

SCENE_SETTING::~SCENE_SETTING() {
	delete UiRoot;
}

void SCENE_SETTING::proc(){
	WINDOW* w = WINDOW::instance();
	GRAPHIC* g = GRAPHIC::instance();
	INDEV* indev = INDEV::instance();
	DEBUG_STR* ds = DEBUG_STR::instance();
	indev->getState();

	VolumeSlider.update();
	SoundVolumeSlider.update();
	BgmVolumeSlider.update();
	AimSensitivitySlider.update();
	OneFrameProcessSlider.update();

	SETTING* setting = commonData()->setting();
	setting->volume()->set((int)VolumeSlider.value());
	setting->soundVolume()->set((int)SoundVolumeSlider.value());
	setting->bgmVolume()->set((int)BgmVolumeSlider.value());
	setting->aimSensitivity()->set((int)AimSensitivitySlider.value());
	setting->oneFrameProcess()->set((int)OneFrameProcessSlider.value());
	setting->debugDisp()->set(DebugDispCheckBox.isCheck());

	SOUND_MANAGER::instance()->load(setting);

	g->clearTarget(COLOR(1.0f, 0.4f, 0.4f, 1.0f));
	UiManager.update();
	SHADER* shader = image2d();
	BEGIN_PATH_
		UiRoot->draw(shader);
	END_PATH_
		BEGIN_PATH_
		ds->draw(shader);
	SceneManager->fade()->draw(shader);
	END_PATH_
		g->present();
	if (SceneManager->fade()->outEndFlag()) {
		(this->*NextSceneMethod)();
	}
}

void SCENE_SETTING::onClickToTitle(){
	NextSceneMethod = &SCENE_SETTING::nextSceneTitle;
	SceneManager->fade()->outTrigger();
	SOUND_MANAGER::instance()->playSound(SoundButton);
	
}

void SCENE_SETTING::nextSceneTitle(){
	SCENE_MANAGER* sceneManager = SceneManager;
	sceneManager->setNextScene(SCENE_FACTORY::instanceTitle(sceneManager));
}
