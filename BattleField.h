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

    int block_image[BLOCK_TYPE_NUM];//ブロック画像
    int back_ground_image;//背景画像

    void SetBattleField();//バトルフィールドを生成

public:
    BattleField(I_VECTOR2 field_array_size);
    ~BattleField();

    bool Update(float delta_time);//戻り値あるよ！
    void Draw() const;
};