#pragma once
#include"define.h"
#include"PlayerManager.h"
#include"EnemyManager.h"
#include"AttackManager.h"
#include"EventManager.h"

class BattleField
{
private:
    class PlayerManager* player_manager;
    class EnemyManager* enemy_manager;
    class AttackManager* attack_manager;
    class EventManager* event_manager;

    int block_image[BLOCK_TYPE_NUM];//�u���b�N�摜
    int back_ground_image;//�w�i�摜

    void SetBattleField();//�o�g���t�B�[���h�𐶐�

public:
    BattleField(I_VECTOR2 field_array_size);
    ~BattleField();

    bool Update(float delta_time);//�߂�l�����I
    void Draw() const;
};