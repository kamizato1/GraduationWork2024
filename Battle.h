#pragma once
#include"define.h"
#include<string>

class Battle
{
private:

    enum class BATTLE_STATE
    {
        DRAW_ENEMY_NAME,//�퓬�J�n���̓G�̖��O�\��
        PLAYER_ACTION_SELECT,//�v���C���[�̍s���I��
        PLAYER_MAGIC_SELECT,//�v���C���[�̖��@�I��
        PLAYER_ITEM_SELECT,//�v���C���[�̃A�C�e���I��
        ENEMY_ACTION //�G�L�����̍s��
    };

    BATTLE_STATE battle_state;//�o�g���̏�

    class Player* player;
    class EnemyManager* enemy_manager;
    class Message* message;

    std::string enemy_name;

    float wait_time;
    int scenery_image[12];//�퓬���̌i�F�摜
    int image_transparency;//�摜�̓��ߓx
    
    bool EncountAnimation();

public:

    Battle(class Player* player);
    ~Battle();

    void Initialize(int encount_enemy_rank); //������

    bool Update(float delta_time);
    void Draw() const;
};