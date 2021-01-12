#pragma once
#include "UI.h"
namespace UI_FUNC_ATTACHER {
	template<class T>
	//�w���ui�ɁA�Ȃ�����F���ς��@�\��t���܂�
	//OverlapIn,OverlapOut
	static void OverlapColorChange(UI* ui, T* drawer, const COLOR& color) {
		ui->setOverlapIn([drawer, color]() {drawer->setColor(color);});
		ui->setOverlapOut([drawer]() {drawer->setColor(COLOR(1.0f, 1.0f, 1.0f, 1.0f));});
	};
	//�w���ui�ɁA�Ȃ�����F���ς��@�\��t���܂�
	//OverlapIn,OverlapOut
	template<class T>
	static void OverlapColorChange(UI* ui, T* drawer,const COLOR& defaultColor, const COLOR& changeColor) {
		ui->setOverlapIn([drawer, changeColor]() {drawer->setColor(changeColor);});
		ui->setOverlapOut([drawer, defaultColor]() {drawer->setColor(defaultColor);});
	};

	//�w���ui�ɁA�Ȃ�����Ԃ��Ȃ�@�\��t���܂�
	//OverlapIn,OverlapOut
	template<class T>
	static void OverlapColorChange(UI* ui, T* drawer) {
		ui->setOverlapIn([drawer]() {drawer->setColor(COLOR(1.0f, 0.0f, 0.0f, 1.0f));});
		ui->setOverlapOut([drawer]() {drawer->setColor(COLOR(1.0f, 1.0f, 1.0f, 1.0f));});
	};

	//�w���ui�ɁA�Ȃ����甖���Ȃ�@�\��t���܂�
	//OverlapIn,OverlapOut
	template<class T>
	static void OverlapAlphaColorChange(UI* ui, T* drawer) {
		ui->setOverlapIn([drawer]() {drawer->setColor(COLOR(0.0f, 0.0f, 0.0f, 0.7f));});
		ui->setOverlapOut([drawer]() {drawer->setColor(COLOR(1.0f, 1.0f, 1.0f, 1.0f));});
	};
	//�w���ui�ɁA�Ȃ����玞�ԂŐԂ��Ȃ�@�\��t���܂�
	template<class T>
	static void OverlapAlphaColorTemporalChange(UI* ui, T* drawer,int inFrame) {
		ui->setOverlapUpdate([ui,drawer, inFrame]() {
			drawer->setColor(COLOR(1.0f, drawer->color().g - 1.0f / inFrame, drawer->color().b - 1.0f / inFrame, 1.0f));}
		);
		ui->setOverlapOut([drawer]() {
			drawer->setColor(COLOR(1.0f, 1.0f, 1.0f, 1.0f));}
		);
	};

}