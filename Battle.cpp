#include"DxLib.h"
#include"Battle.h"
#include"Player.h"
#include"EnemyManager.h"
#include"Message.h"
#include"Effect.h"

#include"Key.h"

#define BLINKING_TIME 0.08f //点滅時間

#define MAX_TRANSPARENCY 255 // 透明度の最大値
#define ADD_TRANSPARENCY 5 //透明度の加算

#define ADD_SCREEN_AMPLITUDE 1 //画面の振れ幅


Battle::Battle(Player* player)
{
	//画像読み込み
	if (LoadDivGraph("data/image/Battle/scenery.png", 12, 1, 12, 720, 96, scenery_image) == -1)throw("error_scenery.png\n");
	if (LoadDivGraph("data/image/Battle/attack.png", 7, 7, 1, 32, 32, effect_image[0]) == -1)throw("error_effect.png\n");

	//フォントの読み込み
	retro_font_48 = LoadFontDataToHandle("data/font/DragonQuestFont48.dft", 0);

	//クラス設定
	this->player = player;
	enemy_manager = new EnemyManager();
	effect = nullptr;

	//初期化
	Initialize(0);

	OutputDebugString("Battleコンストラクタ呼ばれました。\n");
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

	OutputDebugString("Battleデストラクタ呼ばれました。\n");
}

void Battle::Initialize(int encount_enemy_rank)
{
	//state
	battle_state = BATTLE_STATE::ENCOUNT_ANIMATION;
	action_select_state = ACTION_SELECT_STATE::NONE;
	action_state = ACTION_STATE::NONE;

	//変数
	action_select_index = 0;
	target_select_index = 0;
	screen_transparency_value = 0;
	damage_value = 0;
	delta_time = 0.0f;
	font_color = 0xffffff;
	blinking_time = 0.0f;
	screen_amplitude = 0;
	add_screen_amplitude = ADD_SCREEN_AMPLITUDE;

	draw_ui = { false, false, false, false };

	//エネミーマネージャーの初期化
	enemy_manager->Initialize(encount_enemy_rank);

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

		UpdatePlayerAction(delta_time);
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

void Battle::UpdatePlayerAction(float delta_time)
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

			font_color = 0x808080;
		}

		break;

	case ACTION_SELECT_STATE::ATTACK:

		UpdatePlayerAttack(delta_time);

		break;
	}
}

void Battle::UpdatePlayerAttack(float delta_time)
{
	switch (action_state)
	{
	case ACTION_STATE::NONE:

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
		else if (effect->Update(delta_time))
		{
			delete effect;
			effect = nullptr;
			action_state = ACTION_STATE::DRAW_DAMAGE;
		}

		break;

	case ACTION_STATE::DRAW_DAMAGE:

		if ((blinking_time += delta_time) > BLINKING_TIME * 2)blinking_time = 0.0f;

		if ((this->delta_time += delta_time) > 1.0f)
		{
			battle_state = BATTLE_STATE::ENEMY_TURN;
			action_state = ACTION_STATE::NONE;
			action_select_state = ACTION_SELECT_STATE::NONE;
			action_select_index = 0;
			this->delta_time = 0.0f;
			font_color = 0xffffff;
			blinking_time = 0.0f;
		}

		break;
	}
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
			action_state = ACTION_STATE::DRAW_DAMAGE;
		}
		

		break;

	case ACTION_STATE::DRAW_DAMAGE:

		if (UpdateScreenAmplitude(delta_time))
		{
			battle_state = BATTLE_STATE::PLAYER_TURN;
			action_state = ACTION_STATE::NONE;
			action_select_state = ACTION_SELECT_STATE::NONE;
			this->delta_time = 0.0f;
			draw_ui = { false, true, true, true };
		}

		break;
	}
}


bool Battle::UpdateScreenAmplitude(float delta_time)
{
	screen_amplitude += add_screen_amplitude;
	if ((screen_amplitude == ADD_SCREEN_AMPLITUDE * 2) || (screen_amplitude == -ADD_SCREEN_AMPLITUDE * 2))add_screen_amplitude *= -1;

	if ((this->delta_time += delta_time) > 0.7f)
	{
		screen_amplitude = 0;
		this->delta_time = 0.0f;
		add_screen_amplitude = ADD_SCREEN_AMPLITUDE;
		return true;
	}

	return false;
}


