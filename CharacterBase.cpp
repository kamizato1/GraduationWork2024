#include"DxLib.h"
#include"CharacterBase.h"

CharacterBase::CharacterBase(const std::string& name, int hp, int mp, int attack_power, int defense_power, int speed)
{
	this->name = name;
	this->hp = hp;
	this->mp = mp;
	this->attack_power = attack_power;
	this->defense_power = defense_power;
	this->speed = speed;

	OutputDebugString("CharacterBaseコンストラクタ呼ばれました。\n");
}

CharacterBase::~CharacterBase()
{
	OutputDebugString("CharacterBaseデストラクタ呼ばれました。\n");
}

int CharacterBase::GetHp()const
{
	return hp;
}

int CharacterBase::GetMp()const
{
	return mp;
}

int CharacterBase::SetHp(int hp)
{
	return 0;
}

int CharacterBase::SetMp(int mp)
{
	return 0;
}

const char* CharacterBase::GetName()const
{
	return name.c_str();
}