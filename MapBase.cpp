#include"DxLib.h"
#include"MapBase.h"
#include"Player.h"
#include"Key.h"

#define PLAYER_IMAGE_CHANGE_TIME 0.2f //画像切り替え時間
#define PLAYER_IMAGE_INDEX 4 //プレイヤー画像配列数

#define PLAYER_SPEED 2 //プレイヤーの移動速度


MapBase::MapBase(Player* player)
{
	this->player = player;

	//プレイヤー画像読み込み
	if (LoadDivGraph("data/MapBase/walk.png", 5, 5, 1, 50, 50, player_image[1]) == -1)throw("data/MapBase/walk.pngが読み込めません\n");
	if (LoadDivGraph("data/MapBase/wait.png", 5, 5, 1, 50, 50, player_image[0]) == -1)throw("data/MapBase/wait.pngが読み込めません\n");

	//フォントの読み込み
	retro_font_48 = LoadFontDataToHandle("data/font/DragonQuestFont48.dft", 0);

	//変数
	player_image_change_time = 0.0f;
	player_image_index = 0;

	OutputDebugString("MapBaseコンストラクタ呼ばれました。\n");
}

MapBase::~MapBase()
{
	OutputDebugString("MapBaseデストラクタが呼ばれました。\n");
}

void MapBase::UpdatePlayerImageIndex(float delta_time)
{
	if ((player_image_change_time += delta_time) > PLAYER_IMAGE_CHANGE_TIME)
	{
		if (++player_image_index == PLAYER_IMAGE_INDEX)player_image_index = 0;
		player_image_change_time = 0.0f;
	}
}

VECTOR2_I MapBase::UpdateMovement(VECTOR2_I tile_location)
{
	VECTOR2_I player_location_index = map_player.location_index;

	if (map_player.location == tile_location)
	{
		if (Key::KeyPressed(KEY_TYPE::UP))map_player.location_index.y = map_player.location_index.y - 1;
		else if (Key::KeyPressed(KEY_TYPE::DOWN))map_player.location_index.y = map_player.location_index.y + 1;
		else if (Key::KeyPressed(KEY_TYPE::LEFT))map_player.location_index.x = map_player.location_index.x - 1;
		else if (Key::KeyPressed(KEY_TYPE::RIGHT))map_player.location_index.x = map_player.location_index.x + 1;
	}

	return player_location_index;
}

bool MapBase::UpdateScroll(TILE tile, VECTOR2_I player_location_index)
{
	/*if(tile.type >= 17)map_player.location_index = player_location_index;
	else
	{*/
		if (UpdateAddScrollValue(&map_player.location.x, tile.location.x))return true;
		if (UpdateAddScrollValue(&map_player.location.y, tile.location.y))return true;
	//}

	return false;
}

bool MapBase::UpdateAddScrollValue(int* player_location, int tile_location)
{
	if (*player_location < tile_location)
	{
		if ((*player_location += PLAYER_SPEED) >= tile_location)
		{
			*player_location = tile_location;
			return true;
		}
	}
	else if (*player_location > tile_location)
	{
		if ((*player_location -= PLAYER_SPEED) <= tile_location)
		{
			*player_location = tile_location;
			return true;
		}
	}

	return false;
}