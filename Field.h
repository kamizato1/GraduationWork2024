#pragma once
#include"FieldBase.h"

class Field : public FieldBase
{
private:

    class Tile* tile[10][10];

    class Player;

    void SetField() override;//�t�B�[���h�𐶐�

public:
    Field();
    ~Field();

    bool Update(float delta_time) override;//�߂�l�����I
    void Draw() const override;
};