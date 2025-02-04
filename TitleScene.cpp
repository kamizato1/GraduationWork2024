#include "TitleScene.h"
#include "DxLib.h"
#include "Key.h"


TitleScene::TitleScene()
{
    retro_font_100 = LoadFontDataToHandle("data/font/DragonQuestFont100.dft", 0);
    retro_font_48 = LoadFontDataToHandle("data/font/DragonQuestFont48.dft", 0);
    cursor_index = 0;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
  
}

void TitleScene::Finalize()
{
    
}

SCENE_TYPE TitleScene::Update(float time_count)
{
    if (Key::KeyDown(KEY_TYPE::UP))
    {
        if (--cursor_index < 0)cursor_index = 1;
    }
    else if (Key::KeyDown(KEY_TYPE::DOWN))
    {
        if (++cursor_index > 1)cursor_index = 0;
    }
    if (Key::KeyDown(KEY_TYPE::A))
    {
        if (cursor_index == 0)return SCENE_TYPE::MAIN;
        else return SCENE_TYPE::GAME_END;
    }

    return GetNowScene();
}

void TitleScene::Draw() const
{
    DrawStringToHandle(185, 100, "ぼうけんゲーム", 0xffffff, retro_font_100);

    int color = 0xffffff;
    if (cursor_index == 0)color = 0xff0000;

    DrawStringToHandle(300, 300, "スタート", color, retro_font_48);

    color = 0xffffff;
    if (cursor_index == 1)color = 0xff0000;

    DrawStringToHandle(310, 380, "おわり", color, retro_font_48);
}

SCENE_TYPE TitleScene::GetNowScene() const
{
    return SCENE_TYPE::TITLE;
}