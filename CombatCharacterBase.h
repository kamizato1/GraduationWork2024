#pragma once
#include"CharacterBase.h"

class CombatCharacterBase : public CharacterBase
{
protected:

    int hp;//�U����
    int mp;//���@��
    int max_hp;
    int max_mp;
    int attack_power;//�U����
    int defense_power;//�����

    bool is_dead;//����ł��邩�H

public:
    CombatCharacterBase(F_VECTOR2 array_location, F_VECTOR2 tile_size, int hp, int mp, int attack_power, int defense_power);
    ~CombatCharacterBase();

    int GetHp()const;
    int GetMp()const;
    bool GetIsDead()const;

    void SetHp(int hp);
    void SetMp(int mp);

    void AddHp(int hp);
    void AddMp(int mp);
};