void Battle::Draw() const
{
	if (battle_state == BATTLE_STATE::ENCOUNT_ANIMATION)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, screen_transparency_value);

		DrawGraph(0, 0, scenery_image[0], TRUE);//背景画像
		enemy_manager->Draw();//敵
		DrawMessageBox();
		if (screen_transparency_value == MAX_TRANSPARENCY)DrawFormatStringToHandle(55, 505, 0xffffff, retro_font_48, "%sが あらわれた！", enemy_manager->GetEnemyName(0));

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, MAX_TRANSPARENCY);
	}
	else
	{
		DrawGraph(0, 0, scenery_image[0], TRUE);//背景画像

		if (blinking_time < BLINKING_TIME)enemy_manager->Draw();

		if (effect != nullptr)effect->Draw();

		DrawUi();

		int damage = 15;

		if (battle_state == BATTLE_STATE::PLAYER_TURN)
		{
			if (action_state == ACTION_STATE::TARGET_SELECT)DrawStringToHandle(200, 505, "＞", 0xffffff, retro_font_48);

			if (action_state == ACTION_STATE::PLAY_EFFECT)DrawFormatStringToHandle(55, 505, 0xffffff, retro_font_48, "%sの こうげき！", player->GetName());

			if (action_state == ACTION_STATE::DRAW_DAMAGE)
			{
				DrawFormatStringToHandle(55, 505, 0xffffff, retro_font_48, "%sの こうげき！", player->GetName());
				DrawFormatStringToHandle(55, 550, 0xffffff, retro_font_48, "%sに %3dの ダメージ！！", enemy_manager->GetEnemyName(0), damage);
			}
		}
		else if (battle_state == BATTLE_STATE::ENEMY_TURN)
		{
			if (action_state == ACTION_STATE::PLAY_EFFECT)DrawFormatStringToHandle(55, 505, 0xffffff, retro_font_48, "%sの こうげき！", enemy_manager->GetEnemyName(0));

			if (action_state == ACTION_STATE::DRAW_DAMAGE)
			{
				DrawFormatStringToHandle(55, 505, 0xffffff, retro_font_48, "%sの こうげき！", enemy_manager->GetEnemyName(0));
				DrawFormatStringToHandle(55, 550, 0xffffff, retro_font_48, "%sは %3dの ダメージを うけた！", player->GetName(), damage);
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
	//テキストボックスの表示
	DrawBox(5 + screen_amplitude, 500 + screen_amplitude, 715 + screen_amplitude, 715 + screen_amplitude, 0xffffff, TRUE);
	DrawBox(10 + screen_amplitude, 505 + screen_amplitude, 710 + screen_amplitude, 710 + screen_amplitude, 0x000000, TRUE);
}

void Battle::DrawPlayerNameBox()const
{
	DrawBox(5 + screen_amplitude, 50 + screen_amplitude, 525 + screen_amplitude, 130 + screen_amplitude, 0xffffff, TRUE);
	DrawBox(10 + screen_amplitude, 55 + screen_amplitude, 520 + screen_amplitude, 125 + screen_amplitude, 0x000000, TRUE);

	DrawFormatStringToHandle(25, 55, 0xffffff, retro_font_48, "%s  HP %3d MP %3d", player->GetName(), player->GetHp(), player->GetMp());
}

void Battle::DrawActionSelectBox()const
{
	//テキストボックス
	DrawBox(5, 500, 180, 715, font_color, TRUE);
	DrawBox(10, 505, 175, 710, 0x000000, TRUE);

	//選択矢印
	DrawStringToHandle(20, 505 + (45 * action_select_index), "＞", font_color, retro_font_48);

	//選択コマンド
	char action_font[4][15] = { {"たたかう"}, {"じゅもん"}, {"どうぐ"}, {"にげる"} };
	for (int i = 0; i < 4; i++)DrawFormatStringToHandle(55, 505 + (45 * i), font_color, retro_font_48, "%s", action_font[i]);

}

void Battle::DrawEnemyNameBox()const
{
	//敵テキストボックス
	DrawBox(185, 500, 715, 580, 0xffffff, TRUE);
	DrawBox(190, 505, 710, 575, 0x000000, TRUE);

	DrawFormatStringToHandle(235, 505, 0xffffff, retro_font_48, "%s", enemy_manager->GetEnemyName(0));

}