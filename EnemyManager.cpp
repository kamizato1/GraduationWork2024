#include"DxLib.h"
#include"EnemyManager.h"
#include"EnemyBase.h"

EnemyManager::EnemyManager() : enemy(nullptr)
{
	if (LoadDivGraph("data/image/Battle/enemy1.png", 10, 10, 1, 120, 160, enemy_image[0]) == -1)throw("data/image/Battle/enemy1.pngが読み込めません\n");
	if (LoadDivGraph("data/image/Battle/enemy2.png", 10, 10, 1, 120, 160, enemy_image[1]) == -1)throw("data/image/Battle/enemy2.pngが読み込めません\n");
	if (LoadDivGraph("data/image/Battle/enemy3.png", 10, 10, 1, 120, 160, enemy_image[2]) == -1)throw("data/image/Battle/enemy3.pngが読み込めません\n");

	Initialize(0);

	OutputDebugString("EnemyManagerコンストラクタ呼ばれました。\n");
}

EnemyManager::~EnemyManager()
{
	delete enemy;

	for (int i = 0; i < ENEMY_PER_RANK; i++)
	{
		for(int j = 0; j < ENEMY_MAX_RANK; j++)DeleteGraph(enemy_image[i][j]);
	}

	OutputDebugString("EnemyManagerデストラクタ呼ばれました。\n");
}

void EnemyManager::Initialize(int encount_enemy_rank)
{
	if (enemy != nullptr)delete enemy;
	int enemy_type = GetRand(ENEMY_PER_RANK - 1);
	this->enemy = new EnemyBase(enemy_data[enemy_type][encount_enemy_rank], enemy_image[enemy_type][encount_enemy_rank]);
}

int EnemyManager::EnemyNum()const
{
	return 1;
}

const char* EnemyManager::GetEnemyName(int enemy_num)const
{
	return enemy->GetName();
}

int EnemyManager::HitAttack(int enemy_num, int attack_power)
{
	return enemy->HitAttack(attack_power);
}

bool EnemyManager::Update(float delta_time)
{
	return true;
}

void EnemyManager::Draw() const
{


	enemy->Draw();

	//DrawFormatString(100, 0, 0xffffff, "%s", enemy->GetName());
}