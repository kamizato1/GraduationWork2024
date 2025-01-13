#pragma once
#include"CharacterBase.h"
#include <string>

class EnemyBase : public CharacterBase
{
public:

    EnemyBase(CHARACTER_DATA enemy_data);
    ~EnemyBase();

    bool Update(float delta_time);
    void Draw() const;
};