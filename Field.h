#pragma once
#include"define.h"

#define TILE_TYPE_NUM 23

class Field
{
private:

    char i = 0;

    class Player* player;

    struct PLAYER
    {
        I_VECTOR2 position;//�v���C���[�̍��W
        I_VECTOR2 target_tile_array;//�v���C���[�̈ړ���̃^�C���̔z��ԍ�
        int speed;
    };

    PLAYER field_player;

    struct TILE
    {
        I_VECTOR2 position;//�^�C���̍��W
        int type;//�^�C���̎��
        int enemy_rank;//�^�C���ŏo������G�̃����N
    };

    TILE tile[FIELD_TILE_NUM_Y][FIELD_TILE_NUM_X];

    //�摜
    int tile_image[TILE_TYPE_NUM];
    int player_image[2][5];

    int image_change_time;
    int draw_player_image_index;
    int encount_rate;

    //�֐�
    void SetField();//�t�B�[���h�𐶐�
    void PlayerMovement();//�v���C���[�ړ�����
    void PlayerScroll();//�v���C���[�X�N���[������

    int EncountAnimation();//�G���J�E���g���̃A�j���[�V����

    int encount_blinking_count;//�_�ŉ�
    int encount_blinking_time_interval;//�_�Ŏ���
    bool is_encount_blinking;//�_�ł����邩�H

public:
    Field(class Player* player);
    ~Field();

    int Update(float delta_time);//�߂�l�����I
    void Draw() const;
};