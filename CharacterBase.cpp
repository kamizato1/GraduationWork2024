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

	if (character_data.hp > character_data.max_hp)character_data.hp = character_data.max_hp;
	else if (character_data.hp < 0)character_data.hp = 0;
	
	return 0;
}

int CharacterBase::SetMp(int mp)
{
	return 0;
}

int CharacterBase::AddHp(int add_hp)
{
	return SetHp(character_data.hp + add_hp);
}

int CharacterBase::AddMp(int add_mp)
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

void CharacterBase::SetName(const char* name)
{
	character_data.name = name;
}

int CharacterBase::GetImage()const
{
	return character_data.image;
}

int CharacterBase::Attack(CharacterBase* character_base)
{
	int damage = (character_data.attack_power / 2) - (character_base->character_data.defense_power / 4);
	if (damage < 0)damage = 0;

	character_base->AddHp(-damage);

	return damage;
}