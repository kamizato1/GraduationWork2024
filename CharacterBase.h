#pragma once
#include"define.h"

class CharacterBase
{
private:

    CHARACTER_DATA character_data;

public:

    CharacterBase(CHARACTER_DATA character_data);
    ~CharacterBase();

    virtual bool Update(float delta_time) = 0;
    virtual void Draw() const = 0;

    int GetHp()const;
    int GetMp()const;
    int SetHp(int hp);
    int SetMp(int mp);
    int GetAttackPower()const;
    int HitAttack(int attack_power);
    const char* GetName()const;
};