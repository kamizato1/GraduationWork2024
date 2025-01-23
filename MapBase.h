#pragma once
#include"define.h"

#define TILE_SIZE 48 //�^�C���̑傫��
#define DRAW_TILE_NUM 17 //�\������t�B�[���h�̃^�C���̐�

class MapBase
{
protected:

    class Player* player;

    //�\���̐錾

    struct PLAYER
    {
        VECTOR2_I location;//�v���C���[�̍��W
        VECTOR2_I location_index;//�v���C���[�̈ړ���̃^�C���̔z��ԍ�
    };

    struct TILE
    {
        VECTOR2_I location;//�^�C���̍��W
        int type;//�^�C���̎��
        int enemy_rank;//�^�C���ŏo������G�̃����N
    };

    //�\����

    PLAYER map_player;

    //�摜

    int player_image[2][5];

    //�ϐ�
    float player_image_change_time;//�摜�؂�ւ�����
    int player_image_index;//�v���C���[�摜�v�f��

    //�t�H���g
    int retro_font_48;

    //�֐�
    virtual void SetMap() = 0; //�t�B�[���h�𐶐�
    void UpdatePlayerImageIndex(float delta_time);
    VECTOR2_I UpdateMovement(VECTOR2_I map_tile_location);//�v���C���[�ړ�����
    bool UpdateScroll(TILE map_tile, VECTOR2_I map_player_location_index);//�v���C���[�X�N���[������
    bool UpdateAddScrollValue(int* map_player_location, int map_tile_location);//�X�N���[���̒l�̉��Z
    //int Base36ToDecimal();

public:
    MapBase(class Player* player);
    ~MapBase();

    virtual int Update(float delta_time) = 0;//�߂�l�����I
    virtual void Draw() const = 0;
};