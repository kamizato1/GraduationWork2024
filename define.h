#pragma once
#include <string>

#define FONT_SIZE 30 // �����̑傫��

#define SCREEN_SIZE 720 //��ʃT�C�Y

#define HALF_SCREEN_SIZE 360

#define FIELD_TILE_NUM_X 256
#define FIELD_TILE_NUM_Y 256

#define BLOCK_TYPE_NUM 17//�u���b�N�̎��

#define BLOCK_SIZE 36.0f //�u���b�N�̃T�C�Y

#define ENEMY_TYPE_NUM 30

struct F_VECTOR2 //���W,�傫��,�X�s�[�h�ȂǂɎg��(float�^)
{
    float x, y;
};

struct I_VECTOR2 //�z��̍��W�ȂǂɎg��(int�^)
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


