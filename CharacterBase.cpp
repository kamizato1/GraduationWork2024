#include"dxlib.h"
#include"CharacterBase.h"

CharacterBase::CharacterBase(F_VECTOR2 array_location, F_VECTOR2 tile_size)
{
	this->array_location = array_location; //配列座標

	this->location.x = array_location.x * tile_size.x;//座標
	this->location.y = array_location.y * tile_size.y;

	OutputDebugString("ObjectBaseコンストラクタが呼ばれました。\n");
}

CharacterBase::~CharacterBase()
{
	OutputDebugString("ObjectBaseデストラクタが呼ばれました。\n");
}

void CharacterBase::SetArrayLocation(F_VECTOR2 array_location)
{

}