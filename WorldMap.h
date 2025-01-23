#pragma once
#include"MapBase.h"

#define TILE_NUM 128
#define TILE_TYPE_NUM 19

class WorldMap : public MapBase
{
private:

    TILE tile[TILE_NUM][TILE_NUM];

    //�摜
    int tile_image[TILE_TYPE_NUM];

    //�ϐ�
    int encount_rate;
    bool update_encount_animation;//�G���J�E���g�A�j���[�V�������X�V���邩�H
    float screen_blinking_time;//�_�Ŏ���
    int screen_blinking_count;//�_�ŉ�
    
    //�֐�
    void SetMap()override;//�t�B�[���h�𐶐�
    int UpdateEncountAnimation(float delta_time);//�G���J�E���g���̃A�j���[�V����

public:
    WorldMap(class Player* player);
    ~WorldMap();

    int Update(float delta_time)override;//�߂�l�����I
    void Draw() const override;
};






















//#pragma once
//#include"define.h"
//
//#define TILE_TYPE_NUM 23
//
//class WorldMap
//{
//private:
//
//    //�N���X
//    class Player* player;
//
//    //�\���̐錾
//
//    struct PLAYER
//    {
//        VECTOR2_I location;//�v���C���[�̍��W
//        VECTOR2_I location_index;//�v���C���[�̈ړ���̃^�C���̔z��ԍ�
//    };
//
//    struct TILE
//    {
//        VECTOR2_I location;//�^�C���̍��W
//        int type;//�^�C���̎��
//        int enemy_rank;//�^�C���ŏo������G�̃����N
//    };
//
//    //�\����
//    PLAYER map_player;
//    TILE tile[MAP_TILE_NUM][MAP_TILE_NUM];
//
//
//    //�摜
//    int tile_image[TILE_TYPE_NUM];
//    int player_image[2][5];
//
//    //�ϐ�
//    float player_image_change_time;//�摜�؂�ւ�����
//    int player_image_index;//�v���C���[�摜�v�f��
//
//    int encount_rate;//
//
//    bool update_encount_animation;//�G���J�E���g�A�j���[�V�������X�V���邩�H
//    float screen_blinking_time;//�_�Ŏ���
//    int screen_blinking_count;//�_�ŉ�
//
//    //�t�H���g
//    int retro_font_48;
//
//    //�֐�
//    void SetMap();//�t�B�[���h�𐶐�
//
//    void UpdateMovement();//�v���C���[�ړ�����
//    bool UpdateScroll();//�v���C���[�X�N���[������
//    bool UpdateAddScrollValue(int* player_location, int* tile_location);//�X�N���[���̒l�̉��Z
//
//    int UpdateEncountAnimation(float delta_time);//�G���J�E���g���̃A�j���[�V����
//
//public:
//    WorldMap(class Player* player);
//    ~WorldMap();
//
//    int Update(float delta_time);//�߂�l�����I
//    void Draw() const;
//};