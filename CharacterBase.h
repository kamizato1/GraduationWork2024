#pragma once
#include"define.h"

class CharacterBase //オブジェクトの基底クラス
{
private:
	F_VECTOR2 array_location;//配列上の座標
	F_VECTOR2 location;//オブジェクトの座標

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

