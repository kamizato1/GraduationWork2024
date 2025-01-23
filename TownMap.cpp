#include"DxLib.h"
#include"TownMap.h"

#define START_PLAYER_LOCATION_X 15
#define START_PLAYER_LOCATION_Y 15

TownMap::TownMap(Player* player) : MapBase(player)
{
	if (LoadDivGraph("data/TownMap/tile.png", TILE_TYPE_NUM, TILE_TYPE_NUM, 1, 16, 16, tile_image) == -1)throw("data/image/TownMap/tile.png���ǂݍ��߂܂���\n");

	SetMap();

	OutputDebugString("TownMap�R���X�g���N�^�Ă΂�܂����B\n");
}

void TownMap::SetMap()
{
	FILE* map_data = nullptr;//�t�B�[���h�ǂݍ���
	
	errno_t error_map_data = fopen_s(&map_data, "data/TownMap/map_data.txt", "r");
	if (error_map_data != 0)throw("data/TownMap/map_data.txt���ǂݍ��߂܂���\n");//�G���[�`�F�b�N

	for (int i = 0; i < TILE_NUM; i++)
	{
		for (int j = 0; j < TILE_NUM; j++)
		{
			tile[i][j].location.x = (j * TILE_SIZE) + (TILE_SIZE / 2);
			tile[i][j].location.y = (i * TILE_SIZE) + (TILE_SIZE / 2);
			
			char c_map_data[2];
			fscanf_s(map_data, "%c ", c_map_data, 1);
			tile[i][j].type = strtol(&c_map_data[0], NULL, 36);
		}
	}

	fclose(map_data);

	//�v���C���[�̐ݒ�
	map_player.location_index.x = START_PLAYER_LOCATION_X; //�v���C���[���W�i�z��j
	map_player.location_index.y = START_PLAYER_LOCATION_Y;

	map_player.location.x = tile[map_player.location_index.y][map_player.location_index.x].location.x;
	map_player.location.y = tile[map_player.location_index.y][map_player.location_index.x].location.y;
}

TownMap::~TownMap()
{
	OutputDebugString("TownMap�f�X�g���N�^���Ă΂�܂����B\n");
}


int TownMap::Update(float delta_time)
{
	UpdatePlayerImageIndex(delta_time);

	UpdateScroll(tile[map_player.location_index.y][map_player.location_index.x],
		UpdateMovement(tile[map_player.location_index.y][map_player.location_index.x].location));

	return -1;
}

void TownMap::Draw() const
{
	for (int i = 0; i < DRAW_TILE_NUM; i++)//�c�̌J��Ԃ�
	{
		for (int j = 0; j < DRAW_TILE_NUM; j++)//���̌J��Ԃ�
		{
			int draw_tile_array_x = map_player.location_index.x - (DRAW_TILE_NUM / 2) + j;
			int draw_tile_array_y = map_player.location_index.y - (DRAW_TILE_NUM / 2) + i;

			int add_x = tile[map_player.location_index.y][map_player.location_index.x].location.x - map_player.location.x;
			int add_y = tile[map_player.location_index.y][map_player.location_index.x].location.y - map_player.location.y;

			if ((draw_tile_array_y < 0) || (draw_tile_array_y >= TILE_NUM) || (draw_tile_array_x < 0) || (draw_tile_array_x >= TILE_NUM))
			{
				//�}�b�v�̊O�͊C�̉摜
				DrawRotaGraph((j * TILE_SIZE) - (TILE_SIZE / 2) + add_x, i * TILE_SIZE - (TILE_SIZE / 2) + add_y, 3, 0, tile_image[0], FALSE);
			}
			else DrawRotaGraph((j * TILE_SIZE) - (TILE_SIZE / 2) + add_x, i * TILE_SIZE - (TILE_SIZE / 2) + add_y, 3, 0, tile_image[tile[draw_tile_array_y][draw_tile_array_x].type], FALSE);
		}
	}

	DrawRotaGraph(HALF_SCREEN_SIZE, HALF_SCREEN_SIZE, 2, 0, player_image[1][player_image_index], TRUE);

}