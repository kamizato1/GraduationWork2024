#include"DxLib.h"
#include"Field.h"
#include"Key.h"

#define TILE_SIZE_X 48
#define TILE_SIZE_Y 48

#define DRAW_TILE_NUM_X 17
#define DRAW_TILE_NUM_Y 17

#define PLAYER_SPEED 2

int Clamp(int value, int min, int max)//値が範囲外にならないようにする
{
	if (min > max)
	{
		int work = min;
		min = max;
		max = work;
	}

	if (value > max) return max;
	else if (value < min)return min;

	return value;
}

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

Field::Field()
{
	SetFontSize(10);

   /* class PlayerManager* player_manager;
    class EnemyManager* enemy_manager;
    class AttackManager* attack_manager;
    class EventManager* event_manager;*/

	if (LoadDivGraph("image/Field/tile.png", TILE_TYPE_NUM, TILE_TYPE_NUM, 1, 16, 16, tile_image) == -1)throw("image/Field/tile.pngが読み込めません\n");

	SetField();

	//プレイヤーの初期位置の設定

	//配列
	player.target_tile_array.x = 166;
	player.target_tile_array.y = 60;

	//座標
	player.position.x = (player.target_tile_array.x * TILE_SIZE_X) + (TILE_SIZE_X / 2);
	player.position.y = (player.target_tile_array.y * TILE_SIZE_Y) + (TILE_SIZE_Y / 2);

	player.speed = 0;

    OutputDebugString("Fieldコンストラクタ呼ばれました。\n");
}

void Field::SetField()
{
	FILE* field_data = nullptr;//フィールド読み込み

	errno_t error_field_data = fopen_s(&field_data, "data/field.txt", "r");
	if (error_field_data != 0)throw("data/field.txtが読み込めません\n");//エラーチェック

	for (int i = 0; i < FIELD_TILE_NUM_Y; i++)
	{
		for (int j = 0; j < FIELD_TILE_NUM_X; j++)
		{
			tile[i][j].position.x = (j * TILE_SIZE_X) + (TILE_SIZE_X / 2);
			tile[i][j].position.y = (i * TILE_SIZE_Y) + (TILE_SIZE_Y / 2);
			fscanf_s(field_data, "%d", &tile[i][j].type);
		}
	}

	fclose(field_data);
}

Field::~Field()
{
    OutputDebugString("Fieldデストラクタが呼ばれました。\n");
}


bool Field::Update(float delta_time)
{
	I_VECTOR2 target_position = tile[player.target_tile_array.y][player.target_tile_array.x].position;

	if ((player.position.x == target_position.x) &&
		(player.position.y == target_position.y))
	{
		I_VECTOR2 player_target_tile_array = player.target_tile_array;

		if (Key::KeyPressed(KEY_TYPE::UP))
		{
			player.target_tile_array.y = WrapAround(player.target_tile_array.y - 1, 0, FIELD_TILE_NUM_Y - 1), player.speed = -PLAYER_SPEED;
		}
		else if (Key::KeyPressed(KEY_TYPE::DOWN))
		{
			player.target_tile_array.y = WrapAround(player.target_tile_array.y + 1, 0, FIELD_TILE_NUM_Y - 1), player.speed = PLAYER_SPEED;
		}
		else if (Key::KeyPressed(KEY_TYPE::LEFT))
		{
			player.target_tile_array.x = WrapAround(player.target_tile_array.x - 1, 0, FIELD_TILE_NUM_X - 1), player.speed = -PLAYER_SPEED;
		}
		else if (Key::KeyPressed(KEY_TYPE::RIGHT))
		{
			player.target_tile_array.x = WrapAround(player.target_tile_array.x + 1, 0, FIELD_TILE_NUM_X - 1), player.speed = PLAYER_SPEED;
		}

		//当たり判定
		if (tile[player.target_tile_array.y][player.target_tile_array.x].type >= 17)
		{
			player.target_tile_array = player_target_tile_array;
		}
	}
	else
	{
		if (player.position.x != target_position.x)
		{
			player.position.x = WrapAround(player.position.x + player.speed, 0, (FIELD_TILE_NUM_X * TILE_SIZE_X) - 1);
		}
		else
		{
			player.position.y = WrapAround(player.position.y + player.speed, 0, (FIELD_TILE_NUM_Y * TILE_SIZE_Y) - 1);
		}
	}

    return false;
}

void Field::Draw() const
{
	for (int i = 0; i < DRAW_TILE_NUM_Y; i++)//縦の繰り返し
	{
		for (int j = 0; j < DRAW_TILE_NUM_X; j++)//横の繰り返し
		{
			int draw_tile_array_x = WrapAround(player.target_tile_array.x - (DRAW_TILE_NUM_X / 2) + j, 0, FIELD_TILE_NUM_X - 1);
			int draw_tile_array_y = WrapAround(player.target_tile_array.y - (DRAW_TILE_NUM_Y / 2) + i, 0, FIELD_TILE_NUM_Y - 1);

			int x = WrapAround(tile[draw_tile_array_y][draw_tile_array_x].position.x - player.position.x + (SCREEN_SIZE_X / 2), -(TILE_SIZE_X / 2), tile[FIELD_TILE_NUM_Y - 1][FIELD_TILE_NUM_X - 1].position.x - 1);
			int y = WrapAround(tile[draw_tile_array_y][draw_tile_array_x].position.y - player.position.y + (SCREEN_SIZE_Y / 2), -(TILE_SIZE_Y / 2), tile[FIELD_TILE_NUM_Y - 1][FIELD_TILE_NUM_X - 1].position.y - 1);

			DrawRotaGraph(x, y, 3, 0, tile_image[tile[draw_tile_array_y][draw_tile_array_x].type], FALSE);
			//DrawFormatString(x - 20, y, 0xffffff, "%d", tile[draw_tile_array_y][draw_tile_array_x].position.y);
		}
	}

	DrawFormatString(0, 20, 0xffffff, "target_position x = %d, y = %d", tile[player.target_tile_array.y][player.target_tile_array.x].position.x, tile[player.target_tile_array.y][player.target_tile_array.x].position.y);
	DrawFormatString(0, 40, 0xffffff, "player_position x = %d, y = %d", player.position.x, player.position.y);
	//DrawFormatString(0, 60, 0xffffff, "%d", tile[FIELD_TILE_NUM_Y - 1][FIELD_TILE_NUM_X - 1].position.y);
	//DrawFormatString(0, 80, 0xffffff, "%d", ((FIELD_TILE_NUM_Y - 1) * TILE_SIZE_Y) + (TILE_SIZE_Y / 2));

}