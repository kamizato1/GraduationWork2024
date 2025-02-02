#include"DxLib.h"
#include"NameInput.h"
#include"Key.h"

NameInput::NameInput()
{
	//�t�H���g�̓ǂݍ���
	retro_font_48 = LoadFontDataToHandle("data/font/DragonQuestFont48.dft", 0);
	cursor_location_index = { 0, 0 };
	moji_count = 0;

	OutputDebugString("NameInput�R���X�g���N�^�Ă΂�܂����B\n");
}

NameInput::~NameInput()
{
	DeleteFontToHandle(retro_font_48);
	OutputDebugString("NameInput�f�X�g���N�^�Ă΂�܂����B\n");
}

bool NameInput::Update(float delta_time)
{

	if (Key::KeyDown(KEY_TYPE::UP))
	{
		if (--cursor_location_index.y < 0)cursor_location_index.y = 4;
	}
	if (Key::KeyDown(KEY_TYPE::DOWN))
	{
		if (++cursor_location_index.y > 4)cursor_location_index.y = 0;
	}
	if (Key::KeyDown(KEY_TYPE::LEFT))
	{
		if (--cursor_location_index.x < 0)cursor_location_index.x = 10;
	}
	if (Key::KeyDown(KEY_TYPE::RIGHT))
	{
		if (++cursor_location_index.x > 10)cursor_location_index.x = 0;
	}
	if (Key::KeyDown(KEY_TYPE::A))
	{
		if ((cursor_location_index.x == 10) && (cursor_location_index.y == 0))
		{
			if (moji_count != 0)
			{
				char moji[4] = {'\0'};
				memcpy(moji, name + (moji_count - 1) * 2, 2);
				if (strcmp(moji, "��") == 0)memcpy(name + ((moji_count - 1) * 2), "��", 2);
				else if (strcmp(moji, "��") == 0)memcpy(name + ((moji_count - 1) * 2), "��", 2);
				else if (strcmp(moji, "��") == 0)memcpy(name + ((moji_count - 1) * 2), "��", 2);
				else if (strcmp(moji, "��") == 0)memcpy(name + ((moji_count - 1) * 2), "��", 2);
				else if (strcmp(moji, "��") == 0)memcpy(name + ((moji_count - 1) * 2), "��", 2);
				else if (strcmp(moji, "��") == 0)memcpy(name + ((moji_count - 1) * 2), "��", 2);
				else if (strcmp(moji, "��") == 0)memcpy(name + ((moji_count - 1) * 2), "��", 2);
				else if (strcmp(moji, "��") == 0)memcpy(name + ((moji_count - 1) * 2), "��", 2);
				else if (strcmp(moji, "��") == 0)memcpy(name + ((moji_count - 1) * 2), "��", 2);
				else if (strcmp(moji, "��") == 0)memcpy(name + ((moji_count - 1) * 2), "��", 2);
				else if (strcmp(moji, "��") == 0)memcpy(name + ((moji_count - 1) * 2), "��", 2);
				else if (strcmp(moji, "��") == 0)memcpy(name + ((moji_count - 1) * 2), "��", 2);
				else if (strcmp(moji, "��") == 0)memcpy(name + ((moji_count - 1) * 2), "��", 2);
				else if (strcmp(moji, "��") == 0)memcpy(name + ((moji_count - 1) * 2), "��", 2);
				else if (strcmp(moji, "��") == 0)memcpy(name + ((moji_count - 1) * 2), "��", 2);
				else if (strcmp(moji, "��") == 0)memcpy(name + ((moji_count - 1) * 2), "��", 2);
				else if (strcmp(moji, "��") == 0)memcpy(name + ((moji_count - 1) * 2), "��", 2);
				else if (strcmp(moji, "��") == 0)memcpy(name + ((moji_count - 1) * 2), "��", 2);
				else if (strcmp(moji, "��") == 0)memcpy(name + ((moji_count - 1) * 2), "��", 2);
				else if (strcmp(moji, "��") == 0)memcpy(name + ((moji_count - 1) * 2), "��", 2);
			}
		}
		else if ((cursor_location_index.x == 10) && (cursor_location_index.y == 1))
		{
			if (moji_count != 0)
			{
				char moji[4] = { '\0' };
				memcpy(moji, name + (moji_count - 1) * 2, 2);
				if (strcmp(moji, "��") == 0)memcpy(name + ((moji_count - 1) * 2), "��", 2);
				else if (strcmp(moji, "��") == 0)memcpy(name + ((moji_count - 1) * 2), "��", 2);
				else if (strcmp(moji, "��") == 0)memcpy(name + ((moji_count - 1) * 2), "��", 2);
				else if (strcmp(moji, "��") == 0)memcpy(name + ((moji_count - 1) * 2), "��", 2);
				else if (strcmp(moji, "��") == 0)memcpy(name + ((moji_count - 1) * 2), "��", 2);
			}
		}
		else if ((cursor_location_index.x == 10) && (cursor_location_index.y == 3))
		{
			if (moji_count != 0)
			{
				name[(moji_count * 2) - 1] = '\0';
				name[(moji_count * 2) - 2] = '\0';
				moji_count--;
			}
		}
		else if ((cursor_location_index.x == 10) && (cursor_location_index.y == 4))
		{
			if (moji_count != 0)return true;
		}
		else if (moji_count < 4)
		{
			std::memcpy(name + (moji_count * 2), moji[cursor_location_index.y][cursor_location_index.x], 2);
			moji_count++;
		}
	}

	return false;
}

const char* NameInput::GetName()const
{
	return name;
}

void NameInput::Draw()const
{
	DrawBox(250, 160, 450, 215, 0xffffff, TRUE);
	DrawBox(255, 165, 445, 210, 0x000000, TRUE);

	DrawBox(20, 220, 700, 570, 0xffffff, TRUE);
	DrawBox(25, 225, 695, 565, 0x000000, TRUE);
	DrawBox(20, 280, 700, 283, 0xffffff, TRUE);

	DrawStringToHandle(210, 220,"�Ȃ܂�������Ă�������", 0xffffff, retro_font_48);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if((cursor_location_index.x == j) && (cursor_location_index.y == i))DrawFormatStringToHandle(45 + (55 * j), 280 + (55 * i), 0xff0000, retro_font_48, "%s", moji[i][j]);
			else DrawFormatStringToHandle(45 + (55 * j), 280 + (55 * i), 0xffffff, retro_font_48, "%s", moji[i][j]);
		}
	}

	
	DrawFormatStringToHandle(305, 155,0xffffff, retro_font_48, "%s", name);
}