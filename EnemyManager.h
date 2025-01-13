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
            {"�q���s���j�A", 10, 10, 5, 5, 3},
            {"�X���C��", 10, 10, 5, 5, 3},
            {"�|�C�Y�����[��", 10, 10, 5, 5, 3},
            {"�]���r�C�k", 10, 10, 5, 5, 3},
            {"�ЂƂ����΂�", 10, 10, 5, 5, 3},
            {"��݂̂���", 10, 10, 5, 5, 3},
            {"������", 10, 10, 5, 5, 3},
            {"�Ă̂܂���", 10, 10, 5, 5, 3},
            {"�V�[�N�C�[��", 10, 10, 5, 5, 3},
            {"�����̂�������", 10, 10, 5, 5, 3}
        },
        {
            {"�^�[�h�A�[�`���[", 10, 10, 5, 5, 3},
            {"�n�j�[���X�v", 10, 10, 5, 5, 3},
            {"���U�[�h���v�X", 10, 10, 5, 5, 3},
            {"�䂤�ꂢ", 10, 10, 5, 5, 3},
            {"��݂̂ւ���", 10, 10, 5, 5, 3},
            {"���񂵂̂����Ԃ�", 10, 10, 5, 5, 3},
            {"�P���x���X", 10, 10, 5, 5, 3},
            {"�V���h�[�h���C�N", 10, 10, 5, 5, 3},
            {"���Ⴕ�񂩂�", 10, 10, 5, 5, 3},
            {"�����̂��񂰂�", 10, 10, 5, 5, 3}
        },
        {
            {"��", 10, 10, 5, 5, 3},
            {"�S�u����", 10, 10, 5, 5, 3},
            {"�܂ق�����", 10, 10, 5, 5, 3},
            {"��", 10, 10, 5, 5, 3},
            {"��", 10, 10, 5, 5, 3},
            {"��", 10, 10, 5, 5, 3},
            {"��", 10, 10, 5, 5, 3},
            {"��", 10, 10, 5, 5, 3},
            {"��", 10, 10, 5, 5, 3},
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