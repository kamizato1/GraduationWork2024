#pragma once

#define FONT_SIZE 35 // �����̑傫��

#define SCREEN_SIZE_X 720 //����ʃT�C�Y
#define SCREEN_SIZE_Y 720 //�c��ʃT�C�Y

#define HALF_SCREEN_SIZE_X 360
#define HALF_SCREEN_SIZE_Y 360

#define FIELD_TILE_NUM_X 256
#define FIELD_TILE_NUM_Y 256

#define BLOCK_TYPE_NUM 17//�u���b�N�̎��

#define BLOCK_SIZE 36.0f //�u���b�N�̃T�C�Y

struct F_VECTOR2 //���W,�傫��,�X�s�[�h�ȂǂɎg��(float�^)
{
    float x, y;
};

struct I_VECTOR2 //�z��̍��W�ȂǂɎg��(int�^)
{
    int x, y;
};

