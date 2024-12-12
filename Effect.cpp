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

	OutputDebugString("Effect�R���X�g���N�^�Ă΂�܂����B\n");
}

Effect::~Effect()
{
	OutputDebugString("Effect�f�X�g���N�^�Ă΂�܂����B\n");
}

bool Effect::Update(float delta_time)
{
	if ((this->delta_time += delta_time) > image_change_time)
	{
		this->delta_time = 0.0f;
		if (image[++draw_image_element] == NULL)return true;
	}
	return false;
}

void Effect::Draw() const
{
	DrawRotaGraph(HALF_SCREEN_SIZE, 300, 3, 0, image[draw_image_element], TRUE);
}

