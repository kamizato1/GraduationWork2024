#pragma once
#include"FieldBase.h"
#include"define.h"

#define TILE_TYPE_NUM 23

class Field : public FieldBase
{
private:

    struct PLAYER
    {
        I_VECTOR2 position;//プレイヤーの座標
        I_VECTOR2 target_tile_array;//プレイヤーの移動先のタイルの配列番号
        int speed;
    };

    PLAYER player;

    struct TILE
    {
        I_VECTOR2 position;//タイルの座標
        int type;//タイルの種類
    };

    TILE tile[FIELD_TILE_NUM_Y][FIELD_TILE_NUM_X];

    int tile_image[TILE_TYPE_NUM];

    void SetField() override;//フィールドを生成

public:
    Field();
    ~Field();

    bool Update(float delta_time) override;//戻り値あるよ！
    void Draw() const override;
};