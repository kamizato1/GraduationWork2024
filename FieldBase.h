#pragma once
#include"define.h"

#define TILE_SIZE 48 //�^�C���̑傫��
#define DRAW_TILE_NUM 17 //�\������t�B�[���h�̃^�C���̐�

class FieldBase
{
protected:

    class Player* player;

    //�\���̐錾

    struct FIELD_PLAYER
    {
        VECTOR2_I location;//�v���C���[�̍��W
        VECTOR2_I location_index;//�v���C���[�̈ړ���̃^�C���̔z��ԍ�
    };

    struct FIELD_TILE
    {
        VECTOR2_I location;//�^�C���̍��W
        int type;//�^�C���̎��
        int enemy_rank;//�^�C���ŏo������G�̃����N
    };

    //�\����

    FIELD_PLAYER field_player;

    //�摜

    int player_image[2][5];

    //�ϐ�
    float player_image_change_time;//�摜�؂�ւ�����
    int player_image_index;//�v���C���[�摜�v�f��

    //�t�H���g
    int retro_font_48;

    //�֐�
    virtual void SetField() = 0; //�t�B�[���h�𐶐�
    void UpdatePlayerImageIndex(float delta_time);
    VECTOR2_I UpdateMovement(VECTOR2_I field_tile_location);//�v���C���[�ړ�����
    bool UpdateScroll(FIELD_TILE field_tile, VECTOR2_I field_player_location_index);//�v���C���[�X�N���[������
    bool UpdateAddScrollValue(int* field_player_location, int field_tile_location);//�X�N���[���̒l�̉��Z

public:
    FieldBase(class Player* player);
    ~FieldBase();

    virtual int Update(float delta_time) = 0;//�߂�l�����I
    virtual void Draw() const = 0;
};