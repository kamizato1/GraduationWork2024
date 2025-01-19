#include"DxLib.h"
#include"Field.h"
#include"Key.h"
#include"Player.h"

#define TILE_SIZE 48 //�^�C���̑傫��

#define DRAW_TILE_NUM 17 //�\������t�B�[���h�̃^�C���̐�

#define PLAYER_IMAGE_CHANGE_TIME 0.2f //�摜�؂�ւ�����
#define PLAYER_IMAGE_INDEX 4 //�v���C���[�摜�z��

#define PLAYER_SPEED 2 //�v���C���[�̈ړ����x

#define MAX_ENCOUNT_RATE 10 //�ő�G���J�E���g��(����)
#define MAX_WALK_ENCOUNT_RATE 7 //�����Ă���Ƃ��オ��ő�G���J�E���g���i�����j
#define SAFE_ENCOUNT_STEP 5 //�G���J�E���g���Ȃ�����

#define SCREEN_BLINKING_TIME 0.08f //��ʓ_�Ŏ���
#define SCREEN_BLINKING_COUNT 5 //��ʓ_�ŉ�

int WrapAround(int value, int min, int max)//�l���͈͊O�ɂȂ�����������悤�ɂ���
{
	if (min > max)
	{
		int work = min;
		min = max;
		max = work;
	}

	if (value > max)return min + (value - max) - 1;
	else if (value < min)return max - (min - value) + 1;

	return value;
}

Field::Field(Player* player)
{
	this->player = player;

	if (LoadDivGraph("data/image/Field/tile.png", TILE_TYPE_NUM, TILE_TYPE_NUM, 1, 16, 16, tile_image) == -1)throw("data/image/Field/tile.png���ǂݍ��߂܂���\n");
	if (LoadDivGraph("data/image/Field/Player/walk.png", 5, 5, 1, 50, 50, player_image[1]) == -1)throw("data/image/Field/Player/walk.png���ǂݍ��߂܂���\n");
	if (LoadDivGraph("data/image/Field/Player/wait.png", 5, 5, 1, 50, 50, player_image[0]) == -1)throw("data/image/Field/Player/wait.png.png���ǂݍ��߂܂���\n");

	//�t�H���g�̓ǂݍ���
	retro_font_48 = LoadFontDataToHandle("data/font/DragonQuestFont48.dft", 0);

	SetField();

	//�v���C���[�̐ݒ�
	field_player.location_index.x = 11; //�v���C���[���W�i�z��j
	field_player.location_index.y = 106;

	field_player.location.x = tile[field_player.location_index.y][field_player.location_index.x].location.x;
	field_player.location.y = tile[field_player.location_index.y][field_player.location_index.x].location.y;

	//�ϐ�
	player_image_change_time = 0.0f;
	player_image_index = 0;

	encount_rate = -SAFE_ENCOUNT_STEP;

	screen_blinking_time = 0.0f;
	screen_blinking_count = 0;

    OutputDebugString("Field�R���X�g���N�^�Ă΂�܂����B\n");
}

void Field::SetField()
{
	FILE* field_data = nullptr;//�t�B�[���h�ǂݍ���
	FILE* enemy_rank_data = nullptr;//�o������G�̃����N�ǂݍ���

	errno_t error_field_data = fopen_s(&field_data, "data/map/field.txt", "r");
	if (error_field_data != 0)throw("data/map/field.txt���ǂݍ��߂܂���\n");//�G���[�`�F�b�N

	errno_t error_enemy_rank_data = fopen_s(&enemy_rank_data, "data/map/enemyrank.txt", "r");
	if (error_enemy_rank_data != 0)throw("data/map/enemyrank.txt���ǂݍ��߂܂���\n");//�G���[�`�F�b�N

	for (int i = 0; i < FIELD_TILE_NUM; i++)
	{
		for (int j = 0; j < FIELD_TILE_NUM; j++)
		{
			tile[i][j].location.x = (j * TILE_SIZE) + (TILE_SIZE / 2);
			tile[i][j].location.y = (i * TILE_SIZE) + (TILE_SIZE / 2);
			fscanf_s(field_data, "%d", &tile[i][j].type);
			fscanf_s(enemy_rank_data, "%d", &tile[i][j].enemy_rank);
		}
	}

	fclose(field_data);
	fclose(enemy_rank_data);
}

Field::~Field()
{
    OutputDebugString("Field�f�X�g���N�^���Ă΂�܂����B\n");
}


