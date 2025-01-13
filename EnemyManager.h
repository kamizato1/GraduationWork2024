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
            {"ヒレピラニア", 10, 10, 5, 5, 3},
            {"スライム", 10, 10, 5, 5, 3},
            {"ポイズンワーム", 10, 10, 5, 5, 3},
            {"ゾンビイヌ", 10, 10, 5, 5, 3},
            {"ひとくいばな", 10, 10, 5, 5, 3},
            {"やみのきし", 10, 10, 5, 5, 3},
            {"さつじんき", 10, 10, 5, 5, 3},
            {"てつのまもり", 10, 10, 5, 5, 3},
            {"シークイーン", 10, 10, 5, 5, 3},
            {"あくのそっきん", 10, 10, 5, 5, 3}
        },
        {
            {"タードアーチャー", 10, 10, 5, 5, 3},
            {"ハニーワスプ", 10, 10, 5, 5, 3},
            {"リザードロプス", 10, 10, 5, 5, 3},
            {"ゆうれい", 10, 10, 5, 5, 3},
            {"やみのへいし", 10, 10, 5, 5, 3},
            {"げんしのかいぶつ", 10, 10, 5, 5, 3},
            {"ケルベロス", 10, 10, 5, 5, 3},
            {"シャドードレイク", 10, 10, 5, 5, 3},
            {"じゃしんかん", 10, 10, 5, 5, 3},
            {"あくのこんげん", 10, 10, 5, 5, 3}
        },
        {
            {"な", 10, 10, 5, 5, 3},
            {"ゴブリン", 10, 10, 5, 5, 3},
            {"まほうつかい", 10, 10, 5, 5, 3},
            {"ね", 10, 10, 5, 5, 3},
            {"の", 10, 10, 5, 5, 3},
            {"は", 10, 10, 5, 5, 3},
            {"ひ", 10, 10, 5, 5, 3},
            {"ふ", 10, 10, 5, 5, 3},
            {"へ", 10, 10, 5, 5, 3},
            {"", 10, 10, 5, 5, 3}
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