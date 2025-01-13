#include"DxLib.h"
#include"EnemyBase.h"
#include"define.h"

EnemyBase::EnemyBase(CHARACTER_DATA enemy_data) : CharacterBase(enemy_data)
{
	OutputDebugString("EnemyBase�R���X�g���N�^�Ă΂�܂����B\n");
}

EnemyBase::~EnemyBase()
{
	OutputDebugString("EnemyBase�f�X�g���N�^�Ă΂�܂����B\n");
}

bool EnemyBase::Update(float delta_time)
{
	return false;
}

void EnemyBase::Draw() const
{
	DrawRotaGraph(HALF_SCREEN_SIZE, 300, 2.5, 0, GetImage(), TRUE);
}