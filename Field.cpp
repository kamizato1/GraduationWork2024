#include"DxLib.h"
#include"Field.h"
#include"Key.h"
#include"Player.h"

#define TILE_SIZE_X 48 //�^�C���̑傫��
#define TILE_SIZE_Y 48

#define DRAW_TILE_NUM_X 17 //�\������t�B�[���h�̃^�C���̐�
#define DRAW_TILE_NUM_Y 17

#define PLAYER_SPEED 2 //�v���C���[�̈ړ����x

#define CHANGE_IMAGE_TIME 10 //�摜�؂�ւ�����
#define MAX_ENCOUNT_RATE 10 //�ő�G���J�E���g��(����)
#define MAX_WALK_ENCOUNT_RATE 7 //�����Ă���Ƃ��オ��ő�G���J�E���g���i�����j
#define SAFE_ENCOUNT_STEP 5 //�G���J�E���g���Ȃ�����
#define ENCOUNT_BLINKING_TIME_INTERVAL 5 //�G���J�E���g�̉�ʓ_�ŊԊu
#define ENCOUNT_BLINKING_COUNT 5 //�G���J�E���g�̓_�ŉ�

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

	SetField();

	//�v���C���[�̐ݒ�
	field_player.target_tile_array.x = 194; //�v���C���[���W�i�z��j
	field_player.target_tile_array.y = 28;

	field_player.position.x = (field_player.target_tile_array.x * TILE_SIZE_X) + (TILE_SIZE_X / 2); //�v���C���[���W
	field_player.position.y = (field_player.target_tile_array.y * TILE_SIZE_Y) + (TILE_SIZE_Y / 2);

	field_player.speed = 0; //�v���C���[�X�s�[�h

	//////
	image_change_time = 0; //�摜�؂�ւ�����
	draw_player_image_index = 0; //�\������摜�̔z��ԍ�
	encount_rate = -SAFE_ENCOUNT_STEP; //�G���J�E���g���Ȃ�����

	//�G���J�E���g�A�j���[�V�����ϐ�
	encount_blinking_count = 0;//��ʂ��_�ł�����
	encount_blinking_time_interval = 0;//��ʂ̓_�Ŏ���
	is_encount_blinking = false;//��ʂ�_�ł����邩�H

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

	for (int i = 0; i < FIELD_TILE_NUM_Y; i++)
	{
		for (int j = 0; j < FIELD_TILE_NUM_X; j++)
		{
			tile[i][j].position.x = (j * TILE_SIZE_X) + (TILE_SIZE_X / 2);
			tile[i][j].position.y = (i * TILE_SIZE_Y) + (TILE_SIZE_Y / 2);
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
	//�G���J�E���g�����ꍇ
	if (encount_rate >= MAX_ENCOUNT_RATE)return EncountAnimation();
	
	//�G���J�E���g���Ă��Ȃ��ꍇ
	else
	{
		//�L�����̃A�j���[�V����

		if (++image_change_time > CHANGE_IMAGE_TIME)
		{
			image_change_time = 0;
			if (++draw_player_image_index > 3)draw_player_image_index = 0;
		}

		//�v���C���[���}�X�̏�Ŏ~�܂��Ă���ꍇ

		if ((field_player.position.x == tile[field_player.target_tile_array.y][field_player.target_tile_array.x].position.x) &&
			(field_player.position.y == tile[field_player.target_tile_array.y][field_player.target_tile_array.x].position.y))
		{

			//�G�ƃG���J�E���g���邩�H

			if (field_player.speed != 0)
			{
				field_player.speed = 0;

				if (++encount_rate > MAX_WALK_ENCOUNT_RATE)encount_rate = MAX_WALK_ENCOUNT_RATE;

				if (encount_rate > 0)
				{
					if (GetRand(MAX_ENCOUNT_RATE - encount_rate) == 0)encount_rate = MAX_ENCOUNT_RATE;
				}
			}

			//�v���C���[�ړ��i�}�X�P�ʂ̈ړ��j
			if(encount_rate != MAX_ENCOUNT_RATE)PlayerMovement();
		}

		//�v���C���[���}�X���X�N���[�����鏈��
		else PlayerScroll(); 

	}

    return -1;
}

void Field::PlayerMovement()
{
	I_VECTOR2 player_target_tile_array = field_player.target_tile_array;

	if (Key::KeyPressed(KEY_TYPE::UP))
	{
		field_player.target_tile_array.y = WrapAround(field_player.target_tile_array.y - 1, 0, FIELD_TILE_NUM_Y - 1), field_player.speed = -PLAYER_SPEED;
	}
	else if (Key::KeyPressed(KEY_TYPE::DOWN))
	{
		field_player.target_tile_array.y = WrapAround(field_player.target_tile_array.y + 1, 0, FIELD_TILE_NUM_Y - 1), field_player.speed = PLAYER_SPEED;
	}
	else if (Key::KeyPressed(KEY_TYPE::LEFT))
	{
		field_player.target_tile_array.x = WrapAround(field_player.target_tile_array.x - 1, 0, FIELD_TILE_NUM_X - 1), field_player.speed = -PLAYER_SPEED;
	}
	else if (Key::KeyPressed(KEY_TYPE::RIGHT))
	{
		field_player.target_tile_array.x = WrapAround(field_player.target_tile_array.x + 1, 0, FIELD_TILE_NUM_X - 1), field_player.speed = PLAYER_SPEED;
	}

	//�����蔻��
	if (tile[field_player.target_tile_array.y][field_player.target_tile_array.x].type >= 17)
	{
		field_player.target_tile_array = player_target_tile_array;
		field_player.speed = 0;
	}
}

void Field::PlayerScroll()
{
	if (field_player.position.x != tile[field_player.target_tile_array.y][field_player.target_tile_array.x].position.x)
	{
		field_player.position.x = WrapAround(field_player.position.x + field_player.speed, 0, (FIELD_TILE_NUM_X * TILE_SIZE_X) - 1);
	}
	else
	{
		field_player.position.y = WrapAround(field_player.position.y + field_player.speed, 0, (FIELD_TILE_NUM_Y * TILE_SIZE_Y) - 1);
	}
}

int Field::EncountAnimation()
{
	if (++encount_blinking_time_interval > ENCOUNT_BLINKING_TIME_INTERVAL)
	{
		is_encount_blinking = false;

		if (encount_blinking_time_interval > (ENCOUNT_BLINKING_TIME_INTERVAL * 2))
		{
			
			is_encount_blinking = true;
			encount_blinking_time_interval = 0;
			
			if (++encount_blinking_count == ENCOUNT_BLINKING_COUNT)
			{
				encount_rate = -SAFE_ENCOUNT_STEP;
				encount_blinking_count = 0;
				is_encount_blinking = false;
				return tile[field_player.target_tile_array.y][field_player.target_tile_array.x].enemy_rank;
			}
		}
	}

	return -1;
}

void Field::Draw() const
{
	for (int i = 0; i < DRAW_TILE_NUM_Y; i++)//�c�̌J��Ԃ�
	{
		for (int j = 0; j < DRAW_TILE_NUM_X; j++)//���̌J��Ԃ�
		{
			int draw_tile_array_x = WrapAround(field_player.target_tile_array.x - (DRAW_TILE_NUM_X / 2) + j, 0, FIELD_TILE_NUM_X - 1);
			int draw_tile_array_y = WrapAround(field_player.target_tile_array.y - (DRAW_TILE_NUM_Y / 2) + i, 0, FIELD_TILE_NUM_Y - 1);

			int x = WrapAround(tile[draw_tile_array_y][draw_tile_array_x].position.x - field_player.position.x + HALF_SCREEN_SIZE, -(TILE_SIZE_X / 2), tile[FIELD_TILE_NUM_Y - 1][FIELD_TILE_NUM_X - 1].position.x - 1);
			int y = WrapAround(tile[draw_tile_array_y][draw_tile_array_x].position.y - field_player.position.y + HALF_SCREEN_SIZE, -(TILE_SIZE_Y / 2), tile[FIELD_TILE_NUM_Y - 1][FIELD_TILE_NUM_X - 1].position.y - 1);

			DrawRotaGraph(x, y, 3, 0, tile_image[tile[draw_tile_array_y][draw_tile_array_x].type], FALSE);
		}
	}

	DrawRotaGraph(HALF_SCREEN_SIZE, HALF_SCREEN_SIZE, 2, 0, player_image[1][draw_player_image_index], TRUE);
	//DrawFormatString(0, 20, 0xffffff, "HP = %d", player->GetHp());

	//�_�ł̕\��
	if (is_encount_blinking)DrawBox(0, 0, SCREEN_SIZE, SCREEN_SIZE, 0xffffff, TRUE);
}