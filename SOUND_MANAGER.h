#pragma once
#include "../Library/VECTOR3.h"
#include "../Library/SINGLETON.h"
class SETTING;
class SOUND;
class SOUND_MANAGER:public SINGLETON<SOUND_MANAGER>{
public:
	SOUND_MANAGER();
	~SOUND_MANAGER();
	void update();//BGMフェードとか用
	void stopSound(SOUND* sound);
	void playSound(SOUND* sound);
	void playSound(SOUND* sound,const VECTOR3& pos);
	void playSoundLoop(SOUND* sound);
	void playSoundLoop(SOUND* sound, const VECTOR3& pos);
	void setVolumeSE(SOUND* sound);
	void setVolumeBGM(SOUND* sound);

	//音量の0~1を-10000~0に変換
	long cvt(float val);
	//音量の-10000~0を0~1に変換
	float unCvt(long val);

	//セッター
	void setMasterVolume(float volume);
	void setSEVolume(float volume);
	void setBGMVolume(float volume);
	void stopBgm();
	void setNextBgm(SOUND* sound);
	void setPlayerPos(const VECTOR3& playerPos) { PlayerPos = playerPos; }
	void load(SETTING* setting);
	//ゲッター
	long masterVolume() { return (long)MasterVolume; }

	void debug();
private:
	VECTOR3 PlayerPos;
	float Attenuation = 0.0f;
	float MasterVolume = 0;//0min 1max
	float SEVolume = 0;
	float BGMVolume = 0;
	//内部で使う計算済み値
	long _MasterVolume = 0;//-10000min 0max
	long _SEVolume = 0;
	long _BGMVolume = 0;
	//フェード関連
	float FeedSpped = 0.0f;
	SOUND* NewBgm = nullptr;
	float NewBgmVolume = 0;
	SOUND* NowBgm = nullptr;
	float NowBgmVolume = 0;

	bool stopFlag = false;

};

