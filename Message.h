#pragma once
#include"define.h"
#include <string>
#include <vector>

class Message
{
private:
    std::vector<std::string> text_line;//メッセージ1桁
    std::vector<int>character_code;//文字コード


    float draw_text_time;//1文字表示するための時間
    int draw_line_text_num;//現在表示中のメッセージ桁の文字数
    int draw_line_text_max_num;//表示中のメッセージ桁の最大文字数
    int draw_text_line_num;//表示中のメッセージ桁
    int draw_start_text_line;
    I_VECTOR2 location;

    bool ProceedMessage(float delta_time);
    int GetLineTextNum(int draw_text_line_num)const;
    void UpdateTextLine();

public:
    Message(const char* message, bool open_txt_file, I_VECTOR2 location);
    ~Message();

    bool Update(float delta_time);
    void Draw() const;
};
