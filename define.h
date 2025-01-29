#pragma once
#include <string>

#define FONT_SIZE 30 // �����̑傫��

#define SCREEN_SIZE 720 //��ʃT�C�Y

#define HALF_SCREEN_SIZE 360

#define ENEMY_TYPE_NUM 30

struct F_VECTOR2 //���W,�傫��,�X�s�[�h�ȂǂɎg��(float�^)
{
    float x, y;
};

class VECTOR2_I //�z��̍��W�ȂǂɎg��(int�^)
{
public:

    int x,y;

public:

    bool operator== (VECTOR2_I& other)const
    {
        return ((this->x == other.x) && (this->y == other.y));
    }

    VECTOR2_I operator+= (VECTOR2_I& other)
    {
        this->x += other.x;
        this->y += other.y;

        return *this;
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

enum class GAME_SCENE_TYPE
{
    WORLD_MAP, //���[���h�}�b�v
    TOWN_MAP,
    BATTLE //�o�g��
};


