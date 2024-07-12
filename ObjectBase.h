#pragma once
#include"define.h"

class ObjectBase //�I�u�W�F�N�g�̊��N���X
{
private:
	F_VECTOR2 array_location;//�z���̍��W
	F_VECTOR2 location;//�I�u�W�F�N�g�̍��W

protected:
	void SetArrayLocation(F_VECTOR2 array_location);
	F_VECTOR2 GetArrayLocation()const;
	
	void UpdateLocation();

public:

	ObjectBase(F_VECTOR2 array_location, F_VECTOR2 block_size);
	~ObjectBase();
};

