#include"DxLib.h"
#include"Player.h"

Player::Player() : CharacterBase(CHARACTER_DATA{"かみざと", 20, 10, 5, 5, 5 })
{
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

void Player::Draw() const
{

}