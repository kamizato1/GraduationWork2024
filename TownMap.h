#pragma once
#include"MapBase.h"

#define TILE_TYPE_NUM 28
#define TILE_NUM 32

class TownMap : public MapBase
{
private:

    TILE tile[TILE_NUM][TILE_NUM];

    //画像
    int tile_image[TILE_TYPE_NUM];

    //関数
    void SetMap()override;//フィールドを生成

public:
    TownMap(class Player* player);
    ~TownMap();

    int Update(float delta_time)override;//戻り値あるよ！
    void Draw() const override;
};