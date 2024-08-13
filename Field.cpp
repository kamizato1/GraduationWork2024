#include"DxLib.h"
#include"define.h"
#include"Field.h"
#include"Tile.h"

Field::Field()
{
    class PlayerManager* player_manager;
    class EnemyManager* enemy_manager;
    class AttackManager* attack_manager;
    class EventManager* event_manager;

	SetField();

    OutputDebugString("Field�R���X�g���N�^�Ă΂�܂����B\n");
}

void Field::SetField()
{
	const F_VECTOR2 tile_size = { 72.0f,72.0f };

	for (int i = 0; i < 10; i++)//�c�̌J��Ԃ�
	{
		for (int j = 0; j < 10; j++)//���̌J��Ԃ�
		{
			tile[i][j] = new Tile({ (j * tile_size.x) + (tile_size.x / 2), (i * tile_size.y) + (tile_size.y / 2) }, tile_size);
		}
	}
}

Field::~Field()
{
    OutputDebugString("Field�f�X�g���N�^���Ă΂�܂����B\n");
}

bool Field::Update(float delta_time)
{
    return false;
}

void Field::Draw() const
{
	for (int i = 0; i < 10; i++)//�c�̌J��Ԃ�
	{
		for (int j = 0; j < 10; j++)//���̌J��Ԃ�
		{
			tile[i][j]->Draw(0.0f);
		}
	}
}