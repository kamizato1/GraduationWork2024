#pragma once
#include"define.h"

#define TILE_TYPE_NUM 23

class Field
{
private:

    char i = 0;

    class Player* player;

    struct PLAYER
    {
        I_VECTOR2 position;//プレイヤーの座標
        I_VECTOR2 target_tile_array;//プレイヤーの移動先のタイルの配列番号
        int speed;
    };

    PLAYER field_player;

    struct TILE
    {
        I_VECTOR2 position;//タイルの座標
        int type;//タイルの種類
        int enemy_rank;//タイルで出現する敵のランク
    };

    TILE tile[FIELD_TILE_NUM_Y][FIELD_TILE_NUM_X];

    //画像
    int tile_image[TILE_TYPE_NUM];
    int player_image[2][5];

    int image_change_time;
    int draw_player_image_index;
    int encount_rate;

    //関数
    void SetField();//フィールドを生成
    void PlayerMovement();//プレイヤー移動処理
    void PlayerScroll();//プレイヤースクロール処理

    int EncountAnimation();//エンカウント時のアニメーション

    int encount_blinking_count;//点滅回数
    int encount_blinking_time_interval;//点滅時間
    bool is_encount_blinking;//点滅させるか？

public:
    Field(class Player* player);
    ~Field();

    int Update(float delta_time);//戻り値あるよ！
    void Draw() const;
};