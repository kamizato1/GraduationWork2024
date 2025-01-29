#include"DxLib.h"
#include"NpcBase.h"

#define SPEED 2
#define DIRECTION_CHANGE_TIME 5.0f

NpcBase::NpcBase(VECTOR2_I location, VECTOR2_I location_index, int* image)
{
    this->location = location;
    this->location_index = location_index;

	for (int i = 0; i < 16; i++)
	{
		if(image == nullptr)this->image[i] = NULL;
		else this->image[i] = image[i];
	}

	image_direction_index = 0;
	direction_change_time = 0.0f;

    //this->text_data_name = new std::string(text_data_name);
   
    OutputDebugString("NpcBaseコンストラクタ呼ばれました。\n");
}

NpcBase::~NpcBase()
{
    OutputDebugString("NpcBaseデストラクタが呼ばれました。\n");
}

bool NpcBase::Update(float delta_time)
{
	if ((direction_change_time += delta_time) > DIRECTION_CHANGE_TIME)
	{
		direction_change_time = 0.0f;
		return true;
	}

	return false;
}

VECTOR2_I NpcBase::UpdateMovement(VECTOR2_I tile_location)
{
	VECTOR2_I location_index = this->location_index;

	if (location == tile_location)
	{
		int direction = GetRand(10);

		if (direction == 0)this->location_index.y -= 1;
		else if (direction == 1)this->location_index.y += 1;
		else if (direction == 2)this->location_index.x -= 1;
		else if (direction == 3)this->location_index.x += 1;

		if (direction < 4) image_direction_index = direction;
	}

	return location_index;
}


bool NpcBase::UpdateScroll(int tile_type, int collide_tile_type, VECTOR2_I location_index, VECTOR2_I tile_location)
{
	if (tile_type >= collide_tile_type)this->location_index = location_index;
	else return UpdateAddScrollValue(tile_location);

	return false;
}

bool NpcBase::UpdateAddScrollValue(VECTOR2_I tile_location)
{
	bool set_location = false;

	if (location.x < tile_location.x)
	{
		if ((location.x += SPEED) >= tile_location.x)set_location = true;
	}
	else if (location.x > tile_location.x)
	{
		if ((location.x -= SPEED) <= tile_location.x)set_location = true;
	}
	else if (location.y < tile_location.y)
	{
		if ((location.y += SPEED) >= tile_location.y)set_location = true;
	}
	else if (location.y > tile_location.y)
	{
		if ((location.y -= SPEED) <= tile_location.y)set_location = true;
	}

	if(set_location)location = tile_location;

	return set_location;
}


void NpcBase::Draw(VECTOR2_I add_location, int image_index)const
{
    DrawRotaGraph(location.x + add_location.x, location.y + add_location.y, 3, 0, image[(image_direction_index * 3) + image_index], TRUE);
}



VECTOR2_I NpcBase::GetLocationIndex()const
{
	return location_index;
}

VECTOR2_I NpcBase::GetLocation()const
{
	return location;
}

void NpcBase::SetLocationIndex(VECTOR2_I location_index)
{
	this->location_index = location_index;
}

void NpcBase::SetLocation(VECTOR2_I location)
{
	this->location = location;
}


//std::string NpcBase::GetTextDataName()const
//{
//    return *text_data_name;
//}