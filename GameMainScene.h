#pragma once
#include"SceneBase.h"

class GameMainScene :public SceneBase
{
private:

	enum class GAME_SCENE_TYPE
	{
		WORLD_MAP, //ワールドマップ
		TOWN_MAP,
		BATTLE //バトル
	};

	GAME_SCENE_TYPE game_scene_type;

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