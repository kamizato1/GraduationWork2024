#pragma once
#include"define.h"

class NameInput
{
private:

    char moji[5][11][10] =
    {
        {"��","��","��","��","��","��","��","��","��","��","�J"},
        {"��","��","��","��","��","��","��","��","��","��","�K"},
        {"��","��","��","��","��","��","��","��","��","��","�["},
        {"��","��","��","��","��","��","��","��","��","��","���ǂ�"},
        {"��","��","��","��","��","��","��","��","��","��","�����"}
    };
  
    //�t�H���g
    int retro_font_48;

    char name[13] = {'\0'};
    int moji_count;

    int bright_value;

    VECTOR2_I cursor_location_index;

public:

    NameInput();
    ~NameInput();

    bool Update(float delta_time);
    void Draw() const;

    const char* GetName()const;
};