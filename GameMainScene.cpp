#include"GameMainScene.h"
#include"Player.h"
#include"WorldMap.h"
#include"TownMap.h"
#include"Battle.h"
#include"DxLib.h"

GameMainScene::GameMainScene()
{
	//�N���X�|�C���^�[
	player = nullptr;
	world_map = nullptr;
	town_map = nullptr;
	battle = nullptr;

	game_scene_type = GAME_SCENE_TYPE::WORLD_MAP;
}

GameMainScene::~GameMainScene()
{
}

//����������
void GameMainScene::Initialize()
{
	player = new Player();
	world_map = new WorldMap(player);
	town_map = new TownMap(player);
	battle = new Battle(player);
}

//�I��������
void GameMainScene::Finalize()
{
	delete player;
	delete world_map;
	delete town_map;
	delete battle;
}

//�X�V����
SCENE_TYPE GameMainScene::Update(float delta_time)
{
	switch (game_scene_type)
	{
	case GAME_SCENE_TYPE::WORLD_MAP:
	{
		int encount_enemy_rank = world_map->Update(delta_time);

		if (encount_enemy_rank != -1)
		{
			game_scene_type = GAME_SCENE_TYPE::TOWN_MAP;
			//battle->Initialize(encount_enemy_rank);
		}
		break;
	}
	case GAME_SCENE_TYPE::TOWN_MAP:

		if (town_map->Update(delta_time) != -1)game_scene_type = GAME_SCENE_TYPE::WORLD_MAP;

		break;

	case GAME_SCENE_TYPE::BATTLE:

		if (battle->Update(delta_time))game_scene_type = GAME_SCENE_TYPE::WORLD_MAP;

		break;
	}

	return GetNowScene();
}

//�`�揈��
void GameMainScene::Draw() const
{
	switch (game_scene_type)
	{
	case GAME_SCENE_TYPE::WORLD_MAP:

		world_map->Draw();
		break;

	case GAME_SCENE_TYPE::TOWN_MAP:

		town_map->Draw();

		break;


	case GAME_SCENE_TYPE::BATTLE:

		battle->Draw();

		break;
	}

	//DrawFormatString(0, 50, 0xffffff, "%s", player->GetName());
	DrawString(0, 0, "gamemain", 0xffffff);
}

//���݂̃V�[�������擾
SCENE_TYPE GameMainScene::GetNowScene() const
{
	return SCENE_TYPE::MAIN;
}