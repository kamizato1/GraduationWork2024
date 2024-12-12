#pragma once
#include <vector>

class Effect
{
private:
    int image[10];
    float image_change_time;//�摜�؂�ւ�����
    float delta_time;//�o�ߎ���
    int draw_image_element;//�摜�̕\���v�f��

public:

    Effect(int *image, int image_element, float image_change_time);
    ~Effect();

    bool Update(float delta_time);
    void Draw()const;
};