#pragma once
#include"define.h"

class CharacterBase //�I�u�W�F�N�g�̊��N���X
{
private:
	F_VECTOR2 array_location;//�z���̍��W
	F_VECTOR2 location;//�I�u�W�F�N�g�̍��W

protected:

	void SetArrayLocation(F_VECTOR2 array_location);

	F_VECTOR2 GetArrayLocation()const;
	void UpdateLocation();

public:

	CharacterBase(F_VECTOR2 array_location, F_VECTOR2 tile_size);
	~CharacterBase();

	virtual void Update(float delta_time) = 0;
	virtual void Draw()const = 0;
};

