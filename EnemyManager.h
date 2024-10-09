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
            {"�X���C��", 10, 10, 5, 5, 3},
            {"�n�l����", 10, 10, 5, 5, 3},
            {"�O������", 10, 10, 5, 5, 3},
            {"�����肢��", 10, 10, 5, 5, 3},
            {"�ЂƂ����΂�", 10, 10, 5, 5, 3},
            {"���܂ւ���", 10, 10, 5, 5, 3},
            {"�_�C�i�b�N�X", 10, 10, 5, 5, 3},
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

    bool Update(float delta_time);
    void Draw() const;
};