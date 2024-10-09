#pragma once
#include <string>

class NpcBase
{
private:
    std::string* text_data_name;//���b�Z�[�W1��

protected:

public:

    NpcBase(const std::string& name);
    ~NpcBase();

    void Update(float delta_time);
    void Draw()const;

    std::string GetTextDataName()const;
};