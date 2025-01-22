#pragma once
#include"define.h"

#define TILE_SIZE 48 //タイルの大きさ
#define DRAW_TILE_NUM 17 //表示するフィールドのタイルの数

class FieldBase
{
protected:

    class Player* player;

    //構造体宣言

    struct FIELD_PLAYER
    {
        VECTOR2_I location;//プレイヤーの座標
        VECTOR2_I location_index;//プレイヤーの移動先のタイルの配列番号
    };

    struct FIELD_TILE
    {
        VECTOR2_I location;//タイルの座標
        int type;//タイルの種類
        int enemy_rank;//タイルで出現する敵のランク
    };

    //構造体

    FIELD_PLAYER field_player;

    //画像

    int player_image[2][5];

    //変数
    float player_image_change_time;//画像切り替え時間
    int player_image_index;//プレイヤー画像要素数

    //フォント
    int retro_font_48;

    //関数
    virtual void SetField() = 0; //フィールドを生成
    void UpdatePlayerImageIndex(float delta_time);
    VECTOR2_I UpdateMovement(VECTOR2_I field_tile_location);//プレイヤー移動処理
    bool UpdateScroll(FIELD_TILE field_tile, VECTOR2_I field_player_location_index);//プレイヤースクロール処理
    bool UpdateAddScrollValue(int* field_player_location, int field_tile_location);//スクロールの値の加算

public:
    FieldBase(class Player* player);
    ~FieldBase();

    virtual int Update(float delta_time) = 0;//戻り値あるよ！
    virtual void Draw() const = 0;
};