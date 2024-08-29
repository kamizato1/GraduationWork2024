#pragma once
#include"FieldBase.h"
#include"define.h"

#define TILE_TYPE_NUM 23

class Field : public FieldBase
{
private:

    struct PLAYER
    {
        I_VECTOR2 position;//�v���C���[�̍��W
        I_VECTOR2 target_tile_array;//�v���C���[�̈ړ���̃^�C���̔z��ԍ�
        int speed;
    };

    PLAYER player;

    struct TILE
    {
        I_VECTOR2 position;//�^�C���̍��W
        int type;//�^�C���̎��
    };

    TILE tile[FIELD_TILE_NUM_Y][FIELD_TILE_NUM_X];

    int tile_image[TILE_TYPE_NUM];

    void SetField() override;//�t�B�[���h�𐶐�

public:
    Field();
    ~Field();

    bool Update(float delta_time) override;//�߂�l�����I
    void Draw() const override;
};