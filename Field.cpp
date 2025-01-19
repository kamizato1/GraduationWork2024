#include"DxLib.h"
#include"Field.h"
#include"Key.h"
#include"Player.h"

#define TILE_SIZE 48 //タイルの大きさ

#define DRAW_TILE_NUM 17 //表示するフィールドのタイルの数

#define PLAYER_IMAGE_CHANGE_TIME 0.2f //画像切り替え時間
#define PLAYER_IMAGE_INDEX 4 //プレイヤー画像配列数

#define PLAYER_SPEED 2 //プレイヤーの移動速度

#define MAX_ENCOUNT_RATE 10 //最大エンカウント率(割合)
#define MAX_WALK_ENCOUNT_RATE 7 //歩いているとき上がる最大エンカウント率（割合）
#define SAFE_ENCOUNT_STEP 5 //エンカウントしない歩数

#define SCREEN_BLINKING_TIME 0.08f //画面点滅時間
#define SCREEN_BLINKING_COUNT 5 //画面点滅回数

int WrapAround(int value, int min, int max)//値が範囲外になったら一周するようにする
{
	if (min > max)
	{
		int work = min;
		min = max;
		max = work;
	}

	if (value > max)return min + (value - max) - 1;
	else if (value < min)return max - (min - value) + 1;

	return value;
}

Field::Field(Player* player)
{
	this->player = player;

	if (LoadDivGraph("data/image/Field/tile.png", TILE_TYPE_NUM, TILE_TYPE_NUM, 1, 16, 16, tile_image) == -1)throw("data/image/Field/tile.pngが読み込めません\n");
	if (LoadDivGraph("data/image/Field/Player/walk.png", 5, 5, 1, 50, 50, player_image[1]) == -1)throw("data/image/Field/Player/walk.pngが読み込めません\n");
	if (LoadDivGraph("data/image/Field/Player/wait.png", 5, 5, 1, 50, 50, player_image[0]) == -1)throw("data/image/Field/Player/wait.png.pngが読み込めません\n");

	//フォントの読み込み
	retro_font_48 = LoadFontDataToHandle("data/font/DragonQuestFont48.dft", 0);

	SetField();

	//プレイヤーの設定
	field_player.location_index.x = 11; //プレイヤー座標（配列）
	field_player.location_index.y = 106;

	field_player.location.x = tile[field_player.location_index.y][field_player.location_index.x].location.x;
	field_player.location.y = tile[field_player.location_index.y][field_player.location_index.x].location.y;

	//変数
	player_image_change_time = 0.0f;
	player_image_index = 0;

	encount_rate = -SAFE_ENCOUNT_STEP;

	screen_blinking_time = 0.0f;
	screen_blinking_count = 0;

    OutputDebugString("Fieldコンストラクタ呼ばれました。\n");
}

void Field::SetField()
{
	FILE* field_data = nullptr;//フィールド読み込み
	FILE* enemy_rank_data = nullptr;//出現する敵のランク読み込み

	errno_t error_field_data = fopen_s(&field_data, "data/map/field.txt", "r");
	if (error_field_data != 0)throw("data/map/field.txtが読み込めません\n");//エラーチェック

	errno_t error_enemy_rank_data = fopen_s(&enemy_rank_data, "data/map/enemyrank.txt", "r");
	if (error_enemy_rank_data != 0)throw("data/map/enemyrank.txtが読み込めません\n");//エラーチェック

	for (int i = 0; i < FIELD_TILE_NUM; i++)
	{
		for (int j = 0; j < FIELD_TILE_NUM; j++)
		{
			tile[i][j].location.x = (j * TILE_SIZE) + (TILE_SIZE / 2);
			tile[i][j].location.y = (i * TILE_SIZE) + (TILE_SIZE / 2);
			fscanf_s(field_data, "%d", &tile[i][j].type);
			fscanf_s(enemy_rank_data, "%d", &tile[i][j].enemy_rank);
		}
	}

	fclose(field_data);
	fclose(enemy_rank_data);
}

Field::~Field()
{
    OutputDebugString("Fieldデストラクタが呼ばれました。\n");
}


int Field::Update(float delta_time)
{
	//エンカウントアニメーション
	if (update_encount_animation)return UpdateEncountAnimation(delta_time);
	else
	{
		if ((player_image_change_time += delta_time) > PLAYER_IMAGE_CHANGE_TIME)
		{
			if (++player_image_index == PLAYER_IMAGE_INDEX)player_image_index = 0;
			player_image_change_time = 0.0f;
		}

		UpdateMovement();

		
	}

    return -1;
}

