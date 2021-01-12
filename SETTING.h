#pragma once
class CONTAINER;
class SETTING_VALUE_SLIDE {
public:
	SETTING_VALUE_SLIDE();
	~SETTING_VALUE_SLIDE();
	void init(int maxValue, int minValue, int changeAmount);
	int value()const;
	void set(int value);
	void upValue();
	void downValue();
	int maxValue()const { return MaxValue; }
	int minValue()const { return MinValue; }
	int changeAmount()const {return ChangeAmount;}
	//値の割合を0~1で返す
	float percentage()const;
private:
	int Value = 0;
	int MaxValue = 0;
	int MinValue = 0;
	int ChangeAmount = 0;
};

class SETTING_VALUE_CHECK {
public:
	SETTING_VALUE_CHECK();
	~SETTING_VALUE_CHECK();
	void init(bool isCheck);
	bool isCheck()const;
	void set(bool isCheck);
	void check();
private:
	bool IsCheck = false;
};

class SETTING {
public:
	SETTING();
	~SETTING();
	void create(CONTAINER* c);
	//ディレクトリからロード
	void load(CONTAINER* c);
	//ディレクトリにセーブ
	void save();
	SETTING_VALUE_SLIDE* volume() { return &Volume; }
	SETTING_VALUE_SLIDE* soundVolume() { return &SoundVolume; }
	SETTING_VALUE_SLIDE* bgmVolume() { return &BgmVolume; }
	SETTING_VALUE_SLIDE* aimSensitivity() { return &AimSensitivity; }
	SETTING_VALUE_SLIDE* oneFrameProcess() { return &OneFrameProcess; }
	SETTING_VALUE_CHECK* debugDisp() { return &DebugDisp; }
private:
	SETTING_VALUE_SLIDE Volume;
	SETTING_VALUE_SLIDE SoundVolume;
	SETTING_VALUE_SLIDE BgmVolume;
	SETTING_VALUE_SLIDE AimSensitivity;
	SETTING_VALUE_SLIDE OneFrameProcess;
	SETTING_VALUE_CHECK DebugDisp;

};
