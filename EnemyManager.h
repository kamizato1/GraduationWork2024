#pragma once
#include"define.h"
#include <string>

#define ENEMY_MAX_RANK 10 //�G�̍ő僉���N
#define ENEMY_PER_RANK 3 //�����N������̓G�̐�

class EnemyManager
{
private:

    int enemy_image[ENEMY_PER_RANK][ENEMY_MAX_RANK];

    CHARACTER_DATA enemy_data[ENEMY_PER_RANK][ENEMY_MAX_RANK] =
    {
        {
            {"��������������", 10, 10, 5, 5, 3},
            {"�X���C��", 10, 10, 5, 5, 3},
            {"�|�C�Y�����[��", 10, 10, 5, 5, 3},
            {"���ʃ]���r", 10, 10, 5, 5, 3},
            {"�ЂƂ����΂�", 10, 10, 5, 5, 3},
            {"��݂̂���", 10, 10, 5, 5, 3},
            {"������", 10, 10, 5, 5, 3},
            {"�����̂܂���", 10, 10, 5, 5, 3},
            {"�ւт�������", 10, 10, 5, 5, 3},
            {"��", 10, 10, 5, 5, 3}
        },
        {
            {"��", 10, 10, 5, 5, 3},
            {"��", 10, 10, 5, 5, 3},
            {"��", 10, 10, 5, 5, 3},
            {"��", 10, 10, 5, 5, 3},
            {"��", 10, 10, 5, 5, 3},
            {"��", 10, 10, 5, 5, 3},
            {"��", 10, 10, 5, 5, 3},
            {"��", 10, 10, 5, 5, 3},
            {"��", 10, 10, 5, 5, 3},
            {"��", 10, 10, 5, 5, 3}
        },
        {
            {"��", 10, 10, 5, 5, 3},
            {"��", 10, 10, 5, 5, 3},
            {"��", 10, 10, 5, 5, 3},
            {"��", 10, 10, 5, 5, 3},
            {"��", 10, 10, 5, 5, 3},
            {"��", 10, 10, 5, 5, 3},
            {"��", 10, 10, 5, 5, 3},
            {"��", 10, 10, 5, 5, 3},
            {"��", 10, 10, 5, 5, 3},
            {"��", 10, 10, 5, 5, 3}
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