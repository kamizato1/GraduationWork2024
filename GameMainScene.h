#pragma once
#include"SceneBase.h"

class GameMainScene :public SceneBase
{
private:

	enum class GAME_SCENE_TYPE
	{
		FIELD, //フィールド
		BATTLE //バトル
	};

	GAME_SCENE_TYPE game_scene_type;

	class Player* player;
	class Field* field;
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