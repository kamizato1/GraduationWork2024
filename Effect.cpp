#include"Effect.h"
#include"define.h"
#include"DxLib.h"

Effect::Effect(int* image, int image_element, float image_change_time)
{
	for (int i = 0; i < 10; i++)
	{
		if (image_element > i)this->image[i] = *(image + i);
		else this->image[i] = NULL;
	}

	this->image_change_time = image_change_time;
	delta_time = 0.0f;
	draw_image_element = 0;

	OutputDebugString("Effectコンストラクタ呼ばれました。\n");
}

Effect::~Effect()
{
	OutputDebugString("Effectデストラクタ呼ばれました。\n");
}

bool Effect::Update(float delta_time)
{
	if (draw_image_element == -1)return true;

	if ((this->delta_time += delta_time) > image_change_time)
	{
		this->delta_time = 0.0f;

		draw_image_element++;

		if ((image[draw_image_element] == NULL) || (draw_image_element == 10))draw_image_element = -1;
	}
	return false;
}

void Effect::Draw() const
{
	if(draw_image_element != -1)DrawRotaGraph(HALF_SCREEN_SIZE, 300, 3, 0, image[draw_image_element], TRUE);
}


