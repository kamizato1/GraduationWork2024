#include"DxLib.h"
#include"BattleField.h"


BattleField::BattleField(I_VECTOR2 field_array_size)
{
	SetBattleField();

	OutputDebugString("BattleField�R���X�g���N�^�Ă΂�܂����B\n");
}

void BattleField::SetBattleField()
{
}

BattleField::~BattleField()
{
	OutputDebugString("BattleField�f�X�g���N�^�Ă΂�܂����B\n");
}

bool BattleField::Update(float delta_time)
{
	return false;
}

void BattleField::Draw() const
{
	//�w�i�摜�\��
}