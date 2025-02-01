#include"DxLib.h"
#include"TownMap.h"
#include"Player.h"
#include"Message.h"
#include"Key.h"

#define COLLIDE_TILE_TYPE 9

#define START_PLAYER_LOCATION_X 31
#define START_PLAYER_LOCATION_Y 45

TownMap::TownMap(Player* player) : MapBase(player)
{
	if (LoadDivGraph("data/TownMap/tile.png", TILE_TYPE_NUM, TILE_TYPE_NUM, 1, 16, 16, tile_image) == -1)throw("data/image/TownMap/tile.pngが読み込めません\n");
	if (LoadDivGraph("data/TownMap/npc2.png", 252, 12, 21, 16, 16, npc_image) == -1)throw("data/TownMap/npc1.pngが読み込めません\n");

	message = nullptr;

	SetMap();

	Initialize();

	OutputDebugString("TownMapコンストラクタ呼ばれました。\n");
}

void TownMap::SetMap()
{
	for (int i = 0; i < 10; i++)npc[i] = nullptr;
	int npc_count = 0;

	for (int i = 0; i < TILE_NUM; i++)
	{
		for (int j = 0; j < TILE_NUM; j++)
		{
			tile[i][j].location.x = (j * TILE_SIZE) + (TILE_SIZE / 2);
			tile[i][j].location.y = (i * TILE_SIZE) + (TILE_SIZE / 2);

			char set_c_map_data = town_map_data[i][j][0];
			tile[i][j].type = strtol(&set_c_map_data, NULL, 36);

			set_c_map_data = town_map_data[i][j][1];
			int npc_data = strtol(&set_c_map_data, NULL, 36);

			if (npc_data == 0){}
			else if (npc_data == 1){}
			else if (npc_data == 2)
			{
				player->SetLocation(tile[i][j].location);
				player->SetLocationIndex(VECTOR2_I{ j,  i });
			}
			else if (npc_count < 10)
			{
				npc[npc_count] = new NpcBase(tile[i][j].location, VECTOR2_I{ j,  i }, npc_image + (12 * (npc_data - 3)), "＊「ここは ローデンの むらです。\nみなさん\nきょうは\nいいてんき\nですね。");
				npc_count++;
			}

		}
	}
}

void TownMap::Initialize()
{
	player->SetLocation(tile[START_PLAYER_LOCATION_Y][START_PLAYER_LOCATION_X].location);
	player->SetLocationIndex(VECTOR2_I{ START_PLAYER_LOCATION_X,  START_PLAYER_LOCATION_Y });

	/*if (message != nullptr)
	{
		delete message;
		message = nullptr;
	}*/

	image_index_change_time = 0.0f;
	image_index = 0;
	add_image_index = 1;
}

TownMap::~TownMap()
{
	OutputDebugString("TownMapデストラクタが呼ばれました。\n");
}


GAME_SCENE_TYPE TownMap::Update(float delta_time)
{
	UpdateImageIndex(delta_time);

	if (player->UpdateScroll(tile[player->GetLocationIndex().y][player->GetLocationIndex().x].type, COLLIDE_TILE_TYPE,
		player->UpdateMovement(tile[player->GetLocationIndex().y][player->GetLocationIndex().x].location),
		tile[player->GetLocationIndex().y][player->GetLocationIndex().x].location))
	{
		if (town_map_data[player->GetLocationIndex().y][player->GetLocationIndex().x][1] == '0')return GAME_SCENE_TYPE::WORLD_MAP;
	}

	if (Key::KeyDown(KEY_TYPE::A))SetMessage();

	for (int i = 0; i < 10; i++)
	{
		if (npc[i] != nullptr)
		{
			VECTOR2_I npc_location_index = npc[i]->GetLocationIndex();

			if (npc[i]->Update(delta_time))
			{
				npc[i]->UpdateMovement(tile[npc[i]->GetLocationIndex().y][npc[i]->GetLocationIndex().x].location);
			}

			npc[i]->UpdateScroll(tile[npc[i]->GetLocationIndex().y][npc[i]->GetLocationIndex().x].type, COLLIDE_TILE_TYPE,
				npc_location_index,
				tile[npc[i]->GetLocationIndex().y][npc[i]->GetLocationIndex().x].location);
		}
	}

	if (message != nullptr)
	{
		if (message->Update(delta_time))
		{
			delete message;
			message = nullptr;
		}
	}

	return GAME_SCENE_TYPE::TOWN_MAP;
}

void TownMap::SetMessage()
{

	for (int i = 0; i < 10; i++)
	{
		if (npc[i] != nullptr)
		{
			if ((npc[i]->GetLocationIndex().x == player->GetDirectionIndex().x) &&
				(npc[i]->GetLocationIndex().y == player->GetDirectionIndex().y))
			{
				message = new Message(npc[i]->GetNpcMessage());
				break;
			}
		}
	}
}

void TownMap::Draw() const
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

	DrawFormatString(0, 30, 0xffffff, "%d = x, %d = y", npc[0]->GetLocation().x, npc[0]->GetLocation().y);
	DrawFormatString(0, 50, 0xffffff, "%d = x, %d = y", npc[0]->GetLocationIndex().x, npc[0]->GetLocationIndex().y);
	char moji = '0';
	DrawFormatString(0, 70, 0xffffff, "%d", moji);

	if(message != nullptr)message->Draw();

	for (int i = 0; i < 10; i++)
	{
		if (npc[i] != nullptr)npc[i]->Draw(VECTOR2_I{ -player->GetLocation().x + HALF_SCREEN_SIZE,  -player->GetLocation().y + HALF_SCREEN_SIZE }, image_index);
	}
}