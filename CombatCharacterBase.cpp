#include"DxLib.h"
#include"CombatCharacterBase.h"

CombatCharacterBase::CombatCharacterBase(F_VECTOR2 array_location, F_VECTOR2 tile_size, int hp, int mp, int attack_power, int defense_power) : CharacterBase(array_location, tile_size)
{
    this->hp = hp;
    this->mp = mp;
    max_hp = hp;
    max_mp = mp;
    this->attack_power = attack_power;
    this->defense_power = defense_power;
    is_dead = false;

    OutputDebugString("CombatCharacterBaseコンストラクタ呼ばれました。\n");
}

CombatCharacterBase::~CombatCharacterBase()
{
    OutputDebugString("CombatCharacterBaseデストラクタが呼ばれました。\n");
}

int CombatCharacterBase::GetHp()const
{
    return hp;
}

int CombatCharacterBase::GetMp()const
{
    return mp;
}

bool CombatCharacterBase::GetIsDead()const
{
    return is_dead;
}

void CombatCharacterBase::SetHp(int hp)
{
    if (!is_dead)
    {
        if (hp > 0)
        {
            if (hp > max_hp)this->hp = max_hp;
            else this->hp = hp;
        }
        else
        {
            hp = 0;
            is_dead = true;
        }
    }
}

void CombatCharacterBase::SetMp(int mp)
{
    if (!is_dead)
    {
        if (mp > 0)
        {
            if (mp > max_hp)this->mp = max_hp;
            else this->mp = mp;
        }
        else mp = 0;
    }
}

void CombatCharacterBase::AddMp(int add_mp)
{
    if (!is_dead)
    {
        if ((mp += add_mp) > max_mp)mp = max_mp;
        else if (mp < 0)mp = 0;
    }
}

void CombatCharacterBase::AddHp(int add_hp)
{
    if (!is_dead)
    {
        if ((hp += add_hp) > max_hp)hp = max_hp;
        else if (hp < 0)
        {
            hp = 0;
            is_dead = true;
        }
    }
}