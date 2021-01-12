#pragma once
class IMAGE_2D;
class UI;
class PROCESS_NODE_MANAGER;
class SCENE_ROUND;
class ROBOT_PROCESSOR;
class SOUND;
class SCENE_ROUND_EDIT {
public:
	SCENE_ROUND_EDIT();
	~SCENE_ROUND_EDIT();
	void create(SCENE_ROUND* sceneRound, UI* uiRoot, COMMON_DATA* commonData);
	void update();
	void draw();
	void onEnter();
	void onExit();
	void setModuleScroll(ROBOT_PROCESSOR* robotProcessor);
	PROCESS_NODE_MANAGER* processNodeManager() { return ProcessNodeManager; }
private:
	SCENE_ROUND* SceneRound = nullptr;
	CONTAINER* C = nullptr;
	STATIC_FONT* Font = nullptr;
	IMAGE_2D* Image2dShader = nullptr;
	PROCESS_NODE_MANAGER* ProcessNodeManager = nullptr;
	UI* EditToPlaySwitchingButtonUi = nullptr;
	//‰¹
	SOUND* SoundBgm = nullptr;
};

