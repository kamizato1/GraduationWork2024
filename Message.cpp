#include "Message.h"
#include "Key.h"
#include "DxLib.h"

#define DRAW_TEXT_TIME 0.08f // 1�����\������܂ł̎���
#define FAST_DRAW_TEXT_TIME 0.02f // A�{�^������������1�����\������܂ł̎���

#define DRAW_TEXT_LOCATION_X 55
#define DRAW_TEXT_LOCATION_Y 505

#define MAX_DRAW_TEXT_LINE 3 // 1�x�ɕ\���ł��郁�b�Z�[�W�̍s��(�ő�)
#define MAX_DRAW_TEXT_NUM 300 // 1�x�ɕ\���ł��镶����

Message::Message(const char* message) : draw_text_time(0.0f), draw_line_text_num(0),
update_text_line(0), update_line_text_num(0), draw_start_text_line(0)
{
    //�t�H���g�̓ǂݍ���
    retro_font_48 = LoadFontDataToHandle("data/font/DragonQuestFont48.dft", 0);

    char message_line[256];
    for (int i = 0; i < 256; i++)message_line[i] = '\0';
    int message_count = 0;

    for (int i = 0; message[i] != '\0'; i++)
    {
        message_line[message_count++] = message[i];

        if (message[i] == '\n')
        {
            text_line.push_back(message_line);
            message_count = 0;
            for (int i = 0; i < 256; i++)message_line[i] = '\0';
        }
    }
    text_line.push_back(message_line);

    // 1�s�ڂ̕����̐��𐔂���
    update_line_text_num = GetLineTextNum(update_text_line);
}

Message::~Message()
{
    text_line.clear();
    text_line.shrink_to_fit();

    DeleteFontToHandle(retro_font_48);
}

bool Message::Update(float delta_time)
{
    // A�{�^��������������Ă���ꍇ�̕`�掞��
    float effective_draw_text_time = DRAW_TEXT_TIME;
    if (Key::KeyPressed(KEY_TYPE::A))
    {
        effective_draw_text_time = FAST_DRAW_TEXT_TIME;
    }

    if (draw_line_text_num > update_line_text_num)
    {
        if (update_text_line >= text_line.size() - 1)
        {
            if (Key::KeyDown(KEY_TYPE::A)) return true;
        }
        else if ((update_text_line + 1) % MAX_DRAW_TEXT_LINE == 0)
        {
            if (Key::KeyDown(KEY_TYPE::A)) UpdateTextLine();
        }
        else UpdateTextLine();
    }
    else if ((draw_text_time += delta_time) > effective_draw_text_time)
    {
        draw_line_text_num++;
        draw_text_time = 0.0f;
    }

    return false;
}

void Message::UpdateTextLine()
{
    update_line_text_num = GetLineTextNum(++update_text_line);
    draw_line_text_num = 0;
    draw_start_text_line = update_text_line - (MAX_DRAW_TEXT_LINE - 1);
    if (draw_start_text_line < 0) draw_start_text_line = 0;
}

int Message::GetLineTextNum(int draw_text_line) const
{
    int text_count = 0;

    if (draw_text_line >= 0 && draw_text_line < text_line.size()) // ���E�`�F�b�N��ǉ�
    {
        for (int i = 0; i < text_line[draw_text_line].length(); i++)
        {
            // �����̃T�C�Y�𒲂ׂ�
            int text_size = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, text_line[draw_text_line].c_str() + i);

            if (*(text_line[draw_text_line].c_str() + i) == '\n') break;
            else if (text_size == 1) text_count++;
            else if (text_size == 2)
            {
                text_count++;
                i++;
            }
        }
    }

    return text_count;
}

void Message::Draw() const
{
    DrawBox(5 , 500 , 715 , 715 , 0xffffff, TRUE);
    DrawBox(10 , 505 , 710 , 710 , 0x000000, TRUE);

    // ���ݕ\���ł��镶����
    int draw_line_text_num = this->draw_line_text_num;

    // �����̕\���ʒu
    VECTOR2_I text_location = { DRAW_TEXT_LOCATION_X, DRAW_TEXT_LOCATION_Y };

    for (int i = draw_start_text_line; i < text_line.size(); i++)
    {
        if (i > update_text_line) break;

        for (int j = 0; j < text_line[i].length(); j++)
        {
            // �����̃T�C�Y�𒲂ׂ�
            int text_size = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, text_line[i].c_str() + j);

            if ((i == update_text_line) && (draw_line_text_num <= 0)) break;
            else if (*(text_line[i].c_str() + j) == '\n')
            {
                // ���s�����̏ꍇ
                text_location.y += 45; // y���W���X�V���ĉ��s
                text_location.x = DRAW_TEXT_LOCATION_X; // x���W�����Z�b�g
            }
            else if (text_size == 1)
            {
                // ���p�����̏ꍇ
                DrawFormatStringToHandle(text_location.x, text_location.y, 0xffffff, retro_font_48, "%c", *(text_line[i].c_str() + j));
                text_location.x += 10; // X���W���X�V
                if (i == update_text_line) draw_line_text_num--;
            }
            else if (text_size == 2)
            {
                // �S�p�����̏ꍇ
                DrawFormatStringToHandle(text_location.x, text_location.y, 0xffffff, retro_font_48, "%c%c", *(text_line[i].c_str() + j), *(text_line[i].c_str() + j + 1));
                text_location.x += 25; //X���W���X�V
                if (i == update_text_line) draw_line_text_num--;
                j++;
            }
        }
    }

    //DrawFormatString(SCREEN_CENTER_X, 680, 0xffffff, "%f", draw_text_time);
}
