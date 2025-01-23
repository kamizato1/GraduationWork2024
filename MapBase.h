#pragma once
#include"define.h"

#define TILE_SIZE 48 //タイルの大きさ
#define DRAW_TILE_NUM 17 //表示するフィールドのタイルの数

class MapBase
{
protected:

    class Player* player;

    //構造体宣言

    struct PLAYER
    {
        VECTOR2_I location;//プレイヤーの座標
        VECTOR2_I location_index;//プレイヤーの移動先のタイルの配列番号
    };

    struct TILE
    {
        VECTOR2_I location;//タイルの座標
        int type;//タイルの種類
        int enemy_rank;//タイルで出現する敵のランク
    };

    //構造体

    PLAYER map_player;

    //画像

    int player_image[2][5];

    //変数
    float player_image_change_time;//画像切り替え時間
    int player_image_index;//プレイヤー画像要素数

    //フォント
    int retro_font_48;

    //関数
    virtual void SetMap() = 0; //フィールドを生成
    void UpdatePlayerImageIndex(float delta_time);
    VECTOR2_I UpdateMovement(VECTOR2_I map_tile_location);//プレイヤー移動処理
    bool UpdateScroll(TILE map_tile, VECTOR2_I map_player_location_index);//プレイヤースクロール処理
    bool UpdateAddScrollValue(int* map_player_location, int map_tile_location);//スクロールの値の加算
    //int Base36ToDecimal();

public:
    MapBase(class Player* player);
    ~MapBase();

    virtual int Update(float delta_time) = 0;//戻り値あるよ！
    virtual void Draw() const = 0;
};