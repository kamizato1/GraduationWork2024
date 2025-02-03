#include"DxLib.h"
#include"Battle.h"
#include"Player.h"
#include"EnemyBase.h"
#include"EnemyManager.h"
#include"Message.h"
#include"Effect.h"

#include"Key.h"

#define BLINKING_TIME 0.08f //�_�Ŏ���

#define MAX_TRANSPARENCY 255 // �����x�̍ő�l
#define ADD_TRANSPARENCY 5 //�����x�̉��Z

#define DRAW_DAMAGE_TIME 0.7f //�_���[�W���\������

#define ADD_SCREEN_AMPLITUDE 1 //��ʂ̐U�ꕝ


Battle::Battle(Player* player)
{
	//�摜�ǂݍ���
	if (LoadDivGraph("data/image/Battle/scenery.png", 12, 1, 12, 720, 96, scenery_image) == -1)throw("error_scenery.png\n");
	if (LoadDivGraph("data/image/Battle/attack.png", 7, 7, 1, 32, 32, effect_image[0]) == -1)throw("error_effect.png\n");

	//�t�H���g�̓ǂݍ���
	retro_font_48 = LoadFontDataToHandle("data/font/DragonQuestFont48.dft", 0);

	//�N���X�ݒ�
	this->player = player;
	enemy = nullptr;
	effect = nullptr;
	enemy_manager = new EnemyManager();

	//������
	Initialize(0, 0);

	OutputDebugString("Battle�R���X�g���N�^�Ă΂�܂����B\n");
}

Battle::~Battle()
{
	delete enemy;
	delete effect;
	delete enemy_manager;

	for (int i = 0; i < 12; i++)DeleteGraph(scenery_image[i]);

	for (int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)DeleteGraph(effect_image[i][j]);
	}

	DeleteFontToHandle(retro_font_48);

	OutputDebugString("Battle�f�X�g���N�^�Ă΂�܂����B\n");
}

void Battle::Initialize(int encount_enemy_rank, int scenery_image_index)
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
	font_color_value = 0xffffff;
	blinking_time = 0.0f;
	draw_enemy = true;
	screen_amplitude_value = 0;
	add_screen_amplitude_value = ADD_SCREEN_AMPLITUDE;

	this->scenery_image_index = scenery_image_index;
	if (scenery_image_index > 11)this->scenery_image_index = 0;

	draw_ui = { false, false, false, false };

	//�G�l�~�[�̐ݒ�
	enemy = new EnemyBase(enemy_manager->GetEnemyData(encount_enemy_rank));

	if (effect != nullptr)delete effect;
	effect = nullptr;
}

bool Battle::Update(float delta_time)
{
	switch (battle_state)
	{
	case BATTLE_STATE::ENCOUNT_ANIMATION:

		UpdateEncountAnimation(delta_time);
		break;

	case BATTLE_STATE::PLAYER_TURN:

		return UpdatePlayerAction(delta_time);
		break;

	case BATTLE_STATE::ENEMY_TURN:

		UpdateEnemyAction(delta_time);
		break;
	}

	return false;
}

void Battle::UpdateEncountAnimation(float delta_time)
{
	if ((screen_transparency_value += ADD_TRANSPARENCY) > MAX_TRANSPARENCY)
	{
		screen_transparency_value = MAX_TRANSPARENCY;

		if ((this->delta_time += delta_time) > 1.0f)
		{
			battle_state = BATTLE_STATE::PLAYER_TURN;
			this->delta_time = 0.0f;
			draw_ui = { false, true, true, true };
		}
	}
}

bool Battle::UpdatePlayerAction(float delta_time)
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
			action_select_state = static_cast<ACTION_SELECT_STATE>(action_select_index);
		}

		break;

	case ACTION_SELECT_STATE::ATTACK:

		return UpdatePlayerAttack(delta_time);

		break;

	case ACTION_SELECT_STATE::MAGIC:

		return UpdatePlayerMagic(delta_time);

		break;

	case ACTION_SELECT_STATE::ITEM:

		return UpdatePlayerItem(delta_time);

		break;

	case ACTION_SELECT_STATE::ESCAPE:

		return UpdatePlayerEscape(delta_time);


		break;
	}

	return false;
}

