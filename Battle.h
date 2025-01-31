#pragma once
#include"define.h"
#include<string>

class Battle
{
private:

    struct DRAW_UI //message, player, enemy, action
    {
        bool message_box;
        bool player_name_box;
        bool enemy_name_box;
        bool action_select_box;
    };

    enum class BATTLE_STATE//�o�g���̏�
    {
        ENCOUNT_ANIMATION,//�o�����̉��o
        PLAYER_TURN,//�v���C���[�^�[��
        ENEMY_TURN //�G�L�����^�[��
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
        DEAD,
        NONE,
    };

    //�N���X
    class Player* player;
    class EnemyBase* enemy;
    class Effect* effect;
    class EnemyManager* enemy_manager;

    //��� enum class
    BATTLE_STATE battle_state;
    ACTION_SELECT_STATE action_select_state;
    ACTION_STATE action_state;

    //�\����
    DRAW_UI draw_ui;

    //�ϐ�
    int scenery_image_index;
    int action_select_index;
    int target_select_index;
    int screen_transparency_value; //��ʂ̖��邳
    int damage_value;
    int font_color_value;
    float blinking_time;
    bool draw_enemy;
    int screen_amplitude_value;
    int add_screen_amplitude_value;

    float delta_time;//���ԊǗ��Ɏg��

    //�摜
    int scenery_image[12];
    int effect_image[10][10];

    //�t�H���g
    int retro_font_48;

    //�֐�

    void UpdateEncountAnimation(float delta_time);

    bool UpdatePlayerAction(float delta_time);
    bool UpdatePlayerAttack(float delta_time);
    bool UpdatePlayerMagic(float delta_time);

    void UpdateEnemyAction(float delta_time);
    void UpdateEnemyAttack(float delta_time);

    bool UpdateBlinking(float delta_time);
    void UpdateScreenAmplitude();

    void DrawUi()const;

    void DrawMessageBox()const;
    void DrawPlayerNameBox()const;
    void DrawEnemyNameBox()const;

    void DrawActionSelectBox()const;
    
public:

    Battle(class Player* player);
    ~Battle();

    void Initialize(int encount_enemy_rank, int scenery_image_index); //������

    bool Update(float delta_time);
    void Draw() const;
};