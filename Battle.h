#pragma once
#include"define.h"
#include<string>

class Battle
{
private:

    enum class BATTLE_STATE//�o�g���̏�
    {
        ENCOUNT_ANIMATION,//�o�����̉��o
        PLAYER,//�v���C���[�^�[��
        ENEMY //�G�L�����^�[��
    };

    enum class ACTION_SELECT_STATE
    {
        ATTACK,//�U������I��
        MAGIC,//���@�I��
        ITEM,//�A�C�e���I��
        ESCAPE,//������
        NONE,
    };

    enum class ACTION_STATE
    {
        ACTION_SELECT,//�A�N�V�����I��
        TARGET_SELECT,//�^�[�Q�b�g�I��
        PLAY_EFFECT,//�G�t�F�N�g�Đ�
        DRAW_DAMAGE,//�_���[�W�\��
        NONE,
    };

    //�N���X
    class Player* player;
    class EnemyManager* enemy_manager;
    class Effect* effect;

    //��� enum class
    BATTLE_STATE battle_state;
    ACTION_SELECT_STATE action_select_state;
    ACTION_STATE action_state;

    //�ϐ�
    int action_select_index;
    int target_select_index;
    int screen_transparency_value; //��ʂ̖��邳
    int damage_value;

    float delta_time;//���ԊǗ��Ɏg��

    //�摜
    int scenery_image[12];
    int effect_image[10][10];

    //�t�H���g
    int retro_font_48;

    //�֐�
    void PlayerAction(float delta_time);
    void PlayerAttack(float delta_time);

    void DrawPlayerAction()const;
    void DrawPlayerAttack()const;

public:

    Battle(class Player* player);
    ~Battle();

    void Initialize(int encount_enemy_rank); //������

    bool Update(float delta_time);
    void Draw() const;
};