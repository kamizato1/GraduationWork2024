#pragma once
#include"CharacterBase.h"
#include"define.h"

class Player : public CharacterBase
{
public:

    Player();
    ~Player();

    bool Update(float delta_time) override;//�߂�l�����I
    void Draw() const override;
};