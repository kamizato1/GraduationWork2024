#pragma once
#include"define.h"
#include <string>
#include <vector>

class Message
{
private:
    std::vector<std::string> text_line;//���b�Z�[�W1��
    std::vector<int>character_code;//�����R�[�h


    float draw_text_time;//1�����\�����邽�߂̎���
    int draw_line_text_num;//���ݕ\�����̃��b�Z�[�W���̕�����
    int draw_line_text_max_num;//�\�����̃��b�Z�[�W���̍ő啶����
    int draw_text_line_num;//�\�����̃��b�Z�[�W��
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
