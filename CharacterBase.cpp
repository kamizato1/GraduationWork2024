#include"DxLib.h"
#include"CharacterBase.h"

CharacterBase::CharacterBase(F_VECTOR2 array_location, F_VECTOR2 block_size) : ObjectBase(array_location, block_size)
{
    OutputDebugString("CharacterBaseコンストラクタ呼ばれました。\n");
}

void CharacterBase::SetPointer(class Stage* stage, class PlayerManager* player_manager, class EnemyManager* enemy_manager, class AttackManager* attack_manager)
{
    this->stage = stage;
    this->player_manager = player_manager;
    this->enemy_manager = enemy_manager;
    this->attack_manager = attack_manager;
}

CharacterBase::~CharacterBase()
{
    OutputDebugString("CharacterBaseデストラクタが呼ばれました。\n");
}


//-----------------------------------
//キャラクター間の距離を測る
//-----------------------------------
float CharacterBase::CalculateDistance(DATA target_location)const
{
    float dx = target_location.x - location.x;
    float dy = target_location.y - location.y;
    return (float)sqrt(dx * dx + dy * dy); // ユークリッド距離の計算（平方根を取る）
}

