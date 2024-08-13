#pragma once
#include"CharacterBase.h"
#include <string>

class NpcBase : public CharacterBase
{
private:
    std::string* text_data_name;//メッセージ1桁

protected:

public:

    NpcBase(F_VECTOR2 array_location, F_VECTOR2 block_size, const char* text_data_name);
    ~NpcBase();

    void Update(float delta_time) override {};
    void Draw()const override {};

    std::string GetTextDataName()const;
};