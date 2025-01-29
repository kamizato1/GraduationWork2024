#include"DxLib.h"
#include"MapBase.h"
#include"Player.h"
#include"NpcBase.h"
#include"Key.h"

#define IMAGE_INDEX_CHANGE_TIME 0.2f //画像切り替え時間
#define IMAGE_INDEX 3 //プレイヤー画像配列数

#define PLAYER_SPEED 2 //プレイヤーの移動速度


MapBase::MapBase(Player* player)
{
	this->player = player;
	
	//フォントの読み込み
	retro_font_48 = LoadFontDataToHandle("data/font/DragonQuestFont48.dft", 0);

	//変数
	image_index_change_time = 0.0f;
	image_index = 0;
	add_image_index = 1;

	OutputDebugString("MapBaseコンストラクタ呼ばれました。\n");
}

MapBase::~MapBase()
{
	OutputDebugString("MapBaseデストラクタが呼ばれました。\n");
}

void MapBase::UpdateImageIndex(float delta_time)
{
	if ((image_index_change_time += delta_time) > IMAGE_INDEX_CHANGE_TIME)
	{
		image_index += add_image_index;
		if ((image_index == 0) || (image_index == IMAGE_INDEX - 1))add_image_index *= -1;
		image_index_change_time = 0.0f;
	}
}