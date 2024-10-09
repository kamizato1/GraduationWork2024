#pragma once
#include"CharacterBase.h"
#include"define.h"

class Player : public CharacterBase
{
public:

    Player();
    ~Player();

    bool Update(float delta_time) override;//–ß‚è’l‚ ‚é‚æI
    void Draw() const override;
};