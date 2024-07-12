#pragma once
#include"CharacterBase.h"

class CombatCharacterBase : public CharacterBase
{
protected:
    int hp;//攻撃力
    int mp;//魔法力
    int max_hp;
    int max_mp;
    int attack_power;//攻撃力
    int defense_power;//守備力

    bool is_dead;//死んでいるか？

public:
    CombatCharacterBase(DATA location, DATA size, int hp, int mp, int attack_power, int defense_power);
    ~CombatCharacterBase();

    //攻撃を食らった時の処理
    virtual bool HitDamege(BoxCollider* bc, int attack_power) { return false; }

    int GetHp()const;
    int GetMp()const;
    bool GetIsDead()const;

    void SetHp(int hp);
    void SetMp(int mp);

    void AddHp(int hp);
    void AddMp(int mp);
};