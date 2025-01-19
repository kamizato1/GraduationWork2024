#pragma once
#include"define.h"

#define TILE_TYPE_NUM 23

class Field
{
private:

    //�N���X
    class Player* player;

    //�\���̐錾

    struct FIELD_PLAYER
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
    FIELD_PLAYER field_player;
    TILE tile[FIELD_TILE_NUM][FIELD_TILE_NUM];


    //�摜
    int tile_image[TILE_TYPE_NUM];
    int player_image[2][5];

    //�ϐ�
    float player_image_change_time;//�摜�؂�ւ�����
    int player_image_index;//�v���C���[�摜�v�f��

    int encount_rate;//

    bool update_encount_animation;//�G���J�E���g�A�j���[�V�������X�V���邩�H
    float screen_blinking_time;//�_�Ŏ���
    int screen_blinking_count;//�_�ŉ�
    
    //�t�H���g
    int retro_font_48;

    //�֐�
    void SetField();//�t�B�[���h�𐶐�

    void UpdateMovement();//�v���C���[�ړ�����
    bool UpdateScroll();//�v���C���[�X�N���[������
    bool UpdateAddScrollValue(int* player_location, int* tile_location);//�X�N���[���̒l�̉��Z

    int UpdateEncountAnimation(float delta_time);//�G���J�E���g���̃A�j���[�V����

public:
    Field(class Player* player);
    ~Field();

    int Update(float delta_time);//�߂�l�����I
    void Draw() const;
};