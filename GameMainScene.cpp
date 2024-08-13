#include"GameMainScene.h"
#include"DxLib.h"

GameMainScene::GameMainScene() : field(nullptr)
{
}

GameMainScene::~GameMainScene()
{
}

//初期化処理
void GameMainScene::Initialize()
{
	field = new Field();
}

//終了時処理
void GameMainScene::Finalize()
{
	delete field;
}

//更新処理
SCENE_TYPE GameMainScene::Update(float delta_time)
{
	if (field->Update(delta_time))return SCENE_TYPE::GAME_OVER;

	return GetNowScene();
}

//描画処理
void GameMainScene::Draw() const
{
	field->Draw();

	DrawString(0, 0, "gamemain", 0xffffff);
}

//現在のシーン情報を取得
SCENE_TYPE GameMainScene::GetNowScene() const
{
	return SCENE_TYPE::MAIN;
}