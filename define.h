#pragma once
#include <string>

#define FONT_SIZE 30 // 文字の大きさ

#define SCREEN_SIZE 720 //画面サイズ

#define HALF_SCREEN_SIZE 360

#define FIELD_TILE_NUM_X 256
#define FIELD_TILE_NUM_Y 256

#define BLOCK_TYPE_NUM 17//ブロックの種類

#define BLOCK_SIZE 36.0f //ブロックのサイズ

#define ENEMY_TYPE_NUM 30

struct F_VECTOR2 //座標,大きさ,スピードなどに使う(float型)
{
    float x, y;
};

struct I_VECTOR2 //配列の座標などに使う(int型)
{
    int x, y;
};

struct CHARACTER_DATA
{
    std::string name;
    int hp;
    int mp;
    int attack_power;
    int defense_power;
    int speed;
};


