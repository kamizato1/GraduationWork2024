#include"GameMainScene.h"
#include"Player.h"
#include"Field.h"
#include"Battle.h"
#include"DxLib.h"

GameMainScene::GameMainScene()
{
	//�N���X�|�C���^�[
	player = nullptr;
	field = nullptr;
	battle = nullptr;

	game_scene_type = GAME_SCENE_TYPE::FIELD;
}

GameMainScene::~GameMainScene()
{
}

//����������
void GameMainScene::Initialize()
{
	player = new Player();
	field = new Field(player);
	battle = new Battle(player);
}

//�I��������
void GameMainScene::Finalize()
{
	delete player;
	delete field;
	delete battle;
}

//�X�V����
SCENE_TYPE GameMainScene::Update(float delta_time)
{
	switch (game_scene_type)
	{
	case GAME_SCENE_TYPE::FIELD:
	{
		int encount_enemy_rank = field->Update(delta_time);

		if (encount_enemy_rank != -1)
		{
			game_scene_type = GAME_SCENE_TYPE::BATTLE;
			battle->Initialize(encount_enemy_rank);
		}
		break;
	}
	case GAME_SCENE_TYPE::BATTLE:

		if (battle->Update(delta_time))
		{
			game_scene_type = GAME_SCENE_TYPE::FIELD;
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
	case GAME_SCENE_TYPE::FIELD:
		field->Draw();
		break;
	case GAME_SCENE_TYPE::BATTLE:
		battle->Draw();
		break;
	}

	DrawFormatString(0, 50, 0xffffff, "%s", player->GetName());
	DrawString(0, 0, "gamemain", 0xffffff);
}

//���݂̃V�[�������擾
SCENE_TYPE GameMainScene::GetNowScene() const
{
	return SCENE_TYPE::MAIN;
}