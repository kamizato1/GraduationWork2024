#include"DxLib.h"
#include"Battle.h"
#include"Player.h"
#include"EnemyManager.h"
#include"Message.h"
#include"Effect.h"

#include"Key.h"

Battle::Battle(Player* player)
{
	//�摜�ǂݍ���
	if (LoadDivGraph("data/image/Battle/scenery.png", 12, 1, 12, 720, 96, scenery_image) == -1)throw("error_scenery.png\n");
	if (LoadDivGraph("data/image/Battle/attack.png", 7, 7, 1, 32, 32, effect_image[0]) == -1)throw("error_effect.png\n");

	//�t�H���g�̓ǂݍ���
	retro_font_48 = LoadFontDataToHandle("data/font/RetroFont_48.dft", 0);

	//�N���X�ݒ�
	this->player = player;
	enemy_manager = new EnemyManager();
	effect = nullptr;

	//������
	Initialize(0);

	OutputDebugString("Battle�R���X�g���N�^�Ă΂�܂����B\n");
}

Battle::~Battle()
{
	delete enemy_manager;
	delete effect;

	for (int i = 0; i < 12; i++)DeleteGraph(scenery_image[i]);

	for (int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)DeleteGraph(effect_image[i][j]);
	}

	DeleteFontToHandle(retro_font_48);

	OutputDebugString("Battle�f�X�g���N�^�Ă΂�܂����B\n");
}

void Battle::Initialize(int encount_enemy_rank)
{
	//state
	battle_state = BATTLE_STATE::ENCOUNT_ANIMATION;
	action_select_state = ACTION_SELECT_STATE::NONE;
	action_state = ACTION_STATE::NONE;

	//�ϐ�
	action_select_index = 0;
	target_select_index = 0;
	screen_transparency_value = 0;
	damage_value = 0;
	delta_time = 0.0f;

	//�G�l�~�[�}�l�[�W���[�̏�����
	enemy_manager->Initialize(encount_enemy_rank);

	if (effect != nullptr)delete effect;
	effect = nullptr;
}

bool Battle::Update(float delta_time)
{
	switch (battle_state)
	{
	case BATTLE_STATE::ENCOUNT_ANIMATION:

		if ((screen_transparency_value += 5) > 255)
		{
			screen_transparency_value = 255;

			if ((this->delta_time += delta_time) > 1.0f)
			{
				battle_state = BATTLE_STATE::PLAYER;
				this->delta_time = 0.0f;
			}
		}

		break;

	case BATTLE_STATE::PLAYER:

		PlayerAction(delta_time);

		break;
	}

	return false;
}

void Battle::PlayerAction(float delta_time)
{
	switch (action_select_state)
	{
	case ACTION_SELECT_STATE::NONE:

		if (Key::KeyDown(KEY_TYPE::UP))
		{
			if (--action_select_index < 0)action_select_index = 3;
		}
		else if (Key::KeyDown(KEY_TYPE::DOWN))
		{
			if (++action_select_index > 3)action_select_index = 0;
		}

		if (Key::KeyDown(KEY_TYPE::A))
		{
			action_select_state = ACTION_SELECT_STATE::ATTACK;
			//action_select_state = static_cast<ACTION_SELECT_STATE>(action_select_index);
			action_state = ACTION_STATE::TARGET_SELECT;
		}

		break;

	case ACTION_SELECT_STATE::ATTACK:

		PlayerAttack(delta_time);

		break;
	}
}

void Battle::PlayerAttack(float delta_time)
{
	switch (action_state)
	{
	case ACTION_STATE::NONE:

		break;

	case ACTION_STATE::ACTION_SELECT:

		if (Key::KeyDown(KEY_TYPE::A))action_state = ACTION_STATE::TARGET_SELECT;
		break;

	case ACTION_STATE::TARGET_SELECT:

		if (Key::KeyDown(KEY_TYPE::UP))
		{
			if (--target_select_index < 0)target_select_index = 0;
		}
		else if (Key::KeyDown(KEY_TYPE::DOWN))
		{
			if (++target_select_index > 0)target_select_index = 0;
		}

		if (Key::KeyDown(KEY_TYPE::A))action_state = ACTION_STATE::PLAY_EFFECT;

		break;


	case ACTION_STATE::PLAY_EFFECT:

		if (effect == nullptr)effect = new Effect(effect_image[0], 5, 0.05f);
		else if(effect->Update(delta_time))
		{
			delete effect;
			effect = nullptr;
			action_state = ACTION_STATE::DRAW_DAMAGE;
		}

		break;


	case ACTION_STATE::DRAW_DAMAGE:

		if ((this->delta_time += delta_time) > 2.0f)
		{
			action_state = ACTION_STATE::NONE;
			action_select_state = ACTION_SELECT_STATE::NONE;
			action_select_index = 0;
			this->delta_time = 0.0f;
		}

		break;
	}
}

