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

	image_index_change_time = 0.0f;
	image_index = 0;
	add_image_index = 1;

	SetMap();

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
				if (npc_count == 0)
				{
					npc[0] = new NpcBase(tile[i][j].location, VECTOR2_I{ j,  i }, npc_image + (12 * (npc_data - 3)), "＊「ひがしの どうくつだぞ。");
					npc[0]->SetCanMove(false);
					npc[0]->SetImageDirectionIndex(1);
				}
				else if (npc_count == 1)
				{
					npc[1] = new NpcBase(tile[i][j].location, VECTOR2_I{ j,  i }, npc_image + (12 * (npc_data - 3)), "＊「おみせは じゅんびちゅう です。");
					npc[1]->SetCanMove(false);
					npc[1]->SetImageDirectionIndex(1);
				}
				else if (npc_count == 2)
				{
					npc[2] = new NpcBase(tile[i][j].location, VECTOR2_I{ j,  i }, npc_image + (12 * (npc_data - 3)), "＊「ここは エルムの むらです。");
					npc[2]->SetImageDirectionIndex(1);
				}
				else if (npc_count == 3)
				{
					npc[3] = new NpcBase(tile[i][j].location, VECTOR2_I{ j,  i }, npc_image + (12 * (npc_data - 3)), "＊「おみせは じゅんびちゅう です。");
					npc[3]->SetCanMove(false);
					npc[3]->SetImageDirectionIndex(2);
				}
				else if (npc_count == 4)
				{
					npc[4] = new NpcBase(tile[i][j].location, VECTOR2_I{ j,  i }, npc_image + (12 * (npc_data - 3)), "＊「ぼくのあいする ハニーに\n　 もう ふつかも あってないよ…\n");
					npc[4]->SetImageDirectionIndex(1);
				}

				npc_count++;
			}

		}
	}

	char message[1000];
	sprintf_s(message, sizeof(message), "＊「おお %s！ よくきてくれた！\n\n\n＊「おまえも しっているだろうが\n　 さいきん むらのひとが\n　 つぎつぎと いなくなっておる…\n＊「ひがしのどうくつが あやしいとおもうのだが\n 　なにが おきているか しらべてきてくれんか？\n", player->GetName());
	this->message = new Message(message);
}

void TownMap::Initialize()
{
	player->SetLocation(tile[START_PLAYER_LOCATION_Y][START_PLAYER_LOCATION_X].location);
	player->SetLocationIndex(VECTOR2_I{ START_PLAYER_LOCATION_X,  START_PLAYER_LOCATION_Y });

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

	if (message == nullptr)
	{
		VECTOR2_I player_location_index = player->UpdateLocationIndex();

		if (player->UpdateMovement(player_location_index, CheckHitObject(player->GetLocationIndex(), -1),
			tile[player->GetLocationIndex().y][player->GetLocationIndex().x].location))
		{
			if (town_map_data[player->GetLocationIndex().y][player->GetLocationIndex().x][1] == '0')return GAME_SCENE_TYPE::WORLD_MAP;
		}

		for (int i = 0; i < 10; i++)
		{
			if (npc[i] != nullptr)
			{
				VECTOR2_I npc_location_index = npc[i]->GetLocationIndex();

				if (npc[i]->Update(delta_time))
				{
					npc[i]->UpdateLocationIndex();
				}

				npc[i]->UpdateMovement(npc_location_index, CheckHitObject(npc[i]->GetLocationIndex(), i),
					tile[npc[i]->GetLocationIndex().y][npc[i]->GetLocationIndex().x].location);
			}
		}

		if (Key::KeyDown(KEY_TYPE::A))SetMessage();

	}
	else
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

	VECTOR2_I player_direction_index = player->GetDirectionIndex();

	if (tile[player_direction_index.y][player_direction_index.x].type == 23)
	{
		if (player->GetImageDirectionIndex() == 0)player_direction_index.y--;
		else if (player->GetImageDirectionIndex() == 1)player_direction_index.y++;
		else if (player->GetImageDirectionIndex() == 2)player_direction_index.x--;
		else if (player->GetImageDirectionIndex() == 3)player_direction_index.x++;
	}

	for (int i = 0; i < 10; i++)
	{
		if (npc[i] != nullptr)
		{
			if (npc[i]->GetLocationIndex()== player_direction_index)
			{
				if (player->GetImageDirectionIndex() == 0)npc[i]->SetImageDirectionIndex(1);
				else if (player->GetImageDirectionIndex() == 1)npc[i]->SetImageDirectionIndex(0);
				else if (player->GetImageDirectionIndex() == 2)npc[i]->SetImageDirectionIndex(3);
				else if (player->GetImageDirectionIndex() == 3)npc[i]->SetImageDirectionIndex(2);

				message = new Message(npc[i]->GetNpcMessage());
				break;
			}
		}
	}

	
}

bool TownMap::CheckHitObject(VECTOR2_I character_location_index, int npc_index)
{
	for (int i = 0; i < 10; i++)
	{
		if (npc[i] != nullptr)
		{
			if (npc_index != -1)
			{
				if (player->GetLocationIndex() == character_location_index)return true;
			}
			if (i != npc_index)
			{
				if (npc[i]->GetLocationIndex() == character_location_index)return true;
			}
		}
	}

	return (tile[character_location_index.y][character_location_index.x].type >= COLLIDE_TILE_TYPE);
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

	DrawFormatString(0, 30, 0xffffff, "%d = x, %d = y", player->GetLocation().x, player->GetLocation().y);
	DrawFormatString(0, 50, 0xffffff, "%d = x, %d = y", player->GetLocationIndex().x, player->GetLocationIndex().y);
	char moji = '0';
	DrawFormatString(0, 70, 0xffffff, "%d", moji);

	for (int i = 0; i < 10; i++)
	{
		if (npc[i] != nullptr)npc[i]->Draw(VECTOR2_I{ -player->GetLocation().x + HALF_SCREEN_SIZE,  -player->GetLocation().y + HALF_SCREEN_SIZE }, image_index);
	}

	DrawBox(5 , 50 , 525 , 130 , 0xffffff, TRUE);
	DrawBox(10 , 55 , 520 , 125 , 0x000000, TRUE);

	DrawFormatStringToHandle(25, 55, 0xffffff, retro_font_48, "%s  HP %3d MP %3d", player->GetName(), player->GetHp(), player->GetMp());


	if (message != nullptr)message->Draw();
}