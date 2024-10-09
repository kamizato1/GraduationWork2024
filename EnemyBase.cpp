#include"DxLib.h"
#include"EnemyBase.h"
#include"define.h"

EnemyBase::EnemyBase(const std::string& name, int hp, int mp, int attack_power, int defense_power, int speed, int enemy_image) :
	CharacterBase(name, hp, mp, attack_power, defense_power, speed), enemy_image(enemy_image)
{
	OutputDebugString("EnemyBase�R���X�g���N�^�Ă΂�܂����B\n");
}

EnemyBase::~EnemyBase()
{
	OutputDebugString("EnemyBase�f�X�g���N�^�Ă΂�܂����B\n");
}

bool EnemyBase::Update(float delta_time)
{
	return false;
}

void EnemyBase::Draw() const
{
	DrawRotaGraph(HALF_SCREEN_SIZE_X, 300, 2.5, 0, enemy_image, TRUE);
}