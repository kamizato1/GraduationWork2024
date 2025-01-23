#pragma once
#include <string>

#define FONT_SIZE 30 // 文字の大きさ

#define SCREEN_SIZE 720 //画面サイズ

#define HALF_SCREEN_SIZE 360

#define ENEMY_TYPE_NUM 30

struct F_VECTOR2 //座標,大きさ,スピードなどに使う(float型)
{
    float x, y;
};

class VECTOR2_I //配列の座標などに使う(int型)
{
public:

    int x,y;

public:

    bool operator== (VECTOR2_I& other)const
    {
        return ((this->x == other.x) && (this->y == other.y));
    }
};

struct CHARACTER_DATA
{
    std::string name;
    int hp;
    int mp;
    int max_hp;
    int max_mp;
    int attack_power;
    int defense_power;
    int speed;
    int image;
};


