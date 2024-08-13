#include"DxLib.h"
#include"FieldBase.h"

FieldBase::FieldBase()
{
    OutputDebugString("FieldBase�R���X�g���N�^�Ă΂�܂����B\n");
}

FieldBase::~FieldBase()
{
    OutputDebugString("FieldBase�f�X�g���N�^���Ă΂�܂����B\n");
}

void FieldBase::Initialize(class PlayerManager* player_manager, class EnemyManager* enemy_manager, class AttackManager* attack_manager, class EventManager* event_manager)
{
    this->player_manager = player_manager;
    this->enemy_manager = enemy_manager;
    this->attack_manager = attack_manager;
    this->event_manager = event_manager;
}