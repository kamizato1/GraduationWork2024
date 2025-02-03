#pragma once
#include"define.h"

#define TILE_SIZE 48 //�^�C���̑傫��
#define DRAW_TILE_NUM 17 //�\������t�B�[���h�̃^�C���̐�

class MapBase
{
protected:

    class Player* player;

    //�\���̐錾

    struct TILE
    {
        VECTOR2_I location;//�^�C���̍��W
        int type;//�^�C���̎��
        int enemy_rank;//�^�C���ŏo������G�̃����N
    };
 
    //�ϐ�
    float image_index_change_time;//�摜�؂�ւ�����
    int image_index;//�摜�v�f��
    int add_image_index;

    //�t�H���g
    int retro_font_48;

    //�֐�
    virtual void SetMap() = 0; //�t�B�[���h�𐶐�
    void UpdateImageIndex(float delta_time);

public:

    MapBase(class Player* player);
    ~MapBase();

    virtual void Initialize() = 0;

    virtual GAME_SCENE_TYPE Update(float delta_time) = 0;//�߂�l�����I
    virtual void Draw() const = 0;
};