#pragma once
#include"MapBase.h"
#include"define.h"

#define TILE_NUM 128
#define TILE_TYPE_NUM 29

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
    VECTOR2_I player_location;
    VECTOR2_I player_location_index;
    
    int bright_value;

    //関数
    void SetMap()override;//フィールドを生成
    bool UpdateEncountAnimation(float delta_time);//エンカウント時のアニメーション

public:
    WorldMap(class Player* player);
    ~WorldMap();
    void Initialize()override;

    int GetTileType()const;
    int GetEnemyRank()const;
    void SetPlayerStartLocation();

    GAME_SCENE_TYPE Update(float delta_time)override;//戻り値あるよ！

    void Draw() const override;
};