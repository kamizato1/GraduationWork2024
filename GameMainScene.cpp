#include"GameMainScene.h"
#include"DxLib.h"

GameMainScene::GameMainScene() : field(nullptr)
{
}

GameMainScene::~GameMainScene()
{
}

//����������
void GameMainScene::Initialize()
{
	field = new Field();
}

//�I��������
void GameMainScene::Finalize()
{
	delete field;
}

//�X�V����
SCENE_TYPE GameMainScene::Update(float delta_time)
{
	if (field->Update(delta_time))return SCENE_TYPE::GAME_OVER;

	return GetNowScene();
}

//�`�揈��
void GameMainScene::Draw() const
{
	field->Draw();

	DrawString(0, 0, "gamemain", 0xffffff);
}

//���݂̃V�[�������擾
SCENE_TYPE GameMainScene::GetNowScene() const
{
	return SCENE_TYPE::MAIN;
}