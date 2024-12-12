#pragma once
#include"define.h"
#include <string>

#define ENEMY_MAX_RANK 10 //敵の最大ランク
#define ENEMY_PER_RANK 3 //ランク当たりの敵の数

class EnemyManager
{
private:

    int enemy_image[ENEMY_PER_RANK][ENEMY_MAX_RANK];

    CHARACTER_DATA enemy_data[ENEMY_PER_RANK][ENEMY_MAX_RANK] =
    {
        {
            {"くさったさかな", 10, 10, 5, 5, 3},
            {"スライム", 10, 10, 5, 5, 3},
            {"ポイズンワーム", 10, 10, 5, 5, 3},
            {"いぬゾンビ", 10, 10, 5, 5, 3},
            {"ひとくいばな", 10, 10, 5, 5, 3},
            {"やみのきし", 10, 10, 5, 5, 3},
            {"さつじんき", 10, 10, 5, 5, 3},
            {"あくのまもり", 10, 10, 5, 5, 3},
            {"へびおうじょ", 10, 10, 5, 5, 3},
            {"こ", 10, 10, 5, 5, 3}
        },
        {
            {"さ", 10, 10, 5, 5, 3},
            {"し", 10, 10, 5, 5, 3},
            {"す", 10, 10, 5, 5, 3},
            {"せ", 10, 10, 5, 5, 3},
            {"そ", 10, 10, 5, 5, 3},
            {"た", 10, 10, 5, 5, 3},
            {"ち", 10, 10, 5, 5, 3},
            {"つ", 10, 10, 5, 5, 3},
            {"て", 10, 10, 5, 5, 3},
            {"と", 10, 10, 5, 5, 3}
        },
        {
            {"な", 10, 10, 5, 5, 3},
            {"に", 10, 10, 5, 5, 3},
            {"ぬ", 10, 10, 5, 5, 3},
            {"ね", 10, 10, 5, 5, 3},
            {"の", 10, 10, 5, 5, 3},
            {"は", 10, 10, 5, 5, 3},
            {"ひ", 10, 10, 5, 5, 3},
            {"ふ", 10, 10, 5, 5, 3},
            {"へ", 10, 10, 5, 5, 3},
            {"ほ", 10, 10, 5, 5, 3}
        }
    };

    class EnemyBase* enemy;

public:

    EnemyManager();
    ~EnemyManager();

    void Initialize(int encount_enemy_rank);

    int EnemyNum()const;
    const char* GetEnemyName(int enemy_num)const;

    int HitAttack(int enemy_num, int attack_power);

    bool Update(float delta_time);
    void Draw() const;
};