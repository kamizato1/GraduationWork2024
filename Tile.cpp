#include"DxLib.h"
#include"Tile.h"

Tile::Tile(F_VECTOR2 tile_location, F_VECTOR2 tile_size)
{
    this->tile_location = tile_location;
    this->tile_radius = { tile_size.x / 2, tile_size.y / 2 };
    tile_image = NULL;
    character = nullptr;

    OutputDebugString("Tileコンストラクタ呼ばれました。\n");
}

Tile::~Tile()
{
    DeleteGraph(tile_image);
    delete character;
    OutputDebugString("Tileデストラクタが呼ばれました。\n");
}

void Tile::Draw(float camera_work)const
{
    DrawBox(tile_location.x - tile_radius.x, tile_location.y - tile_radius.y, tile_location.x + tile_radius.x, tile_location.y + tile_radius.y, 0x00ff00, TRUE);
    DrawBox(tile_location.x - tile_radius.x, tile_location.y - tile_radius.y, tile_location.x + tile_radius.x, tile_location.y + tile_radius.y, 0x000000, FALSE);
}