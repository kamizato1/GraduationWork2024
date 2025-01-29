#include"DxLib.h"
#include"MapBase.h"
#include"Player.h"
#include"NpcBase.h"
#include"Key.h"

#define IMAGE_INDEX_CHANGE_TIME 0.2f //�摜�؂�ւ�����
#define IMAGE_INDEX 3 //�v���C���[�摜�z��

#define PLAYER_SPEED 2 //�v���C���[�̈ړ����x


MapBase::MapBase(Player* player)
{
	this->player = player;
	
	//�t�H���g�̓ǂݍ���
	retro_font_48 = LoadFontDataToHandle("data/font/DragonQuestFont48.dft", 0);

	//�ϐ�
	image_index_change_time = 0.0f;
	image_index = 0;
	add_image_index = 1;

	OutputDebugString("MapBase�R���X�g���N�^�Ă΂�܂����B\n");
}

MapBase::~MapBase()
{
	OutputDebugString("MapBase�f�X�g���N�^���Ă΂�܂����B\n");
}

void MapBase::UpdateImageIndex(float delta_time)
{
	if ((image_index_change_time += delta_time) > IMAGE_INDEX_CHANGE_TIME)
	{
		image_index += add_image_index;
		if ((image_index == 0) || (image_index == IMAGE_INDEX - 1))add_image_index *= -1;
		image_index_change_time = 0.0f;
	}
}