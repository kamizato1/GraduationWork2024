#include "Message.h"
#include "Key.h"
#include "DxLib.h"

#define DRAW_TEXT_TIME 0.08f // 1�����\������܂ł̎���
#define FAST_DRAW_TEXT_TIME 0.02f // A�{�^������������1�����\������܂ł̎���

#define DRAW_TEXT_LOCATION_X 50.0f
#define DRAW_TEXT_LOCATION_Y 550.0f

#define MAX_DRAW_TEXT_LINE 3 // 1�x�ɕ\���ł��郁�b�Z�[�W�̍s��(�ő�)
#define MAX_DRAW_TEXT_NUM 300 // 1�x�ɕ\���ł��镶����


Message::Message(const char* message_data, bool open_txt_file, VECTOR2_I location) : location(location)
{
    draw_start_text_line = 0;
    draw_text_time = 0.0f;
    draw_line_text_num = 0;
    draw_line_text_max_num = 0;
    draw_text_line_num = 0;

    if (open_txt_file)
    {
        int text_data = NULL;
        if ((text_data = FileRead_open(message_data)) == 0) throw("text_data���ǂݍ��߂܂���\n");

        while (FileRead_eof(text_data) == 0)
        {
            char text[256];

            if (FileRead_gets(text, sizeof(text), text_data) != -1)
            {
                text_line.push_back(text);
                text_line.back() += "\n";
            }
            else break;
        }
        FileRead_close(text_data);
    }
    else
    {
        text_line.push_back(message_data);
        text_line.back() += "\n";
    }

    draw_line_text_max_num = GetLineTextNum(draw_text_line_num);
}

Message::~Message()
{
    text_line.clear();
    text_line.shrink_to_fit();
}

bool Message::Update(float delta_time)
{
    // A�{�^��������������Ă���ꍇ�̕`�掞��
    float effective_draw_text_time = DRAW_TEXT_TIME;
    if (Key::KeyPressed(KEY_TYPE::A))
    {
        effective_draw_text_time = FAST_DRAW_TEXT_TIME;
    }

    if (draw_line_text_num > draw_line_text_max_num)
    {
        if (draw_text_line_num >= text_line.size() - 1)
        {
            if (Key::KeyDown(KEY_TYPE::A)) return true;
        }
        else if ((draw_text_line_num + 1) % MAX_DRAW_TEXT_LINE == 0)
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
    draw_line_text_max_num = GetLineTextNum(++draw_text_line_num);
    draw_line_text_num = 0;
    draw_start_text_line = draw_text_line_num - (MAX_DRAW_TEXT_LINE - 1);
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
    DrawBox(0, 540, 1280, 720, 0x000000, TRUE);
    DrawBox(0, 540, 1280, 720, 0xffffff, FALSE);

    // ���ݕ\���ł��镶����
    int draw_line_text_num = this->draw_line_text_num;

    // �����̕\���ʒu
    VECTOR2_I text_location = { DRAW_TEXT_LOCATION_X, DRAW_TEXT_LOCATION_Y };

    for (int i = draw_start_text_line; i < text_line.size(); i++)
    {
        if (i > draw_text_line_num) break;

        for (int j = 0; j < text_line[i].length(); j++)
        {
            // �����̃T�C�Y�𒲂ׂ�
            int text_size = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, text_line[i].c_str() + j);

            if ((i == draw_text_line_num) && (draw_line_text_num <= 0)) break;
            else if (*(text_line[i].c_str() + j) == '\n')
            {
                // ���s�����̏ꍇ
                text_location.y += FONT_SIZE + 5; // y���W���X�V���ĉ��s
                text_location.x = DRAW_TEXT_LOCATION_X; // x���W�����Z�b�g
            }
            else if (text_size == 1)
            {
                // ���p�����̏ꍇ
                DrawFormatString(text_location.x, text_location.y, 0xffffff, "%c", *(text_line[i].c_str() + j));
                text_location.x += (FONT_SIZE / 2); // X���W���X�V
                if (i == draw_text_line_num) draw_line_text_num--;
            }
            else if (text_size == 2)
            {
                // �S�p�����̏ꍇ
                DrawFormatString(text_location.x, text_location.y, 0xffffff, "%c%c", *(text_line[i].c_str() + j), *(text_line[i].c_str() + j + 1));
                text_location.x += FONT_SIZE; //X���W���X�V
                if (i == draw_text_line_num) draw_line_text_num--;
                j++;
            }
        }
    }

    //DrawFormatString(SCREEN_CENTER_X, 680, 0xffffff, "%f", draw_text_time);
}