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

    enum class BATTLE_STATE//バトルの状況
    {
        ENCOUNT_ANIMATION,//出現時の演出
        PLAYER_TURN,//プレイヤーターン
        ENEMY_TURN //敵キャラターン
    };

    enum class ACTION_SELECT_STATE
    {
        ATTACK,//攻撃相手選択
        MAGIC,//魔法選択
        ITEM,//アイテム選択
        ESCAPE,//逃げる
        NONE,
    };

    enum class ACTION_STATE
    {
        ACTION_SELECT,//アクション選択
        TARGET_SELECT,//ターゲット選択
        PLAY_EFFECT,//エフェクト再生
        DRAW_DAMAGE,//ダメージ表示
        DEAD,
        NONE,
    };

    //クラス
    class Player* player;
    class EnemyBase* enemy;
    class Effect* effect;
    class EnemyManager* enemy_manager;

    //状態 enum class
    BATTLE_STATE battle_state;
    ACTION_SELECT_STATE action_select_state;
    ACTION_STATE action_state;

    //構造体
    DRAW_UI draw_ui;

    //変数
    int scenery_image_index;
    int action_select_index;
    int target_select_index;
    int screen_transparency_value; //画面の明るさ
    int damage_value;
    int font_color_value;
    float blinking_time;
    bool draw_enemy;
    int screen_amplitude_value;
    int add_screen_amplitude_value;

    float delta_time;//時間管理に使う

    //画像
    int scenery_image[12];
    int effect_image[10][10];

    //フォント
    int retro_font_48;

    //関数

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

    void Initialize(int encount_enemy_rank, int scenery_image_index); //初期化

    bool Update(float delta_time);
    void Draw() const;
};