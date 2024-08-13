#pragma once

class FieldBase
{
protected:
    class PlayerManager* player_manager;
    class EnemyManager* enemy_manager;
    class AttackManager* attack_manager;
    class EventManager* event_manager;

    virtual void SetField() = 0;//�t�B�[���h�𐶐�

public:
    FieldBase();
    ~FieldBase();

    void Initialize(class PlayerManager* player_manager, class EnemyManager* enemy_manager, class AttackManager* attack_manager, class EventManager* event_manager);

    virtual bool Update(float delta_time) = 0;//�߂�l�����I
    virtual void Draw() const = 0;
};