bool Battle::UpdatePlayerAttack(float delta_time)
{
	switch (action_state)
	{
	case ACTION_STATE::NONE:

		font_color_value = 0x808080;
		action_state = ACTION_STATE::TARGET_SELECT;

		break;

	case ACTION_STATE::TARGET_SELECT:

		if (Key::KeyDown(KEY_TYPE::A))
		{
			action_state = ACTION_STATE::PLAY_EFFECT;
			draw_ui = { true, true, false, false };
		}

		break;

	case ACTION_STATE::PLAY_EFFECT:

		if (effect == nullptr)effect = new Effect(effect_image[0], 5, 0.05f);
		else effect->Update(delta_time);

		if ((this->delta_time += delta_time) > 0.5f)
		{
			delete effect;
			effect = nullptr;
			this->delta_time = 0.0f;
			damage_value = player->Attack(enemy);
			action_state = ACTION_STATE::DRAW_DAMAGE;
		}

		break;

	case ACTION_STATE::DRAW_DAMAGE:

		if (damage_value != 0)
		{
			if (UpdateBlinking(delta_time))draw_enemy = !draw_enemy;
		}

		if ((this->delta_time += delta_time) > 1.0f)
		{
			//�G�����񂾂Ƃ�
			if (enemy->GetHp() == 0)
			{
				draw_enemy = false;
				action_state = ACTION_STATE::DEAD;
			}
			//�G�������Ă�Ƃ�
			else
			{
				battle_state = BATTLE_STATE::ENEMY_TURN;
				action_state = ACTION_STATE::NONE;
				action_select_state = ACTION_SELECT_STATE::NONE;
				damage_value = 0;
				draw_enemy = true;
			}

			this->delta_time = 0.0f;
			action_select_index = 0;
			font_color_value = 0xffffff;
			blinking_time = 0.0f;
			
		}

		break;

	case ACTION_STATE::DEAD:

		if ((this->delta_time += delta_time) > 2.0f)
		{
			this->delta_time = 0.0f;
			return true;
		}

		break;
	}

	return false;
}

bool Battle::UpdatePlayerMagic(float delta_time)
{
	switch (action_state)
	{
	case ACTION_STATE::NONE:

		draw_ui = { true, true, false, false };

		if ((this->delta_time += delta_time) > 1.0f)
		{
			action_select_state = ACTION_SELECT_STATE::NONE;
			action_select_index = 0;
			this->delta_time = 0.0f;

			draw_ui = { false, true, true, true };
		}

		break;
	}

	return false;
}



bool Battle::UpdatePlayerItem(float delta_time)
{
	switch (action_state)
	{
	case ACTION_STATE::NONE:

		draw_ui = { true, true, false, false };

		if ((this->delta_time += delta_time) > 1.0f)
		{
			action_select_state = ACTION_SELECT_STATE::NONE;
			action_select_index = 0;
			this->delta_time = 0.0f;

			draw_ui = { false, true, true, true };
		}

		break;
	}

	return false;
}


bool Battle::UpdatePlayerEscape(float delta_time)
{
	switch (action_state)
	{
	case ACTION_STATE::NONE:

		draw_ui = { true, true, false, false };

		if ((this->delta_time += delta_time) > 1.0f)
		{
			action_select_state = ACTION_SELECT_STATE::NONE;
			action_select_index = 0;
			this->delta_time = 0.0f;
			return true;
		}

		break;
	}

	return false;
}


bool Battle::UpdateBlinking(float delta_time)
{
	if ((blinking_time += delta_time) > BLINKING_TIME)
	{
		blinking_time = 0.0f;
		return true;
	}
	return false;
}


void Battle::UpdateEnemyAction(float delta_time)
{
	switch (action_select_state)
	{
	case ACTION_SELECT_STATE::NONE:

		action_select_state = ACTION_SELECT_STATE::ATTACK;

		break;

	case ACTION_SELECT_STATE::ATTACK:

		UpdateEnemyAttack(delta_time);

		break;
	}
}


void Battle::UpdateEnemyAttack(float delta_time)
{
	switch (action_state)
	{
	case ACTION_STATE::NONE:

		action_state = ACTION_STATE::TARGET_SELECT;

		break;

	case ACTION_STATE::TARGET_SELECT:

		action_state = ACTION_STATE::PLAY_EFFECT;

		break;
		
	case ACTION_STATE::PLAY_EFFECT:

		if ((this->delta_time += delta_time) > 0.7f)
		{
			this->delta_time = 0.0f;
			damage_value = enemy->Attack(player);
			action_state = ACTION_STATE::DRAW_DAMAGE;
		}
		

		break;

	case ACTION_STATE::DRAW_DAMAGE:

		if(damage_value != 0)UpdateScreenAmplitude();

		if ((this->delta_time += delta_time) > DRAW_DAMAGE_TIME)
		{
			screen_amplitude_value = 0;
			add_screen_amplitude_value = ADD_SCREEN_AMPLITUDE;

			battle_state = BATTLE_STATE::PLAYER_TURN;
			action_state = ACTION_STATE::NONE;
			action_select_state = ACTION_SELECT_STATE::NONE;
			this->delta_time = 0.0f;
			damage_value = 0;
			draw_ui = { false, true, true, true };
		}

		break;
	}
}


void Battle::UpdateScreenAmplitude()
{
	screen_amplitude_value += add_screen_amplitude_value;
	if ((screen_amplitude_value == ADD_SCREEN_AMPLITUDE * 2) || (screen_amplitude_value == -ADD_SCREEN_AMPLITUDE * 2))add_screen_amplitude_value *= -1;
}


