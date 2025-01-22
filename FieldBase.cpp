#include"DxLib.h"
#include"FieldBase.h"
#include"Player.h"
#include"Key.h"

#define PLAYER_IMAGE_CHANGE_TIME 0.2f //画像切り替え時間
#define PLAYER_IMAGE_INDEX 4 //プレイヤー画像配列数

#define PLAYER_SPEED 2 //プレイヤーの移動速度


FieldBase::FieldBase(Player* player)
{
	this->player = player;

	//プレイヤー画像読み込み
	if (LoadDivGraph("data/image/Field/Player/walk.png", 5, 5, 1, 50, 50, player_image[1]) == -1)throw("data/image/Field/Player/walk.pngが読み込めません\n");
	if (LoadDivGraph("data/image/Field/Player/wait.png", 5, 5, 1, 50, 50, player_image[0]) == -1)throw("data/image/Field/Player/wait.png.pngが読み込めません\n");

	//フォントの読み込み
	retro_font_48 = LoadFontDataToHandle("data/font/DragonQuestFont48.dft", 0);

	//変数
	player_image_change_time = 0.0f;
	player_image_index = 0;

	OutputDebugString("FieldBaseコンストラクタ呼ばれました。\n");
}

FieldBase::~FieldBase()
{
	OutputDebugString("FieldBaseデストラクタが呼ばれました。\n");
}

void FieldBase::UpdatePlayerImageIndex(float delta_time)
{
	if ((player_image_change_time += delta_time) > PLAYER_IMAGE_CHANGE_TIME)
	{
		if (++player_image_index == PLAYER_IMAGE_INDEX)player_image_index = 0;
		player_image_change_time = 0.0f;
	}
}

VECTOR2_I FieldBase::UpdateMovement(VECTOR2_I field_tile_location)
{
	VECTOR2_I field_player_location_index = field_player.location_index;

	if (field_player.location == field_tile_location)
	{
		if (Key::KeyPressed(KEY_TYPE::UP))field_player.location_index.y = field_player.location_index.y - 1;
		else if (Key::KeyPressed(KEY_TYPE::DOWN))field_player.location_index.y = field_player.location_index.y + 1;
		else if (Key::KeyPressed(KEY_TYPE::LEFT))field_player.location_index.x = field_player.location_index.x - 1;
		else if (Key::KeyPressed(KEY_TYPE::RIGHT))field_player.location_index.x = field_player.location_index.x + 1;

		//当たり判定
		//if (field_tile[field_player.location_index.y][field_player.location_index.x].type >= 17)field_player.location_index = location_index;

	}

	return field_player_location_index;
}

bool FieldBase::UpdateScroll(FIELD_TILE field_tile, VECTOR2_I field_player_location_index)
{
	if(field_tile.type >= 17)field_player.location_index = field_player_location_index;
	else
	{
		if (UpdateAddScrollValue(&field_player.location.x, field_tile.location.x))return true;
		if (UpdateAddScrollValue(&field_player.location.y, field_tile.location.y))return true;
	}

	return false;
}

bool FieldBase::UpdateAddScrollValue(int* field_player_location, int field_tile_location)
{
	if (*field_player_location < field_tile_location)
	{
		if ((*field_player_location += PLAYER_SPEED) >= field_tile_location)
		{
			*field_player_location = field_tile_location;
			return true;
		}
	}
	else if (*field_player_location > field_tile_location)
	{
		if ((*field_player_location -= PLAYER_SPEED) <= field_tile_location)
		{
			*field_player_location = field_tile_location;
			return true;
		}
	}

	return false;
}