#pragma once

#include <string>

class CharacterBase
{
private:

    std::string name;

    int hp;
    int mp;
    int attack_power;
    int defense_power;
    int speed;

public:

    CharacterBase(const std::string& name, int hp, int mp, int attack_power, int defense_power, int speed);
    ~CharacterBase();

    virtual bool Update(float delta_time) = 0;
    virtual void Draw() const = 0;

    int GetHp()const;
    int GetMp()const;
    int SetHp(int hp);
    int SetMp(int mp);
    const char* GetName()const;
};