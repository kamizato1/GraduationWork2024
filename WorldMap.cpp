#include"DxLib.h"
#include"WorldMap.h"
#include"NpcBase.h"
#include"Player.h"

#define COLLIDE_TILE_TYPE 25//ぶつかるタイル

#define START_PLAYER_LOCATION_X 12
#define START_PLAYER_LOCATION_Y 107

#define MAX_ENCOUNT_RATE 10 //最大エンカウント率(割合)
#define MAX_WALK_ENCOUNT_RATE 7 //歩いているとき上がる最大エンカウント率（割合）
#define SAFE_ENCOUNT_STEP 5 //エンカウントしない歩数

#define SCREEN_BLINKING_TIME 0.08f //画面点滅時間
#define SCREEN_BLINKING_COUNT 5 //画面点滅回数


WorldMap::WorldMap(Player* player) : MapBase(player)
{
	if (LoadDivGraph("data/WorldMap/tile.png", TILE_TYPE_NUM, TILE_TYPE_NUM, 1, 16, 16, tile_image) == -1)throw("data/WorldMap/tile.pngが読み込めません\n");
	
	SetMap();

	Initialize();

    OutputDebugString("WorldMapコンストラクタ呼ばれました。\n");

	//SetFontSize(15);
}

void WorldMap::SetMap()
{
	FILE* map_data = nullptr;//フィールド読み込み

	errno_t error_field_data = fopen_s(&map_data, "data/WorldMap/map_data.txt", "r");
	if (error_field_data != 0)throw("data/WorldMap/map_data.txtが読み込めません\n");//エラーチェック

	for (int i = 0; i < TILE_NUM; i++)
	{
		for (int j = 0; j < TILE_NUM; j++)
		{
			tile[i][j].location.x = (j * TILE_SIZE) + (TILE_SIZE / 2);
			tile[i][j].location.y = (i * TILE_SIZE) + (TILE_SIZE / 2);

			char c_map_data[4];
			fscanf_s(map_data, "%2s ", c_map_data, 3);

			char set_c_map_data = c_map_data[0];
			tile[i][j].type = strtol(&set_c_map_data, NULL, 36);

			set_c_map_data = c_map_data[1];
			tile[i][j].enemy_rank = strtol(&set_c_map_data, NULL, 36);
		}
	}

	fclose(map_data);

	player_location = tile[START_PLAYER_LOCATION_Y][START_PLAYER_LOCATION_X].location;
	player_location_index = VECTOR2_I{ START_PLAYER_LOCATION_X,  START_PLAYER_LOCATION_Y };

}

void WorldMap::Initialize()
{
	player->SetLocation(player_location);
	player->SetLocationIndex(player_location_index);

	image_index_change_time = 0.0f;
	image_index = 0;
	add_image_index = 1;

	update_encount_animation = false;
	encount_rate = -SAFE_ENCOUNT_STEP;
	screen_blinking_time = 0.0f;
	screen_blinking_count = 0;
}

WorldMap::~WorldMap()
{
    OutputDebugString("WorldMapデストラクタが呼ばれました。\n");
}


GAME_SCENE_TYPE WorldMap::Update(float delta_time)
{
	//エンカウントアニメーション
	if (update_encount_animation)
	{
		if (UpdateEncountAnimation(delta_time))return GAME_SCENE_TYPE::BATTLE;
	}
	else
	{
		UpdateImageIndex(delta_time);

		VECTOR2_I player_location_index = player->UpdateLocationIndex();

		if (player->UpdateMovement(player_location_index, (tile[player_location_index.y][player_location_index.x].type >= COLLIDE_TILE_TYPE),
			tile[player->GetLocationIndex().y][player->GetLocationIndex().x].location))
		{
			if ((tile[player->GetLocationIndex().y][player->GetLocationIndex().x].type == 15) || (tile[player->GetLocationIndex().y][player->GetLocationIndex().x].type == 16))
			{

				player_location = tile[player->GetLocationIndex().y + 1][player->GetLocationIndex().x].location;
				this->player_location_index = { player->GetLocationIndex().x, player->GetLocationIndex().y + 1 };

				return GAME_SCENE_TYPE::TOWN_MAP;
			}
			else if (++encount_rate > 0)
			{
				if (encount_rate > MAX_WALK_ENCOUNT_RATE)encount_rate = MAX_WALK_ENCOUNT_RATE;
				if (GetRand(MAX_ENCOUNT_RATE - encount_rate) == 0)update_encount_animation = true;
			}
		}
	}

    return GAME_SCENE_TYPE::WORLD_MAP;
}

bool WorldMap::UpdateEncountAnimation(float delta_time)
{
	if ((screen_blinking_time += delta_time) >  SCREEN_BLINKING_TIME)
	{
		screen_blinking_time = 0.0f;

		if (++screen_blinking_count > (SCREEN_BLINKING_COUNT * 2) - 1)
		{
			player_location = player->GetLocation();
			player_location_index = player->GetLocationIndex();
			return true;
		}
	}

	return false;
}

int WorldMap::GetTileType()const
{
	return tile[player->GetLocationIndex().y][player->GetLocationIndex().x].type;
}

int WorldMap::GetEnemyRank()const
{
	return tile[player->GetLocationIndex().y][player->GetLocationIndex().x].enemy_rank;
}

void WorldMap::Draw() const
{
	for (int i = 0; i < DRAW_TILE_NUM; i++)//縦の繰り返し
	{
		for (int j = 0; j < DRAW_TILE_NUM; j++)//横の繰り返し
		{
			int draw_tile_array_x = player->GetLocationIndex().x - (DRAW_TILE_NUM / 2) + j;
			int draw_tile_array_y = player->GetLocationIndex().y - (DRAW_TILE_NUM / 2) + i;

			int draw_tile_location_x = tile[draw_tile_array_y][draw_tile_array_x].location.x - player->GetLocation().x + HALF_SCREEN_SIZE;
			int draw_tile_location_y = tile[draw_tile_array_y][draw_tile_array_x].location.y - player->GetLocation().y + HALF_SCREEN_SIZE;

			if ((draw_tile_array_y < 0) || (draw_tile_array_y >= TILE_NUM) || (draw_tile_array_x < 0) || (draw_tile_array_x >= TILE_NUM))
			{
				DrawRotaGraph(draw_tile_location_x, draw_tile_location_y, 3, 0, tile_image[0], FALSE);
			}
			else DrawRotaGraph(draw_tile_location_x, draw_tile_location_y, 3, 0, tile_image[tile[draw_tile_array_y][draw_tile_array_x].type], FALSE);

			//DrawFormatString((j * TILE_SIZE) - (TILE_SIZE / 2) + add_x - 20, i * TILE_SIZE - (TILE_SIZE / 2) + add_y, 0xffffff, "%d", tile[draw_tile_array_y][draw_tile_array_x].enemy_rank);
		}
	}

	player->Draw(image_index);

	DrawBox(5, 50, 525, 130, 0xffffff, TRUE);
	DrawBox(10, 55, 520, 125, 0x000000, TRUE);
	//DrawFormatStringToHandle(25, 55, 0xffffff, retro_font_48, "%s  HP %3d MP %3d", player->GetName(), player->GetHp(), /*player->GetMp()*/encount_rate);

	DrawFormatString(0, 30, 0xffffff, "%d", encount_rate);
	DrawFormatString(0, 50, 0xffffff, "%d = x, %d = y", player->GetLocationIndex().x, player->GetLocationIndex().y);


	//点滅の表示
	if (screen_blinking_count % 2)DrawBox(0, 0, SCREEN_SIZE, SCREEN_SIZE, 0xffffff, TRUE);
}