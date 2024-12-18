#pragma once
#include <vector>

class Effect
{
private:
    int image[10];
    float image_change_time;//画像切り替え時間
    float delta_time;//経過時間
    int draw_image_element;//画像の表示要素数

public:

    Effect(int *image, int image_element, float image_change_time);
    ~Effect();

    bool Update(float delta_time);
    void Draw()const;
};