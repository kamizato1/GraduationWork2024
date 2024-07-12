#include"DxLib.h"
#include"BattleField.h"


BattleField::BattleField(I_VECTOR2 field_array_size)
{
	SetBattleField();

	OutputDebugString("BattleFieldコンストラクタ呼ばれました。\n");
}

void BattleField::SetBattleField()
{
}

BattleField::~BattleField()
{
	OutputDebugString("BattleFieldデストラクタ呼ばれました。\n");
}

bool BattleField::Update(float delta_time)
{
	return false;
}

void BattleField::Draw() const
{
	//背景画像表示
}