#pragma once
#include"CharacterBase.h"
#include"NpcBase.h"
#include"define.h"

class Player : public CharacterBase, public NpcBase
{
private:

public:

    Player();
    ~Player();

    bool Update(float delta_time) override;//ñﬂÇËílÇ†ÇÈÇÊÅI

    VECTOR2_I GetDirectionIndex()const;
    void Draw() const override;

    void Draw(int image_index) const;

    VECTOR2_I UpdateLocationIndex()override;

};