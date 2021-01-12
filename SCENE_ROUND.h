#pragma once
#include <variant>
#include "../Library/RENDER_TARGET_TEXTURE.h"
#include "../Library/VECTOR3.h"
#include "../Library/MATRIX.h"
#include "SCENE.h"
#include "UI.h"
#include "UI_MANAGER.h"
#include "UI_MENU.h"
#include "COLLISION_MANAGER.h"
#include "UI_ANNOTATION_MANAGER.h"
#include "SCENE_ROUND_EDIT.h"
#include "SCENE_ROUND_PLAY.h"
#include "ROBOT_PROCESSOR.h"
#include "HELP_WINDOW.h"
class SCENE_MANAGER;
class IMAGE_2D;
class SOFT_SHADOW;
class PROCESS_NODE_MANAGER;
namespace ENTITY{
	class TERRAIN_FLOOR;
	class ROBOT;
}
namespace DRAWER {
	class DRAWERS_SHADER;
	class STATIC_FONT;
	class BASE;
}
class SOUND;
class SCENE_ROUND :public SCENE {
public:
	SCENE_ROUND(SCENE_MANAGER* sceneManager, const std::string& mapFileName, const std::string& missionFileName, int stageIdx);
	~SCENE_ROUND();
	void proc();
	void startPlay();
	void startEdit();
	void uiDraw();
	void screenTransition();
	void clearRound();
	bool isExistNextRound()const;
	int stageIdx()const { return StageIdx; }
	void nextStage();
	void onClickHelpButton();
	const std::vector<PROCESS_NODE*>& processNodeList();
	SCENE_MANAGER* sceneManager() { return SceneManager; }
	static DRAWER::DRAWERS_SHADER* DebugDrawerImage3d;
	using NEXT_SCENE_METHOD = void (SCENE_ROUND::*)();
private:
	void onClickToTitle();
	void onClickToRoundSelect();
	void create(SCENE_MANAGER* sceneManager, const std::string& mapFileName, const std::string& missionFileName);
	void transitionUpdate();
	void transitionDraw(SHADER* shader);
	void nextSceneTitle();
	void nextSceneRoundSelect();
	//リソース
	SCENE_MANAGER* SceneManager = nullptr;
	SOFT_SHADOW* SoftShadowShader = nullptr;
	//次シーン
	NEXT_SCENE_METHOD NextSceneMethod = nullptr;
	//UI
	UI_MANAGER UiManager;
	UI* RootUi = nullptr;
	UI_MENU MenuUi;
	UI* HelpButtonUi = nullptr;

	UI_ANNOTATION_MANAGER UiAnnotationManager;
	RENDER_TARGET_TEXTURE TransitionRenderTargetTexture;
	float TransitionTextureTimer = 0.0f;
	float TransitionTextureSpeed = 0.0f;
	VECTOR2 TransitionTexturePos;

	int StageIdx = 0;
	SCENE_ROUND_EDIT RoundEdit;
	SCENE_ROUND_PLAY RoundPlay;
	std::variant<SCENE_ROUND_EDIT*, SCENE_ROUND_PLAY*> State;
	//音
	SOUND* SoundButton = nullptr;
};

