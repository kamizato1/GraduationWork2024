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
    int AddHp(int add_hp);
    int AddMp(int add_mp);
    int GetAttackPower()const;
    int Attack(CharacterBase* character_base);
    int GetImage()const;
    const char* GetName()const;
    void SetName(const char* name);
};