void Field::UpdateMovement()
{
	if (field_player.location == tile[field_player.location_index.y][field_player.location_index.x].location)
	{
		VECTOR2_I location_index = field_player.location_index;

		if (Key::KeyPressed(KEY_TYPE::UP))field_player.location_index.y = field_player.location_index.y - 1;
		else if (Key::KeyPressed(KEY_TYPE::DOWN))field_player.location_index.y = field_player.location_index.y + 1;
		else if (Key::KeyPressed(KEY_TYPE::LEFT))field_player.location_index.x = field_player.location_index.x - 1;
		else if (Key::KeyPressed(KEY_TYPE::RIGHT))field_player.location_index.x = field_player.location_index.x + 1;

		//当たり判定
		if (tile[field_player.location_index.y][field_player.location_index.x].type >= 17)field_player.location_index = location_index;
	}
	else
	{
		if (UpdateScroll())
		{
			if (++encount_rate > 0)
			{
				if (encount_rate > MAX_WALK_ENCOUNT_RATE)encount_rate = MAX_WALK_ENCOUNT_RATE;
				if (GetRand(MAX_ENCOUNT_RATE - encount_rate) == 0)update_encount_animation = true;
			}
		}
	}
}

bool Field::UpdateScroll()
{
	if (UpdateAddScrollValue(&field_player.location.x, &tile[field_player.location_index.y][field_player.location_index.x].location.x))return true;
	if (UpdateAddScrollValue(&field_player.location.y, &tile[field_player.location_index.y][field_player.location_index.x].location.y))return true;
	
	return false;
}

bool Field::UpdateAddScrollValue(int* player_location, int* tile_location)
{
	if (*player_location < *tile_location)
	{
		if ((*player_location += PLAYER_SPEED) >= *tile_location)
		{
			*player_location = *tile_location;
			return true;
		}
	}
	else if (*player_location > *tile_location)
	{
		if ((*player_location -= PLAYER_SPEED) <= *tile_location)
		{
			*player_location = *tile_location;
			return true;
		}
	}
	return false;
}


int Field::UpdateEncountAnimation(float delta_time)
{
	if ((screen_blinking_time += delta_time) >  SCREEN_BLINKING_TIME)
	{
		screen_blinking_time = 0.0f;

		if (++screen_blinking_count > (SCREEN_BLINKING_COUNT * 2) - 1)
		{
			screen_blinking_count = 0;
			update_encount_animation = false;
			encount_rate = -SAFE_ENCOUNT_STEP;

			//return -1;

			return tile[field_player.location_index.y][field_player.location_index.x].enemy_rank;
		}
	}

	return -1;
}

void Field::Draw() const
{
	for (int i = 0; i < DRAW_TILE_NUM; i++)//縦の繰り返し
	{
		for (int j = 0; j < DRAW_TILE_NUM; j++)//横の繰り返し
		{
			int draw_tile_array_x = field_player.location_index.x - (DRAW_TILE_NUM / 2) + j;
			int draw_tile_array_y = field_player.location_index.y - (DRAW_TILE_NUM / 2) + i;

			int add_x = tile[field_player.location_index.y][field_player.location_index.x].location.x - field_player.location.x;
			int add_y = tile[field_player.location_index.y][field_player.location_index.x].location.y - field_player.location.y;

			DrawRotaGraph((j * TILE_SIZE) - (TILE_SIZE / 2) + add_x, i * TILE_SIZE - (TILE_SIZE / 2) + add_y, 3, 0, tile_image[tile[draw_tile_array_y][draw_tile_array_x].type], FALSE);
		}
	}

	DrawRotaGraph(HALF_SCREEN_SIZE, HALF_SCREEN_SIZE, 2, 0, player_image[1][player_image_index], TRUE);
	
	DrawBox(5, 50, 525, 130, 0xffffff, TRUE);
	DrawBox(10, 55, 520, 125, 0x000000, TRUE);
	DrawFormatStringToHandle(25, 55, 0xffffff, retro_font_48, "%s  HP %3d MP %3d", player->GetName(), player->GetHp(), /*player->GetMp()*/encount_rate);

	//点滅の表示
	if (screen_blinking_count % 2)DrawBox(0, 0, SCREEN_SIZE, SCREEN_SIZE, 0xffffff, TRUE);
}