#pragma once
#include"define.h"
#include<string>

class Battle
{
private:

    enum class BATTLE_STATE//バトルの状況
    {
        ENCOUNT_ANIMATION,//出現時の演出
        PLAYER,//プレイヤーターン
        ENEMY //敵キャラターン
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
        NONE,
    };

    //クラス
    class Player* player;
    class EnemyManager* enemy_manager;
    class Effect* effect;

    //状態 enum class
    BATTLE_STATE battle_state;
    ACTION_SELECT_STATE action_select_state;
    ACTION_STATE action_state;

    //変数
    int action_select_index;
    int target_select_index;
    int screen_transparency_value; //画面の明るさ
    int damage_value;

    float delta_time;//時間管理に使う

    //画像
    int scenery_image[12];
    int effect_image[10][10];

    //フォント
    int retro_font_48;

    //関数
    void PlayerAction(float delta_time);
    void PlayerAttack(float delta_time);

    void DrawPlayerAction()const;
    void DrawPlayerAttack()const;

public:

    Battle(class Player* player);
    ~Battle();

    void Initialize(int encount_enemy_rank); //初期化

    bool Update(float delta_time);
    void Draw() const;
};