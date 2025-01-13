#include"DxLib.h"
#include"EnemyManager.h"
#include"EnemyBase.h"

EnemyManager::EnemyManager()
{
	if (LoadDivGraph("data/image/Battle/enemy1.png", 10, 10, 1, 120, 160, enemy_image[0]) == -1)throw("data/image/Battle/enemy1.pngが読み込めません\n");
	if (LoadDivGraph("data/image/Battle/enemy2.png", 10, 10, 1, 120, 160, enemy_image[1]) == -1)throw("data/image/Battle/enemy2.pngが読み込めません\n");
	if (LoadDivGraph("data/image/Battle/enemy3.png", 10, 10, 1, 120, 160, enemy_image[2]) == -1)throw("data/image/Battle/enemy3.pngが読み込めません\n");

	OutputDebugString("EnemyManagerコンストラクタ呼ばれました。\n");
}

EnemyManager::~EnemyManager()
{
	for (int i = 0; i < ENEMY_PER_RANK; i++)
	{
		for(int j = 0; j < ENEMY_MAX_RANK; j++)DeleteGraph(enemy_image[i][j]);
	}

	OutputDebugString("EnemyManagerデストラクタ呼ばれました。\n");
}

CHARACTER_DATA EnemyManager::GetEnemyData(int encount_enemy_rank)const
{
	int enemy_type = GetRand(ENEMY_PER_RANK - 1);

	CHARACTER_DATA enemy_data = this->enemy_data[enemy_type][encount_enemy_rank];

	enemy_data.image = enemy_image[enemy_type][encount_enemy_rank];

	return enemy_data;

}