#include"dxlib.h"
#include"CharacterBase.h"

CharacterBase::CharacterBase(F_VECTOR2 array_location, F_VECTOR2 tile_size)
{
	this->array_location = array_location; //�z����W

	this->location.x = array_location.x * tile_size.x;//���W
	this->location.y = array_location.y * tile_size.y;

	OutputDebugString("ObjectBase�R���X�g���N�^���Ă΂�܂����B\n");
}

CharacterBase::~CharacterBase()
{
	OutputDebugString("ObjectBase�f�X�g���N�^���Ă΂�܂����B\n");
}

void CharacterBase::SetArrayLocation(F_VECTOR2 array_location)
{

}