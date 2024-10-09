#pragma once
#include"CharacterBase.h"
#include <string>

class EnemyBase : public CharacterBase
{
private:
    int enemy_image;

public:

    EnemyBase(const std::string& name, int hp, int mp, int attack_power, int defense_power, int speed, int enemy_image);
    ~EnemyBase();

    bool Update(float delta_time);
    void Draw() const;
};