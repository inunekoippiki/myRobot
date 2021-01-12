#pragma warning (disable:4996)
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include "../Library/CONTAINER.h"
#include "../Library/DATA.h"
#include "SETTING.h"
SETTING::SETTING() {
}

SETTING::~SETTING() {
	save();
}

void SETTING::create(CONTAINER* c){

	Volume.init(
		c->data("SETTING::VolumeChangeMax"),
		c->data("SETTING::VolumeChangeMin"),
		c->data("SETTING::VolumeChangeAmount")
	);
	Volume.set(c->data("SETTING::DefaultVolume"));

	SoundVolume.init(
		c->data("SETTING::SoundVolumeChangeMax"),
		c->data("SETTING::SoundVolumeChangeMin"),
		c->data("SETTING::SoundVolumeChangeAmount")
	);
	SoundVolume.set(c->data("SETTING::DefaultSoundVolume"));

	BgmVolume.init(
		c->data("SETTING::BgmVolumeChangeMax"),
		c->data("SETTING::BgmVolumeChangeMin"),
		c->data("SETTING::BgmVolumeChangeAmount")
	);
	BgmVolume.set(c->data("SETTING::DefaultBgmVolume"));

	AimSensitivity.init(
		c->data("SETTING::AimSensitivityChangeMax"),
		c->data("SETTING::AimSensitivityChangeMin"),
		c->data("SETTING::AimSensitivityChangeAmount")
	);
	AimSensitivity.set(c->data("SETTING::DefaultAimSensitivity"));

	OneFrameProcess.init(
		c->data("SETTING::OneFrameProcessChangeMax"),
		c->data("SETTING::OneFrameProcessChangeMin"),
		c->data("SETTING::OneFrameProcessChangeAmount")
	);
	OneFrameProcess.set(c->data("SETTING::DefaultOneFrameProcess"));

	DebugDisp.init((int)c->data("SETTING::DefaultDebugDisp"));
}

void SETTING::load(CONTAINER* c) {
	std::ifstream ifs("saveData/setting.txt");
	if (!ifs.is_open()) {
		//ファイルが無かった場合デフォルト値
		Volume.set(c->data("SETTING::DefaultVolume"));
		SoundVolume.set(c->data("SETTING::DefaultSoundVolume"));
		BgmVolume.set(c->data("SETTING::DefaultBgmVolume"));
		AimSensitivity.set(c->data("SETTING::DefaultAimSensitivity"));
		OneFrameProcess.set(c->data("SETTING::DefaultOneFrameProcess"));
		DebugDisp.set((int)c->data("SETTING::DefaultDebugDisp"));
	}
	else {
		int buffer = 0;
		ifs >> buffer;
		Volume.set(buffer);
		ifs >> buffer;
		SoundVolume.set(buffer);
		ifs >> buffer;
		BgmVolume.set(buffer);
		ifs >> buffer;
		AimSensitivity.set(buffer);
		ifs >> buffer;
		OneFrameProcess.set(buffer);
		ifs >> buffer;
		DebugDisp.set(buffer);
		ifs.close();
	}
}

void SETTING::save() {
	std::ofstream ofs("saveData/setting.txt");
	ofs << Volume.value() << std::endl;
	ofs << SoundVolume.value() << std::endl;
	ofs << BgmVolume.value() << std::endl;
	ofs << AimSensitivity.value() << std::endl;
	ofs << OneFrameProcess.value() << std::endl;
	ofs << (int)DebugDisp.isCheck()<<std::endl;
	ofs.close();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SETTING_VALUE_SLIDE::SETTING_VALUE_SLIDE() {
}

SETTING_VALUE_SLIDE::~SETTING_VALUE_SLIDE() {
}

void SETTING_VALUE_SLIDE::init(int maxValue, int minValue, int changeAmount) {
	MaxValue = maxValue;
	MinValue = minValue;
	ChangeAmount = changeAmount;
}

int SETTING_VALUE_SLIDE::value()const {
	return Value;
}

void SETTING_VALUE_SLIDE::set(int value) {
	Value = std::min(std::max(value, MinValue), MaxValue);
}

void SETTING_VALUE_SLIDE::upValue() {
	set(value() + ChangeAmount);
}

void SETTING_VALUE_SLIDE::downValue() {
	set(value() - ChangeAmount);
}

float SETTING_VALUE_SLIDE::percentage()const {
	int difference = MaxValue - MinValue;
	return (float)(Value - MinValue) / difference;
}

SETTING_VALUE_CHECK::SETTING_VALUE_CHECK(){
}

SETTING_VALUE_CHECK::~SETTING_VALUE_CHECK(){
}

void SETTING_VALUE_CHECK::init(bool isCheck){
	IsCheck = isCheck;
}

bool SETTING_VALUE_CHECK::isCheck() const{
	return IsCheck;
}

void SETTING_VALUE_CHECK::set(bool isCheck){
	IsCheck = isCheck;
}

void SETTING_VALUE_CHECK::check(){
	IsCheck = !IsCheck;
}
