#include"dxlib.h"
#include"ObjectBase.h"

ObjectBase::ObjectBase(F_VECTOR2 array_location, F_VECTOR2 block_size)
{
	this->array_location = array_location; //�z����W

	this->location.x = array_location.x * block_size.x;//���W
	this->location.y = array_location.y * block_size.y;

    OutputDebugString("ObjectBase�R���X�g���N�^���Ă΂�܂����B\n");
}

ObjectBase::~ObjectBase()
{
    OutputDebugString("ObjectBase�f�X�g���N�^���Ă΂�܂����B\n");
}

void ObjectBase::SetArrayLocation(F_VECTOR2 array_location)
{

}



I_VECTOR2 array_location;//�z���̍��W
F_VECTOR2 location;//�I�u�W�F�N�g�̍��W

protected:
	void SetArrayLocation(I_VECTOR2 array_location);
	I_VECTOR2 GetArrayLocation()const;

	void UpdateLocation();
