#pragma once
#include"define.h"

#define TILE_SIZE 48 //タイルの大きさ
#define DRAW_TILE_NUM 17 //表示するフィールドのタイルの数

class MapBase
{
protected:

    class Player* player;

    //構造体宣言

    struct TILE
    {
        VECTOR2_I location;//タイルの座標
        int type;//タイルの種類
        int enemy_rank;//タイルで出現する敵のランク
    };
 
    //変数
    float image_index_change_time;//画像切り替え時間
    int image_index;//画像要素数
    int add_image_index;

    //フォント
    int retro_font_48;

    //関数
    virtual void SetMap() = 0; //フィールドを生成
    void UpdateImageIndex(float delta_time);

public:

    MapBase(class Player* player);
    ~MapBase();

    virtual void Initialize() = 0;

    virtual GAME_SCENE_TYPE Update(float delta_time) = 0;//戻り値あるよ！
    virtual void Draw() const = 0;
};