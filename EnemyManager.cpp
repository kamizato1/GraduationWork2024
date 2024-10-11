#include"DxLib.h"
#include"EnemyManager.h"
#include"EnemyBase.h"

EnemyManager::EnemyManager() : enemy(nullptr)
{
	if (LoadDivGraph("image/Battle/enemy1.png", 10, 10, 1, 120, 160, enemy_image[0]) == -1)throw("image/Battle/enemy1.pngが読み込めません\n");
	if (LoadDivGraph("image/Battle/enemy2.png", 10, 10, 1, 120, 160, enemy_image[1]) == -1)throw("image/Battle/enemy2.pngが読み込めません\n");
	if (LoadDivGraph("image/Battle/enemy3.png", 10, 10, 1, 120, 160, enemy_image[2]) == -1)throw("image/Battle/enemy3.pngが読み込めません\n");

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

std::string EnemyManager::Initialize(int encount_enemy_rank)
{
	if (enemy != nullptr)delete enemy;
	int enemy_type = GetRand(ENEMY_PER_RANK - 1);
	this->enemy = new EnemyBase(enemy_data[enemy_type][encount_enemy_rank].name, enemy_data[enemy_type][encount_enemy_rank].hp, enemy_data[enemy_type][encount_enemy_rank].mp,
		enemy_data[enemy_type][encount_enemy_rank].attack_power, enemy_data[enemy_type][encount_enemy_rank].defense_power, enemy_data[enemy_type][encount_enemy_rank].speed, enemy_image[enemy_type][encount_enemy_rank]);

	return enemy->GetName();
}

bool EnemyManager::Update(float delta_time)
{
	return true;
}

void EnemyManager::Draw() const
{

	enemy->Draw();

	DrawFormatString(100, 0, 0xffffff, "%s", enemy->GetName());
}