void Battle::Draw() const
{
	//DrawFormatString(0, 100, 0xffffff, "%f", wait_time);
	//DrawFormatString(0, 40, 0xffffff, "%d", player->GetMp());

	if (battle_state == BATTLE_STATE::ENCOUNT_ANIMATION)SetDrawBlendMode(DX_BLENDMODE_ALPHA, screen_transparency_value);

	//�w�i�̕\��
	DrawGraph(0, 0, scenery_image[0], TRUE);

	//�G�L�����̕\��
	enemy_manager->Draw();

	if(effect != nullptr)effect->Draw();

	switch (battle_state)
	{
	case BATTLE_STATE::ENCOUNT_ANIMATION:

		//�e�L�X�g�{�b�N�X�̕\��
		DrawBox(5, 500, 715, 715, 0xffffff, TRUE);
		DrawBox(10, 505, 710, 710, 0x000000, TRUE);

		if (screen_transparency_value == 255)DrawFormatStringToHandle(55, 505, 0xffffff, retro_font_48, "%s�� �����ꂽ�I", enemy_manager->GetEnemyName(0));

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		break;

	case BATTLE_STATE::PLAYER:
	{
		//�e�L�X�g�{�b�N�X
		DrawBox(5, 500, 180, 715, 0xffffff, TRUE);
		DrawBox(10, 505, 175, 710, 0x000000, TRUE);

		//�I����
		DrawStringToHandle(20, 505 + (45 * action_select_index), "�p", 0xffffff, retro_font_48);
		//�I���R�}���h
		char action_font[4][15] = { {"��������"}, {"�������"}, {"�ǂ���"}, {"�ɂ���"} };
		for (int i = 0; i < 4; i++)DrawFormatStringToHandle(55, 505 + (45 * i), 0xffffff, retro_font_48, "%s", action_font[i]);

		//�e�L�X�g�{�b�N�X
		DrawBox(185, 500, 715, 600, 0xffffff, TRUE);
		DrawBox(190, 505, 710, 595, 0x000000, TRUE);

		DrawPlayerAction();

		if (effect != nullptr)effect->Draw();

		break;
	}
	}

	//if (message != nullptr)message->Draw();
	//if (image_transparency != 255)SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	DrawFormatString(0, 50 , 0xffffff, "battle_state        = %d", static_cast<int>(battle_state));
	DrawFormatString(0, 75 , 0xffffff, "action_select_state = %d", static_cast<int>(action_select_state));
	DrawFormatString(0, 100, 0xffffff, "action_state        = %d", static_cast<int>(action_state));

	DrawFormatString(0, 125, 0xffffff, "action_select_index = %d", action_select_index);
	DrawFormatString(0, 150, 0xffffff, "target_select_index = %d", target_select_index);
	DrawFormatString(0, 175, 0xffffff, "screen_transparency_value = %d", screen_transparency_value);
	DrawFormatString(0, 200, 0xffffff, "damage_value        = %d", damage_value);

}

void Battle::DrawPlayerAction()const
{
	DrawFormatStringToHandle(235, 505, 0xffffff, retro_font_48, "%s", enemy_manager->GetEnemyName(0));

	switch (action_select_state)
	{
	case ACTION_SELECT_STATE::NONE:

		break;

	case ACTION_SELECT_STATE::ATTACK:

		DrawPlayerAttack();
		break;

	case ACTION_SELECT_STATE::MAGIC:

		break;

	case ACTION_SELECT_STATE::ITEM:

		break;
	}
}

void Battle::DrawPlayerAttack()const
{
	switch (action_state)
	{
	case ACTION_STATE::NONE:

		break;

	case ACTION_STATE::ACTION_SELECT:

		break;

	case ACTION_STATE::TARGET_SELECT:

		DrawStringToHandle(200, 505, "�p", 0xffffff, retro_font_48);
		break;

	case ACTION_STATE::PLAY_EFFECT:

		DrawStringToHandle(200, 505, "�p", 0xffffff, retro_font_48);
		break;

	case ACTION_STATE::DRAW_DAMAGE:

		int damage = 123;

		DrawStringToHandle(200, 505, "�p", 0xffffff, retro_font_48);
		DrawFormatStringToHandle(340, 250 - (delta_time * 50), 0xffffff, retro_font_48, "%d",damage);
		DrawFormatStringToHandle(440, 505, 0xffffff, retro_font_48, "%d �_���[�W", damage);

		break;

	}
}