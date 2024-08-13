#pragma once
#include"FieldBase.h"

class Field : public FieldBase
{
private:

    class Tile* tile[10][10];

    class Player;

    void SetField() override;//フィールドを生成

public:
    Field();
    ~Field();

    bool Update(float delta_time) override;//戻り値あるよ！
    void Draw() const override;
};