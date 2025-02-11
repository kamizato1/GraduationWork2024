#include"DxLib.h"
#include"EnemyBase.h"
#include"define.h"

EnemyBase::EnemyBase(CHARACTER_DATA enemy_data) : CharacterBase(enemy_data)
{
	OutputDebugString("EnemyBaseコンストラクタ呼ばれました。\n");
}

EnemyBase::~EnemyBase()
{
	OutputDebugString("EnemyBaseデストラクタ呼ばれました。\n");
}

bool EnemyBase::Update(float delta_time)
{
	return false;
}

void EnemyBase::Draw() const
{
	DrawRotaGraph(HALF_SCREEN_SIZE, 300, 2.5, 0, GetImage(), TRUE);
}