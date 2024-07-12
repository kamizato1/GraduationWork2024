#include"DxLib.h"
#include"Bird.h"
#include"Stage.h"

#define BIRD_SIZE_X 9.5f//�T�C�Y
#define BIRD_SIZE_Y 9.5f//�T�C�Y

#define IMAGE_CHANGE_TIME 0.2f

#define MAX_HP 10

#define WALK_SPEED 1.5f//1�t���[���̍ő呬
#define ACCELERATION 0.1f//�ړ����̉���

#define ATTACK_SPEED 7.5f  //�㏸�A���~�̏��

#define SEARCH_RANGE 300.0f //��틗��


//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
Bird::Bird(DATA location, int enemy_image[ENEMY_STATE::END][5], class Stage* stage, class PlayerManager* player_manager, class AttackManager* attack_manager) :
EnemyBase(location, { BIRD_SIZE_X , BIRD_SIZE_Y }, MAX_HP, 5, 5, enemy_image),
attack_speed(0.0f), target_location({0.0f, 0.0f}), begin_attack_location({0.0f, 0.0f})
{
	this->stage = stage;
	this->player_manager = player_manager;
	this->attack_manager = attack_manager;

	OutputDebugString("Bird�R���X�g���N�^�Ă΂�܂����B\n");
}

//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
Bird::~Bird()
{
	OutputDebugString("Bird�f�X�g���N�^���Ă΂�܂����B\n");
}


//-----------------------------------
// �X�V����
//-----------------------------------
void Bird::Update(float delta_time)
{
	//��Ԃ��Ƃ̏���

	enemy_control_time += delta_time;

	if ((image_change_time += delta_time) > IMAGE_CHANGE_TIME)
	{
		if (enemy_image[GetEnemyState()][++draw_image_num] == NULL)draw_image_num = 0;
		image_change_time = 0.0f;
	}

	switch (GetEnemyState())
	{
	case ENEMY_STATE::NORMAL:

		if (ScopeoOfActivity())
		{
			is_facing_left = !is_facing_left;
			speed = { 0.0f, 0.0f };
		}

		if (is_facing_left)
		{
			if ((speed.x -= ACCELERATION) < WALK_SPEED)speed.x = -WALK_SPEED;
		}
		else if ((speed.x += ACCELERATION) > WALK_SPEED)speed.x = WALK_SPEED;

		if (enemy_control_time > 5.0f)
		{
			target_location = player_manager->GetPlayerData()->GetLocation();

			if (CalculateDistance(target_location) < SEARCH_RANGE)
			{
				if (((is_facing_left) && (target_location.x < location.x)) ||
					((!is_facing_left) && (target_location.x > location.x)))
				{
					SetEnemyState(ENEMY_STATE::PREPARING_ATTACK);
					begin_attack_location = location;
				}
			}
		}

		break;

	case ENEMY_STATE::PREPARING_ATTACK:

		if (enemy_control_time > 1.0f)SetEnemyState(ENEMY_STATE::ATTACK);
		
		break;

	case ENEMY_STATE::ATTACK:

		speed = TargetTracking(target_location, attack_speed);

		if ((attack_speed += ACCELERATION) > ATTACK_SPEED)attack_speed = ATTACK_SPEED;

		if ((player_manager->CheckHitDamage(this, 5)) || (CalculateDistance(target_location) < 5))
		{
			SetEnemyState(ENEMY_STATE::AFTER_ATTACK);
			is_facing_left = !is_facing_left;
			attack_speed = 0.0f;
		}

		break;

	case ENEMY_STATE::AFTER_ATTACK:

		speed = TargetTracking(begin_attack_location, attack_speed);

		if ((attack_speed += ACCELERATION) > ATTACK_SPEED)attack_speed = ATTACK_SPEED;

		if (CalculateDistance(begin_attack_location) < 5)
		{
			SetEnemyState(ENEMY_STATE::NORMAL);
			attack_speed = 0.0f;
		}

		break;

	default:
		break;
	}

	//X���W�X�V

	location.x += speed.x;

	if (stage->HitBlock(this))
	{
		if (GetEnemyState() == ENEMY_STATE::ATTACK)
		{
			SetEnemyState(ENEMY_STATE::AFTER_ATTACK);
			attack_speed = 0.0f;
		}
		is_facing_left = !is_facing_left;
		location.x -= speed.x;
	}

	//Y���W�X�V

	location.y += speed.y;

	if (stage->HitBlock(this))
	{
		if (GetEnemyState() == ENEMY_STATE::ATTACK)
		{
			SetEnemyState(ENEMY_STATE::AFTER_ATTACK);
			is_facing_left = !is_facing_left;
			attack_speed = 0.0f;
		}
		location.y -= speed.y;
	}
}

//-----------------------------------
// �`��
//-----------------------------------
void Bird::Draw(DATA draw_location) const
{
	DrawRotaGraph(draw_location.x, draw_location.y, 1, 0, enemy_image[GetEnemyState()][draw_image_num], TRUE, !is_facing_left);

	//DrawFormatString(draw_location.x, draw_location.y - 100, 0xffffff, "	�p�x =%f", angle);
	DrawBox(draw_location.x - radius.x, draw_location.y - radius.y, draw_location.x + radius.x, draw_location.y + radius.y, 0x00ffff, FALSE);
}