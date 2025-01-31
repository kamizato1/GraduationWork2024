#include"DxLib.h"
#include"Player.h"
#include"Key.h"

Player::Player() : CharacterBase(CHARACTER_DATA{"かみざと", 200, 100,200, 100, 25, 25, 5 }), 
NpcBase(VECTOR2_I{0, 0}, VECTOR2_I{0, 0} , nullptr, "a")
{
	//プレイヤー画像読み込み
	if (LoadDivGraph("data/MapBase/image.png", 16, 4, 4, 16, 16, image) == -1)throw("data/MapBase/player_image.pngが読み込めません\n");

	OutputDebugString("CharacterBaseコンストラクタ呼ばれました。\n");
}

Player::~Player()
{
	OutputDebugString("CharacterBaseデストラクタ呼ばれました。\n");
}

bool Player::Update(float delta_time)
{
	return false;
}

VECTOR2_I Player::UpdateMovement(VECTOR2_I tile_location)
{
	VECTOR2_I location_index = this->location_index;

	if (location == tile_location)
	{
		if (Key::KeyPressed(KEY_TYPE::UP))this->location_index.y -= 1, image_direction_index = 0;
		else if (Key::KeyPressed(KEY_TYPE::DOWN))this->location_index.y += 1, image_direction_index = 1;
		else if (Key::KeyPressed(KEY_TYPE::LEFT))this->location_index.x -= 1, image_direction_index = 2;
		else if (Key::KeyPressed(KEY_TYPE::RIGHT))this->location_index.x += 1, image_direction_index = 3;
	}

	return location_index;
}

void Player::Draw() const
{

}

void Player::Draw(int image_index) const
{
	DrawRotaGraph(HALF_SCREEN_SIZE, HALF_SCREEN_SIZE, 3, 0, image[(image_direction_index * 4) + image_index], TRUE);
}