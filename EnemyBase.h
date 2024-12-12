#pragma once
#include"CharacterBase.h"
#include <string>

class EnemyBase : public CharacterBase
{
private:

    int enemy_image;

public:

    EnemyBase(CHARACTER_DATA enemy_data, int enemy_image);
    ~EnemyBase();

    bool Update(float delta_time);
    void Draw() const;
};