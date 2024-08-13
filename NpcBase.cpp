#include"DxLib.h"
#include"NpcBase.h"

NpcBase::NpcBase(F_VECTOR2 array_location, F_VECTOR2 block_size, const char* text_data_name) : CharacterBase(array_location, block_size)
{
    //this->text_data_name = new std::string(text_data_name);
   
    OutputDebugString("NpcBase�R���X�g���N�^�Ă΂�܂����B\n");
}

NpcBase::~NpcBase()
{
    delete text_data_name;

    OutputDebugString("NpcBase�f�X�g���N�^���Ă΂�܂����B\n");
}

std::string NpcBase::GetTextDataName()const
{
    return *text_data_name;
}