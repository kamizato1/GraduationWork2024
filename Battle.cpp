#include"DxLib.h"
#include"Battle.h"
#include"Player.h"
#include"EnemyManager.h"

#include"Key.h"

Battle::Battle(Player* player) : player(player)
{
	enemy_manager = new EnemyManager();

	if (LoadDivGraph("image/Battle/scenery.png", 12, 1, 12, 720, 96, scenery_image) == -1)throw("image/Battle/scenery.pngが読み込めません\n");

	Initialize(0);

	OutputDebugString("Battleコンストラクタ呼ばれました。\n");
}

Battle::~Battle()
{
	delete enemy_manager;

	OutputDebugString("Battleデストラクタ呼ばれました。\n");
}

void Battle::Initialize(int encount_enemy_rank)
{
	image_transparency = 0;
	wait_time = 0.0f;
	enemy_manager->Initialize(encount_enemy_rank);
}

bool Battle::Update(float delta_time)
{
	if (image_transparency == 255)
	{

	}
	else if ((image_transparency += 5) > 255)image_transparency = 255;

	if ((wait_time += delta_time) > 4.0f)return true;

	return false;
}

bool Battle::EncountAnimation()
{
	return false;
}

void Battle::Draw() const
{
	DrawFormatString(0, 100, 0xffffff, "%f", wait_time);
	DrawFormatString(0, 40, 0xffffff, "%d", player->GetMp());

	if(image_transparency != 255)SetDrawBlendMode(DX_BLENDMODE_ALPHA, image_transparency);

	DrawGraph(0, 0, scenery_image[0], TRUE);

	enemy_manager->Draw();

	DrawBox(0, 500, 720, 720, 0xffffff, TRUE);
	DrawBox(5, 505, 715, 715, 0x000000, TRUE);
	
	if (image_transparency != 255)SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	
}