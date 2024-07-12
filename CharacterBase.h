#pragma once
#include"ObjectBase.h"

class CharacterBase : public ObjectBase
{
protected:
    class BattleField* battle_field;
    class PlayerManager* player_manager;
    class EnemyManager* enemy_manager;
    class AttackManager* attack_manager;

public:
    CharacterBase(F_VECTOR2 array_location, F_VECTOR2 block_size);
    ~CharacterBase();
};