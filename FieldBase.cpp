#include"DxLib.h"
#include"FieldBase.h"

FieldBase::FieldBase()
{
    OutputDebugString("FieldBaseコンストラクタ呼ばれました。\n");
}

FieldBase::~FieldBase()
{
    OutputDebugString("FieldBaseデストラクタが呼ばれました。\n");
}

void FieldBase::Initialize(class PlayerManager* player_manager, class EnemyManager* enemy_manager, class AttackManager* attack_manager, class EventManager* event_manager)
{
    this->player_manager = player_manager;
    this->enemy_manager = enemy_manager;
    this->attack_manager = attack_manager;
    this->event_manager = event_manager;
}