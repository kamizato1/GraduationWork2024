#pragma once
#include"define.h"

class ObjectBase //オブジェクトの基底クラス
{
private:
	F_VECTOR2 array_location;//配列上の座標
	F_VECTOR2 location;//オブジェクトの座標

protected:
	void SetArrayLocation(F_VECTOR2 array_location);
	F_VECTOR2 GetArrayLocation()const;
	
	void UpdateLocation();

public:

	ObjectBase(F_VECTOR2 array_location, F_VECTOR2 block_size);
	~ObjectBase();
};