void Battle::Draw() const
{
	if (battle_state == BATTLE_STATE::ENCOUNT_ANIMATION)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, screen_transparency_value);

		DrawGraph(0, 0, scenery_image[scenery_image_index], TRUE);//�w�i�摜
		enemy->Draw();//�G
		DrawMessageBox();
		if (screen_transparency_value == MAX_TRANSPARENCY)DrawFormatStringToHandle(55, 505, 0xffffff, retro_font_48, "%s�� �����ꂽ�I", enemy->GetName());

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, MAX_TRANSPARENCY);
	}
	else
	{
		DrawGraph(0, 0, scenery_image[scenery_image_index], TRUE);//�w�i�摜

		if (draw_enemy)enemy->Draw();

		if (effect != nullptr)effect->Draw();

		DrawUi();

		if (battle_state == BATTLE_STATE::PLAYER_TURN)
		{
			switch (action_state)
			{
			case ACTION_STATE::DEAD:
				DrawFormatStringToHandle(55, 595, 0xffffff, retro_font_48, "%s�� ���������I", enemy->GetName(), damage_value);

			case ACTION_STATE::DRAW_DAMAGE:
				DrawFormatStringToHandle(55, 550, 0xffffff, retro_font_48, "%s�� %d�� �_���[�W�I�I", enemy->GetName(), damage_value);

			case ACTION_STATE::PLAY_EFFECT:
				DrawFormatStringToHandle(55, 505, 0xffffff, retro_font_48, "%s�� ���������I", player->GetName());

				break;
			case ACTION_STATE::TARGET_SELECT:
				DrawStringToHandle(200, 505, "��", 0xffffff, retro_font_48);

				break;

			case ACTION_STATE::NONE:

				if (action_select_state == ACTION_SELECT_STATE::MAGIC)DrawStringToHandle(55, 505, "�������� ���ڂ��Ă��Ȃ��I", 0xffffff, retro_font_48);
				else if (action_select_state == ACTION_SELECT_STATE::ITEM)DrawStringToHandle(55, 505, "�ǂ����� �����Ă��Ȃ��I", 0xffffff, retro_font_48);
				else if (action_select_state == ACTION_SELECT_STATE::ESCAPE)DrawFormatStringToHandle(55, 505, 0xffffff, retro_font_48, "%s�� �ɂ��������I", player->GetName());

				break;

			}



		}
		else if (battle_state == BATTLE_STATE::ENEMY_TURN)
		{

			if (action_state == ACTION_STATE::PLAY_EFFECT)
			{
				DrawFormatStringToHandle(55, 505, 0xffffff, retro_font_48, "%s�� ���������I", enemy->GetName());
			}
			else if (action_state == ACTION_STATE::DRAW_DAMAGE)
			{
				DrawFormatStringToHandle(55, 505, 0xffffff, retro_font_48, "%s�� ���������I", enemy->GetName());
				DrawFormatStringToHandle(55, 550, 0xffffff, retro_font_48, "%s�� %d�� �_���[�W�� �������I", player->GetName(), damage_value);
			}

		}

	}

}

void Battle::DrawUi()const
{
	if (draw_ui.message_box)DrawMessageBox();
	if (draw_ui.player_name_box)DrawPlayerNameBox();
	if (draw_ui.enemy_name_box)DrawEnemyNameBox();
	if (draw_ui.action_select_box)DrawActionSelectBox();
}

void Battle::DrawMessageBox()const
{
	//�e�L�X�g�{�b�N�X�̕\��
	DrawBox(5 + screen_amplitude_value, 500 + screen_amplitude_value, 715 + screen_amplitude_value, 715 + screen_amplitude_value, 0xffffff, TRUE);
	DrawBox(10 + screen_amplitude_value, 505 + screen_amplitude_value, 710 + screen_amplitude_value, 710 + screen_amplitude_value, 0x000000, TRUE);
}

void Battle::DrawPlayerNameBox()const
{
	DrawBox(5 + screen_amplitude_value, 50 + screen_amplitude_value, 525 + screen_amplitude_value, 130 + screen_amplitude_value, 0xffffff, TRUE);
	DrawBox(10 + screen_amplitude_value, 55 + screen_amplitude_value, 520 + screen_amplitude_value, 125 + screen_amplitude_value, 0x000000, TRUE);

	DrawFormatStringToHandle(25, 55, 0xffffff, retro_font_48, "%s  HP %3d MP %3d", player->GetName(), player->GetHp(), player->GetMp());
}

void Battle::DrawActionSelectBox()const
{
	//�e�L�X�g�{�b�N�X
	DrawBox(5, 500, 180, 715, font_color_value, TRUE);
	DrawBox(10, 505, 175, 710, 0x000000, TRUE);

	//�I����
	DrawStringToHandle(20, 505 + (45 * action_select_index), "��", font_color_value, retro_font_48);

	//�I���R�}���h
	char action_font[4][15] = { {"��������"}, {"�������"}, {"�ǂ���"}, {"�ɂ���"} };
	for (int i = 0; i < 4; i++)DrawFormatStringToHandle(55, 505 + (45 * i), font_color_value, retro_font_48, "%s", action_font[i]);

}

void Battle::DrawEnemyNameBox()const
{
	//�G�e�L�X�g�{�b�N�X
	DrawBox(185, 500, 715, 580, 0xffffff, TRUE);
	DrawBox(190, 505, 710, 575, 0x000000, TRUE);

	DrawFormatStringToHandle(235, 505, 0xffffff, retro_font_48, "%s", enemy->GetName());

}