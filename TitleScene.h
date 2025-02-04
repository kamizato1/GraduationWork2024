#pragma once
#include "SceneBase.h"

#define MENU_NUM 4

class TitleScene : public SceneBase
{
private:

   int retro_font_100;
   int retro_font_48;

   int cursor_index;

public:
    TitleScene();
    virtual ~TitleScene();

    void Initialize() override;
    void Finalize() override;

    SCENE_TYPE Update(float time_count) override;
    void Draw() const override;

    SCENE_TYPE GetNowScene() const override;
};
