#include"dxlib.h"
#include"ObjectBase.h"

ObjectBase::ObjectBase(F_VECTOR2 array_location, F_VECTOR2 block_size)
{
	this->array_location = array_location; //配列座標

	this->location.x = array_location.x * block_size.x;//座標
	this->location.y = array_location.y * block_size.y;

    OutputDebugString("ObjectBaseコンストラクタが呼ばれました。\n");
}

ObjectBase::~ObjectBase()
{
    OutputDebugString("ObjectBaseデストラクタが呼ばれました。\n");
}

void ObjectBase::SetArrayLocation(F_VECTOR2 array_location)
{

}



I_VECTOR2 array_location;//配列上の座標
F_VECTOR2 location;//オブジェクトの座標

protected:
	void SetArrayLocation(I_VECTOR2 array_location);
	I_VECTOR2 GetArrayLocation()const;

	void UpdateLocation();
