#pragma once
#include"EnemyBase.h"

class Bird : public EnemyBase
{
private:

    DATA target_location;//�U��������W
    DATA begin_attack_location;//�U���J�n���W
    float attack_speed; //�U�����x

public:

    Bird(DATA location, int enemy_image[ENEMY_STATE::END][5], class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager); //�R���X�g���N�^
    ~Bird(); //�f�X�g���N�^

    void Update(float delta_time)override; //�X�V����
    void Draw(DATA draw_location) const override; //�`��֌W
};

