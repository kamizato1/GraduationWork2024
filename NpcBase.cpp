#include"DxLib.h"
#include"NpcBase.h"

#define SPEED 2
#define DIRECTION_CHANGE_TIME 5.0f

NpcBase::NpcBase(VECTOR2_I location, VECTOR2_I location_index, int* image, const char* message)
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

	is_it_moving = false;
	can_move = true;

	strcpy_s(this->message,sizeof(this->message), message);
   
    OutputDebugString("NpcBaseコンストラクタ呼ばれました。\n");
}

NpcBase::~NpcBase()
{
    OutputDebugString("NpcBaseデストラクタが呼ばれました。\n");
}

bool NpcBase::Update(float delta_time)
{
	if (can_move)
	{
		if ((direction_change_time += delta_time) > DIRECTION_CHANGE_TIME)
		{
			direction_change_time = 0.0f;
			return true;
		}
	}

	return false;
}

VECTOR2_I NpcBase::UpdateLocationIndex()
{
	VECTOR2_I location_index = this->location_index;

	if (!is_it_moving)
	{
		int direction = GetRand(10);

		if (direction == 0)this->location_index.y -= 1, image_direction_index = direction, is_it_moving = true;
		else if (direction == 1)this->location_index.y += 1, image_direction_index = direction, is_it_moving = true;
		else if (direction == 2)this->location_index.x -= 1, image_direction_index = direction, is_it_moving = true;
		else if (direction == 3)this->location_index.x += 1, image_direction_index = direction, is_it_moving = true;
	}

	return location_index;
}


bool NpcBase::UpdateMovement(VECTOR2_I location_index, bool hit_object, VECTOR2_I tile_location)
{
	if (is_it_moving)
	{
		if (hit_object)
		{
			this->location_index = location_index;
			is_it_moving = false;
		}
		else return UpdateLocation(tile_location);
	}

	return false;
}

void NpcBase::SetCanMove(bool can_move)
{
	this->can_move = can_move;
}

bool NpcBase::UpdateLocation(VECTOR2_I tile_location)
{
	if (location.x < tile_location.x)
	{
		if ((location.x += SPEED) >= tile_location.x)is_it_moving = false;
	}
	else if (location.x > tile_location.x)
	{
		if ((location.x -= SPEED) <= tile_location.x)is_it_moving = false;
	}
	else if (location.y < tile_location.y)
	{
		if ((location.y += SPEED) >= tile_location.y)is_it_moving = false;
	}
	else if (location.y > tile_location.y)
	{
		if ((location.y -= SPEED) <= tile_location.y)is_it_moving = false;
	}

	if (!is_it_moving)location = tile_location;
	
	return !is_it_moving;
}


void NpcBase::Draw(VECTOR2_I add_location, int image_index)const
{
    DrawRotaGraph(location.x + add_location.x, location.y + add_location.y, 3, 0, image[(image_direction_index * 3) + image_index], TRUE);
}

int NpcBase::GetImageDirectionIndex()const
{
	return image_direction_index;
}

void NpcBase::SetImageDirectionIndex(int image_direction_index)
{
	this->image_direction_index = image_direction_index;
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


const char* NpcBase::GetNpcMessage()const
{
    return message;
}