int Field::Update(float delta_time)
{
	//�G���J�E���g�A�j���[�V����
	if (update_encount_animation)return UpdateEncountAnimation(delta_time);
	else
	{
		if ((player_image_change_time += delta_time) > PLAYER_IMAGE_CHANGE_TIME)
		{
			if (++player_image_index == PLAYER_IMAGE_INDEX)player_image_index = 0;
			player_image_change_time = 0.0f;
		}

		UpdateMovement();

		
	}

    return -1;
}

void Field::UpdateMovement()
{
	if (field_player.location == tile[field_player.location_index.y][field_player.location_index.x].location)
	{
		VECTOR2_I location_index = field_player.location_index;

		if (Key::KeyPressed(KEY_TYPE::UP))field_player.location_index.y = field_player.location_index.y - 1;
		else if (Key::KeyPressed(KEY_TYPE::DOWN))field_player.location_index.y = field_player.location_index.y + 1;
		else if (Key::KeyPressed(KEY_TYPE::LEFT))field_player.location_index.x = field_player.location_index.x - 1;
		else if (Key::KeyPressed(KEY_TYPE::RIGHT))field_player.location_index.x = field_player.location_index.x + 1;

		//�����蔻��
		if (tile[field_player.location_index.y][field_player.location_index.x].type >= 17)field_player.location_index = location_index;
	}
	else
	{
		if (UpdateScroll())
		{
			if (++encount_rate > 0)
			{
				if (encount_rate > MAX_WALK_ENCOUNT_RATE)encount_rate = MAX_WALK_ENCOUNT_RATE;
				if (GetRand(MAX_ENCOUNT_RATE - encount_rate) == 0)update_encount_animation = true;
			}
		}
	}
}

bool Field::UpdateScroll()
{
	if (UpdateAddScrollValue(&field_player.location.x, &tile[field_player.location_index.y][field_player.location_index.x].location.x))return true;
	if (UpdateAddScrollValue(&field_player.location.y, &tile[field_player.location_index.y][field_player.location_index.x].location.y))return true;
	
	return false;
}

bool Field::UpdateAddScrollValue(int* player_location, int* tile_location)
{
	if (*player_location < *tile_location)
	{
		if ((*player_location += PLAYER_SPEED) >= *tile_location)
		{
			*player_location = *tile_location;
			return true;
		}
	}
	else if (*player_location > *tile_location)
	{
		if ((*player_location -= PLAYER_SPEED) <= *tile_location)
		{
			*player_location = *tile_location;
			return true;
		}
	}
	return false;
}


int Field::UpdateEncountAnimation(float delta_time)
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

			return tile[field_player.location_index.y][field_player.location_index.x].enemy_rank;
		}
	}

	return -1;
}

void Field::Draw() const
{
	for (int i = 0; i < DRAW_TILE_NUM; i++)//�c�̌J��Ԃ�
	{
		for (int j = 0; j < DRAW_TILE_NUM; j++)//���̌J��Ԃ�
		{
			int draw_tile_array_x = field_player.location_index.x - (DRAW_TILE_NUM / 2) + j;
			int draw_tile_array_y = field_player.location_index.y - (DRAW_TILE_NUM / 2) + i;

			int add_x = tile[field_player.location_index.y][field_player.location_index.x].location.x - field_player.location.x;
			int add_y = tile[field_player.location_index.y][field_player.location_index.x].location.y - field_player.location.y;

			DrawRotaGraph((j * TILE_SIZE) - (TILE_SIZE / 2) + add_x, i * TILE_SIZE - (TILE_SIZE / 2) + add_y, 3, 0, tile_image[tile[draw_tile_array_y][draw_tile_array_x].type], FALSE);
		}
	}

	DrawRotaGraph(HALF_SCREEN_SIZE, HALF_SCREEN_SIZE, 2, 0, player_image[1][player_image_index], TRUE);
	
	DrawBox(5, 50, 525, 130, 0xffffff, TRUE);
	DrawBox(10, 55, 520, 125, 0x000000, TRUE);
	DrawFormatStringToHandle(25, 55, 0xffffff, retro_font_48, "%s  HP %3d MP %3d", player->GetName(), player->GetHp(), /*player->GetMp()*/encount_rate);

	//�_�ł̕\��
	if (screen_blinking_count % 2)DrawBox(0, 0, SCREEN_SIZE, SCREEN_SIZE, 0xffffff, TRUE);
}