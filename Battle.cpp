#include"DxLib.h"
#include"Battle.h"
#include"Player.h"
#include"EnemyManager.h"
#include"Message.h"

#include"Key.h"

Battle::Battle(Player* player) : player(player), enemy_manager(new EnemyManager()), message(nullptr)
{
	if (LoadDivGraph("data/image/Battle/scenery.png", 12, 1, 12, 720, 96, scenery_image) == -1)throw("data/image/Battle/scenery.png���ǂݍ��߂܂���\n");

	Initialize(0);

	OutputDebugString("Battle�R���X�g���N�^�Ă΂�܂����B\n");
}

Battle::~Battle()
{
	delete enemy_manager;
	delete message;

	OutputDebugString("Battle�f�X�g���N�^�Ă΂�܂����B\n");
}

void Battle::Initialize(int encount_enemy_rank)
{
	battle_state = BATTLE_STATE::DRAW_ENEMY_NAME;
	image_transparency = 0;
	enemy_manager->Initialize(encount_enemy_rank);
}

bool Battle::Update(float delta_time)
{
	if (EncountAnimation())
	{
		switch (battle_state)
		{
		case BATTLE_STATE::DRAW_ENEMY_NAME:
		
			if (message == nullptr)message = new Message("gfgaafgaghshsfhsdfh", false, F_VECTOR2{ 10,10 });
			else message->Update(delta_time);

			break;

		case BATTLE_STATE::PLAYER_ACTION_SELECT:

			break;
		}

	}

	if (Key::KeyDown(KEY_TYPE::A))return true;

	return false;
}

bool Battle::EncountAnimation()
{
	//�퓬�J�n�����X�ɉ�ʂ��\�������
	if (image_transparency == 255)return true;
	else if ((image_transparency += 5) > 255)image_transparency = 255;
	return false;
}

void Battle::Draw() const
{
	DrawFormatString(0, 100, 0xffffff, "%f", wait_time);
	DrawFormatString(0, 40, 0xffffff, "%d", player->GetMp());

	if(image_transparency != 255)SetDrawBlendMode(DX_BLENDMODE_ALPHA, image_transparency);

	DrawGraph(0, 0, scenery_image[0], TRUE);//�w�i�̕\��

	enemy_manager->Draw();//�G�L�����̕\��

	DrawBox(0, 500, 720, 720, 0xffffff, TRUE);//�e�L�X�g�{�b�N�X�̕\��
	DrawBox(5, 505, 715, 715, 0x000000, TRUE);

	if (message != nullptr)message->Draw();
	
	if (image_transparency != 255)SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	
}