#pragma once
#include"MapBase.h"

#define TILE_NUM 128
#define TILE_TYPE_NUM 19

class WorldMap : public MapBase
{
private:

    TILE tile[TILE_NUM][TILE_NUM];

    //画像
    int tile_image[TILE_TYPE_NUM];

    //変数
    int encount_rate;
    bool update_encount_animation;//エンカウントアニメーションを更新するか？
    float screen_blinking_time;//点滅時間
    int screen_blinking_count;//点滅回数
    
    //関数
    void SetMap()override;//フィールドを生成
    int UpdateEncountAnimation(float delta_time);//エンカウント時のアニメーション

public:
    WorldMap(class Player* player);
    ~WorldMap();

    int Update(float delta_time)override;//戻り値あるよ！
    void Draw() const override;
};






















//#pragma once
//#include"define.h"
//
//#define TILE_TYPE_NUM 23
//
//class WorldMap
//{
//private:
//
//    //クラス
//    class Player* player;
//
//    //構造体宣言
//
//    struct PLAYER
//    {
//        VECTOR2_I location;//プレイヤーの座標
//        VECTOR2_I location_index;//プレイヤーの移動先のタイルの配列番号
//    };
//
//    struct TILE
//    {
//        VECTOR2_I location;//タイルの座標
//        int type;//タイルの種類
//        int enemy_rank;//タイルで出現する敵のランク
//    };
//
//    //構造体
//    PLAYER map_player;
//    TILE tile[MAP_TILE_NUM][MAP_TILE_NUM];
//
//
//    //画像
//    int tile_image[TILE_TYPE_NUM];
//    int player_image[2][5];
//
//    //変数
//    float player_image_change_time;//画像切り替え時間
//    int player_image_index;//プレイヤー画像要素数
//
//    int encount_rate;//
//
//    bool update_encount_animation;//エンカウントアニメーションを更新するか？
//    float screen_blinking_time;//点滅時間
//    int screen_blinking_count;//点滅回数
//
//    //フォント
//    int retro_font_48;
//
//    //関数
//    void SetMap();//フィールドを生成
//
//    void UpdateMovement();//プレイヤー移動処理
//    bool UpdateScroll();//プレイヤースクロール処理
//    bool UpdateAddScrollValue(int* player_location, int* tile_location);//スクロールの値の加算
//
//    int UpdateEncountAnimation(float delta_time);//エンカウント時のアニメーション
//
//public:
//    WorldMap(class Player* player);
//    ~WorldMap();
//
//    int Update(float delta_time);//戻り値あるよ！
//    void Draw() const;
//};