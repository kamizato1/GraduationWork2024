#include"DxLib.h"
#include"Player.h"

Player::Player() : CharacterBase("���݂���", 20, 10, 5, 5, 5)
{
	OutputDebugString("CharacterBase�R���X�g���N�^�Ă΂�܂����B\n");
}

Player::~Player()
{
	OutputDebugString("CharacterBase�f�X�g���N�^�Ă΂�܂����B\n");
}

bool Player::Update(float delta_time)
{
	return false;
}

void Player::Draw() const
{

}