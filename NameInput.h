#pragma once
#include"define.h"

class NameInput
{
private:

    char moji[5][11][10] =
    {
        {"あ","い","う","え","お","は","ひ","ふ","へ","ほ","゛"},
        {"か","き","く","け","こ","ま","み","む","め","も","゜"},
        {"さ","し","す","せ","そ","ら","り","る","れ","ろ","ー"},
        {"た","ち","つ","て","と","や","ゆ","よ","わ","ん","もどる"},
        {"な","に","ぬ","ね","の","ゃ","ゅ","ょ","っ","を","おわり"}
    };
  
    //フォント
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