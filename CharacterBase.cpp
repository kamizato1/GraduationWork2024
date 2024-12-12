#include"DxLib.h"
#include"CharacterBase.h"

CharacterBase::CharacterBase(CHARACTER_DATA character_data)
{
	this->character_data = character_data;

	OutputDebugString("CharacterBaseコンストラクタ呼ばれました。\n");
}

CharacterBase::~CharacterBase()
{
	OutputDebugString("CharacterBaseデストラクタ呼ばれました。\n");
}

int CharacterBase::GetHp()const
{
	return character_data.hp;
}

int CharacterBase::GetMp()const
{
	return character_data.mp;
}

int CharacterBase::SetHp(int hp)
{
	character_data.hp = hp;
	if (character_data.hp < 0)character_data.hp = 0;
	return 0;
}

int CharacterBase::SetMp(int mp)
{
	return 0;
}

int CharacterBase::GetAttackPower()const
{
	return character_data.attack_power;
}

const char* CharacterBase::GetName()const
{
	return character_data.name.c_str();
}

int CharacterBase::HitAttack(int attack_power)
{
	int damage = (attack_power / 2) - (character_data.defense_power / 4);
	SetHp(character_data.hp - damage);
	return damage;
}