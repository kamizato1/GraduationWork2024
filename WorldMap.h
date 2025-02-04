#pragma once
#include"MapBase.h"
#include"define.h"

#define TILE_NUM 128
#define TILE_TYPE_NUM 29

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
    VECTOR2_I player_location;
    VECTOR2_I player_location_index;
    
    int bright_value;

    //�֐�
    void SetMap()override;//�t�B�[���h�𐶐�
    bool UpdateEncountAnimation(float delta_time);//�G���J�E���g���̃A�j���[�V����

public:
    WorldMap(class Player* player);
    ~WorldMap();
    void Initialize()override;

    int GetTileType()const;
    int GetEnemyRank()const;
    void SetPlayerStartLocation();

    GAME_SCENE_TYPE Update(float delta_time)override;//�߂�l�����I

    void Draw() const override;
};