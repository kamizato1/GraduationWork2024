#pragma once
#include"CharacterBase.h"
#include"define.h"

class Player : public CharacterBase
{
public:

    Player();
    ~Player();

    bool Update(float delta_time) override;//戻り値あるよ！
    void Draw() const override;
};