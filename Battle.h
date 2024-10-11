#pragma once
#include"define.h"
#include<string>

class Battle
{
private:

    enum class BATTLE_STATE
    {
        DRAW_ENEMY_NAME,//戦闘開始時の敵の名前表示
        PLAYER_ACTION_SELECT,//プレイヤーの行動選択
        PLAYER_MAGIC_SELECT,//プレイヤーの魔法選択
        PLAYER_ITEM_SELECT,//プレイヤーのアイテム選択
        ENEMY_ACTION //敵キャラの行動
    };

    BATTLE_STATE battle_state;//バトルの状況

    class Player* player;
    class EnemyManager* enemy_manager;
    class Message* message;

    std::string enemy_name;

    float wait_time;
    int scenery_image[12];//戦闘時の景色画像
    int image_transparency;//画像の透過度
    
    bool EncountAnimation();

public:

    Battle(class Player* player);
    ~Battle();

    void Initialize(int encount_enemy_rank); //初期化

    bool Update(float delta_time);
    void Draw() const;
};