#include"DxLib.h"
#include"WorldMap.h"

#define START_PLAYER_LOCATION_X 11
#define START_PLAYER_LOCATION_Y 106

#define MAX_ENCOUNT_RATE 10 //�ő�G���J�E���g��(����)
#define MAX_WALK_ENCOUNT_RATE 7 //�����Ă���Ƃ��オ��ő�G���J�E���g���i�����j
#define SAFE_ENCOUNT_STEP 5 //�G���J�E���g���Ȃ�����

#define SCREEN_BLINKING_TIME 0.08f //��ʓ_�Ŏ���
#define SCREEN_BLINKING_COUNT 5 //��ʓ_�ŉ�


WorldMap::WorldMap(Player* player) : MapBase(player)
{
	if (LoadDivGraph("data/WorldMap/tile.png", TILE_TYPE_NUM, TILE_TYPE_NUM, 1, 16, 16, tile_image) == -1)throw("data/WorldMap/tile.png���ǂݍ��߂܂���\n");
	
	SetMap();

	//�ϐ�
	encount_rate = -SAFE_ENCOUNT_STEP;
	screen_blinking_time = 0.0f;
	screen_blinking_count = 0;

    OutputDebugString("WorldMap�R���X�g���N�^�Ă΂�܂����B\n");

	SetFontSize(15);
}

void WorldMap::SetMap()
{
	FILE* map_data = nullptr;//�t�B�[���h�ǂݍ���

	errno_t error_field_data = fopen_s(&map_data, "data/WorldMap/map_data.txt", "r");
	if (error_field_data != 0)throw("data/WorldMap/map_data.txt���ǂݍ��߂܂���\n");//�G���[�`�F�b�N

	for (int i = 0; i < TILE_NUM; i++)
	{
		for (int j = 0; j < TILE_NUM; j++)
		{
			tile[i][j].location.x = (j * TILE_SIZE) + (TILE_SIZE / 2);
			tile[i][j].location.y = (i * TILE_SIZE) + (TILE_SIZE / 2);

			char c_map_data[3];
			fscanf_s(map_data, "%2s ", c_map_data, 3);

			char set_c_map_data = c_map_data[0];
			tile[i][j].type = strtol(&set_c_map_data, NULL, 36);
			set_c_map_data = c_map_data[1];
			tile[i][j].enemy_rank = strtol(&set_c_map_data, NULL, 36);
		}
	}

	fclose(map_data);
	
	//�v���C���[�̐ݒ�
	map_player.location_index.x = START_PLAYER_LOCATION_X; //�v���C���[���W�i�z��j
	map_player.location_index.y = START_PLAYER_LOCATION_Y;

	map_player.location.x = tile[map_player.location_index.y][map_player.location_index.x].location.x;
	map_player.location.y = tile[map_player.location_index.y][map_player.location_index.x].location.y;
}

WorldMap::~WorldMap()
{
    OutputDebugString("WorldMap�f�X�g���N�^���Ă΂�܂����B\n");
}


int WorldMap::Update(float delta_time)
{
	//�G���J�E���g�A�j���[�V����
	if (update_encount_animation)return UpdateEncountAnimation(delta_time);
	else
	{
		UpdatePlayerImageIndex(delta_time);

		if (UpdateScroll(tile[map_player.location_index.y][map_player.location_index.x],
			UpdateMovement(tile[map_player.location_index.y][map_player.location_index.x].location)))
		{
			if (++encount_rate > 0)
			{
				if (encount_rate > MAX_WALK_ENCOUNT_RATE)encount_rate = MAX_WALK_ENCOUNT_RATE;
				if (GetRand(MAX_ENCOUNT_RATE - encount_rate) == 0)update_encount_animation = true;
			}
		}
	}

    return -1;
}

int WorldMap::UpdateEncountAnimation(float delta_time)
{
	if ((screen_blinking_time += delta_time) >  SCREEN_BLINKING_TIME)
	{
		screen_blinking_time = 0.0f;

		if (++screen_blinking_count > (SCREEN_BLINKING_COUNT * 2) - 1)
		{
			screen_blinking_count = 0;
			update_encount_animation = false;
			encount_rate = -SAFE_ENCOUNT_STEP;

			//return -1;

			return tile[map_player.location_index.y][map_player.location_index.x].enemy_rank;
		}
	}

	return -1;
}

void WorldMap::Draw() const
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
				DrawRotaGraph((j * TILE_SIZE) - (TILE_SIZE / 2) + add_x, i * TILE_SIZE - (TILE_SIZE / 2) + add_y, 3, 0, tile_image[18], FALSE);
			}
			else DrawRotaGraph((j * TILE_SIZE) - (TILE_SIZE / 2) + add_x, i * TILE_SIZE - (TILE_SIZE / 2) + add_y, 3, 0, tile_image[tile[draw_tile_array_y][draw_tile_array_x].type], FALSE);


			//DrawFormatString((j * TILE_SIZE) - (TILE_SIZE / 2) + add_x - 20, i * TILE_SIZE - (TILE_SIZE / 2) + add_y, 0xffffff, "%d", tile[draw_tile_array_y][draw_tile_array_x].enemy_rank);
		}
	}

	DrawRotaGraph(HALF_SCREEN_SIZE, HALF_SCREEN_SIZE, 2, 0, player_image[1][player_image_index], TRUE);
	
	DrawBox(5, 50, 525, 130, 0xffffff, TRUE);
	DrawBox(10, 55, 520, 125, 0x000000, TRUE);
	//DrawFormatStringToHandle(25, 55, 0xffffff, retro_font_48, "%s  HP %3d MP %3d", player->GetName(), player->GetHp(), /*player->GetMp()*/encount_rate);

	//�_�ł̕\��
	if (screen_blinking_count % 2)DrawBox(0, 0, SCREEN_SIZE, SCREEN_SIZE, 0xffffff, TRUE);
}