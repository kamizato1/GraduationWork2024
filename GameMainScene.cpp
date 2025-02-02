#include"GameMainScene.h"
#include"Player.h"
#include"WorldMap.h"
#include"TownMap.h"
#include"Battle.h"
#include"NameInput.h"
#include"DxLib.h"

GameMainScene::GameMainScene()
{
	//�N���X�|�C���^�[
	player = nullptr;
	world_map = nullptr;
	town_map = nullptr;
	battle = nullptr;
	name_input = nullptr;

	game_scene_type = GAME_SCENE_TYPE::NAME_INPUT;
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
	name_input = new NameInput();

	world_map->Initialize();
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
	case GAME_SCENE_TYPE::NAME_INPUT:

		if (name_input->Update(delta_time))
		{
			player->SetName(name_input->GetName());
			game_scene_type = GAME_SCENE_TYPE::WORLD_MAP;
		}

		break;

	case GAME_SCENE_TYPE::WORLD_MAP:
	{
		GAME_SCENE_TYPE next_game_scene_type = world_map->Update(delta_time);

		if (next_game_scene_type == GAME_SCENE_TYPE::TOWN_MAP)town_map->Initialize();
		else if (next_game_scene_type == GAME_SCENE_TYPE::BATTLE)battle->Initialize(world_map->GetEnemyRank(), world_map->GetTileType());

		game_scene_type = next_game_scene_type;

		break;
	}
	case GAME_SCENE_TYPE::TOWN_MAP:
	{
		GAME_SCENE_TYPE next_game_scene_type = town_map->Update(delta_time);

		if (next_game_scene_type == GAME_SCENE_TYPE::WORLD_MAP)world_map->Initialize();

		game_scene_type = next_game_scene_type;

		break;
	}
	case GAME_SCENE_TYPE::BATTLE:

		if (battle->Update(delta_time))
		{
			game_scene_type = GAME_SCENE_TYPE::WORLD_MAP;
			world_map->Initialize();
		}

		break;
	}

	return GetNowScene();
}

//�`�揈��
void GameMainScene::Draw() const
{
	switch (game_scene_type)
	{
	case GAME_SCENE_TYPE::NAME_INPUT:

		name_input->Draw();
		break;

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