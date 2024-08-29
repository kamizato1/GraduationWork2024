#pragma once

#define FONT_SIZE 35 // 文字の大きさ

#define SCREEN_SIZE_X 720 //横画面サイズ
#define SCREEN_SIZE_Y 720 //縦画面サイズ

#define HALF_SCREEN_SIZE_X 360
#define HALF_SCREEN_SIZE_Y 360

#define FIELD_TILE_NUM_X 256
#define FIELD_TILE_NUM_Y 256

#define BLOCK_TYPE_NUM 17//ブロックの種類

#define BLOCK_SIZE 36.0f //ブロックのサイズ

struct F_VECTOR2 //座標,大きさ,スピードなどに使う(float型)
{
    float x, y;
};

struct I_VECTOR2 //配列の座標などに使う(int型)
{
    int x, y;
};

