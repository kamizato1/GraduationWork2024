#pragma once
#include"MapBase.h"

#define TILE_TYPE_NUM 28
#define TILE_NUM 32

class TownMap : public MapBase
{
private:

    TILE tile[TILE_NUM][TILE_NUM];

    //�摜
    int tile_image[TILE_TYPE_NUM];

    //�֐�
    void SetMap()override;//�t�B�[���h�𐶐�

public:
    TownMap(class Player* player);
    ~TownMap();

    int Update(float delta_time)override;//�߂�l�����I
    void Draw() const override;
};