#pragma once
#include"SceneBase.h"
#include"define.h"

class GameMainScene :public SceneBase
{
private:

	GAME_SCENE_TYPE game_scene_type;

	class NameInput* name_input;
	class Player* player;
	class WorldMap* world_map;
	class TownMap* town_map;
	class Battle* battle;
	
public:
	GameMainScene();
	virtual ~GameMainScene();

	void Initialize() override;
	void Finalize() override;

	SCENE_TYPE Update(float delta_time) override;
	void Draw() const override;
	
	SCENE_TYPE GetNowScene() const override;
};