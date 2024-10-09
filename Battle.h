#pragma once
#include"define.h"

class Battle
{
private:

    class Player* player;
    class EnemyManager* enemy_manager;

    float wait_time;
    int scenery_image[12];//�퓬���̌i�F�摜
    int image_transparency;//�摜�̓��ߓx
    int enemy_type;
    int enemy_image[ENEMY_TYPE_NUM];


    bool EncountAnimation();


public:

    Battle(class Player* player);
    ~Battle();

    void Initialize(int encount_enemy_rank); //������

    bool Update(float delta_time);
    void Draw() const;
};