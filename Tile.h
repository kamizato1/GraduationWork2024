#pragma once
#include"define.h"

class Tile
{
private:
    int tile_image;//ƒ^ƒCƒ‹‰æ‘œ

    F_VECTOR2 tile_location;
    F_VECTOR2 tile_radius;

    class CharacterManager* character;

public:
    Tile(F_VECTOR2 tile_location, F_VECTOR2 tile_size);
    ~Tile();

    void Draw(float camera_work)const;
};