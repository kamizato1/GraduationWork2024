#pragma once
#include"define.h"
#include <string>

#define ENEMY_MAX_RANK 10 //�G�̍ő僉���N
#define ENEMY_PER_RANK 3 //�����N������̓G�̐�

class EnemyManager
{
private:

    int enemy_image[ENEMY_PER_RANK][ENEMY_MAX_RANK];

    struct ENEMY_DATA
    {
        std::string name;
        int hp;
        int mp;
        int attack_power;
        int defense_power;
        int speed;
    };

    ENEMY_DATA enemy_data[ENEMY_PER_RANK][ENEMY_MAX_RANK] =
    {
        {
            {"�ӂ͂�����", 10, 10, 5, 5, 3},
            {"�X���C��", 10, 10, 5, 5, 3},
            {"�|�C�Y�����[��", 10, 10, 5, 5, 3},
            {"���ʃ]���r", 10, 10, 5, 5, 3},
            {"�ЂƂ����΂�", 10, 10, 5, 5, 3},
            {"��݂̋R�m", 10, 10, 5, 5, 3},
            {"������S", 10, 10, 5, 5, 3},
            {"�����̂܂���", 10, 10, 5, 5, 3},
            {"�ւтЂ�", 10, 10, 5, 5, 3},
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

    std::string Initialize(int encount_enemy_rank);

    bool Update(float delta_time);
    void Draw() const;
};