#pragma once
#include "UI.h"
namespace UI_FUNC_ATTACHER {
	template<class T>
	//指定のuiに、翳したら色が変わる機能を付けます
	//OverlapIn,OverlapOut
	static void OverlapColorChange(UI* ui, T* drawer, const COLOR& color) {
		ui->setOverlapIn([drawer, color]() {drawer->setColor(color);});
		ui->setOverlapOut([drawer]() {drawer->setColor(COLOR(1.0f, 1.0f, 1.0f, 1.0f));});
	};
	//指定のuiに、翳したら色が変わる機能を付けます
	//OverlapIn,OverlapOut
	template<class T>
	static void OverlapColorChange(UI* ui, T* drawer,const COLOR& defaultColor, const COLOR& changeColor) {
		ui->setOverlapIn([drawer, changeColor]() {drawer->setColor(changeColor);});
		ui->setOverlapOut([drawer, defaultColor]() {drawer->setColor(defaultColor);});
	};

	//指定のuiに、翳したら赤くなる機能を付けます
	//OverlapIn,OverlapOut
	template<class T>
	static void OverlapColorChange(UI* ui, T* drawer) {
		ui->setOverlapIn([drawer]() {drawer->setColor(COLOR(1.0f, 0.0f, 0.0f, 1.0f));});
		ui->setOverlapOut([drawer]() {drawer->setColor(COLOR(1.0f, 1.0f, 1.0f, 1.0f));});
	};

	//指定のuiに、翳したら薄くなる機能を付けます
	//OverlapIn,OverlapOut
	template<class T>
	static void OverlapAlphaColorChange(UI* ui, T* drawer) {
		ui->setOverlapIn([drawer]() {drawer->setColor(COLOR(0.0f, 0.0f, 0.0f, 0.7f));});
		ui->setOverlapOut([drawer]() {drawer->setColor(COLOR(1.0f, 1.0f, 1.0f, 1.0f));});
	};
	//指定のuiに、翳したら時間で赤くなる機能を付けます
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