#pragma once
#include <vector>

class Effect
{
private:
    int image[10];
    float image_change_time;//‰æ‘œØ‚è‘Ö‚¦ŠÔ
    float delta_time;//Œo‰ßŠÔ
    int draw_image_element;//‰æ‘œ‚Ì•\¦—v‘f”

public:

    Effect(int *image, int image_element, float image_change_time);
    ~Effect();

    bool Update(float delta_time);
    void Draw()const;
};