#include"DxLib.h"
#include"NameInput.h"
#include"Key.h"

NameInput::NameInput()
{
	//フォントの読み込み
	retro_font_48 = LoadFontDataToHandle("data/font/DragonQuestFont48.dft", 0);
	cursor_location_index = { 0, 0 };
	moji_count = 0;

	OutputDebugString("NameInputコンストラクタ呼ばれました。\n");
}

NameInput::~NameInput()
{
	DeleteFontToHandle(retro_font_48);
	OutputDebugString("NameInputデストラクタ呼ばれました。\n");
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
				if (strcmp(moji, "か") == 0)memcpy(name + ((moji_count - 1) * 2), "が", 2);
				else if (strcmp(moji, "き") == 0)memcpy(name + ((moji_count - 1) * 2), "ぎ", 2);
				else if (strcmp(moji, "く") == 0)memcpy(name + ((moji_count - 1) * 2), "ぐ", 2);
				else if (strcmp(moji, "け") == 0)memcpy(name + ((moji_count - 1) * 2), "げ", 2);
				else if (strcmp(moji, "こ") == 0)memcpy(name + ((moji_count - 1) * 2), "ご", 2);
				else if (strcmp(moji, "さ") == 0)memcpy(name + ((moji_count - 1) * 2), "ざ", 2);
				else if (strcmp(moji, "し") == 0)memcpy(name + ((moji_count - 1) * 2), "じ", 2);
				else if (strcmp(moji, "す") == 0)memcpy(name + ((moji_count - 1) * 2), "ず", 2);
				else if (strcmp(moji, "せ") == 0)memcpy(name + ((moji_count - 1) * 2), "ぜ", 2);
				else if (strcmp(moji, "そ") == 0)memcpy(name + ((moji_count - 1) * 2), "ぞ", 2);
				else if (strcmp(moji, "た") == 0)memcpy(name + ((moji_count - 1) * 2), "だ", 2);
				else if (strcmp(moji, "ち") == 0)memcpy(name + ((moji_count - 1) * 2), "ぢ", 2);
				else if (strcmp(moji, "つ") == 0)memcpy(name + ((moji_count - 1) * 2), "づ", 2);
				else if (strcmp(moji, "て") == 0)memcpy(name + ((moji_count - 1) * 2), "で", 2);
				else if (strcmp(moji, "と") == 0)memcpy(name + ((moji_count - 1) * 2), "ど", 2);
				else if (strcmp(moji, "は") == 0)memcpy(name + ((moji_count - 1) * 2), "ば", 2);
				else if (strcmp(moji, "ひ") == 0)memcpy(name + ((moji_count - 1) * 2), "び", 2);
				else if (strcmp(moji, "ふ") == 0)memcpy(name + ((moji_count - 1) * 2), "ぶ", 2);
				else if (strcmp(moji, "へ") == 0)memcpy(name + ((moji_count - 1) * 2), "べ", 2);
				else if (strcmp(moji, "ほ") == 0)memcpy(name + ((moji_count - 1) * 2), "ぼ", 2);
			}
		}
		else if ((cursor_location_index.x == 10) && (cursor_location_index.y == 1))
		{
			if (moji_count != 0)
			{
				char moji[4] = { '\0' };
				memcpy(moji, name + (moji_count - 1) * 2, 2);
				if (strcmp(moji, "は") == 0)memcpy(name + ((moji_count - 1) * 2), "ぱ", 2);
				else if (strcmp(moji, "ひ") == 0)memcpy(name + ((moji_count - 1) * 2), "ぴ", 2);
				else if (strcmp(moji, "ふ") == 0)memcpy(name + ((moji_count - 1) * 2), "ぷ", 2);
				else if (strcmp(moji, "へ") == 0)memcpy(name + ((moji_count - 1) * 2), "ぺ", 2);
				else if (strcmp(moji, "ほ") == 0)memcpy(name + ((moji_count - 1) * 2), "ぽ", 2);
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

	DrawStringToHandle(210, 220,"なまえをいれてください", 0xffffff, retro_font_48);

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