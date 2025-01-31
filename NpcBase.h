#pragma once
#include"define.h"

class NpcBase
{
private:
    char message[256];//メッセージ1桁

protected:

    VECTOR2_I location;//NPCーの座標
    VECTOR2_I location_index;//NPCの移動先のタイルの配列番号 

    int image[16];
    int image_direction_index;
    float direction_change_time;

public:

    NpcBase(VECTOR2_I location, VECTOR2_I location_index, int* image, const char* message);
    ~NpcBase();

    bool Update(float delta_time);
    void Draw(VECTOR2_I add_location, int image_index)const;

    virtual VECTOR2_I UpdateMovement(VECTOR2_I tile_location);

    bool UpdateScroll(int tile_type, int collide_tile_type, VECTOR2_I location_index, VECTOR2_I tile_location);
    bool UpdateAddScrollValue(VECTOR2_I tile_location);

    VECTOR2_I GetLocationIndex()const;
    VECTOR2_I GetLocation()const;
    void SetLocationIndex(VECTOR2_I location_index);
    void SetLocation(VECTOR2_I location);

    const char* GetNpcMessage()const;
};