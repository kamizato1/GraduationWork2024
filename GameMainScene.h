#pragma once
#include"SceneBase.h"
#include"Field.h"

class GameMainScene :public SceneBase
{
private:
	class Field* field;
	
public:
	GameMainScene();
	virtual ~GameMainScene();

	void Initialize() override;
	void Finalize() override;

	SCENE_TYPE Update(float delta_time) override;
	void Draw() const override;
	
	SCENE_TYPE GetNowScene() const override;
};