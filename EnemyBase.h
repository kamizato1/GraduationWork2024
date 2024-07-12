#pragma once
#include"CombatCharacterBase.h"

class EnemyBase : public CombatCharacterBase
{
public:

	enum ENEMY_STATE//�G�̏��
	{
		NORMAL,//�ʏ�
		PREPARING_ATTACK,//�U������
		ATTACK, //�U��
		AFTER_ATTACK,//�U����

		END
	};

private:

	ENEMY_STATE enemy_state;//�G�̏��
	DATA spawn_location; //�X�|�[���������W���o����
	void DrawHpBar(DATA draw_location) const;

protected:

	int enemy_image[ENEMY_STATE::END][5];

	float enemy_control_time;//�G�̐���p����
	
	void SetEnemyState(ENEMY_STATE enemy_state);
	ENEMY_STATE GetEnemyState()const;
	
	DATA TargetTracking(DATA target_location, float speed)const;

	bool ScopeoOfActivity()const; //�����͈͊O�ɏo�����H

	virtual void Draw(DATA draw_location)const = 0;

public:

	EnemyBase(DATA location, DATA size, int hp, int mp, int attack_power, int enemy_image[ENEMY_STATE::END][5]);
	virtual ~EnemyBase();

	virtual void Update(float delta_time) = 0;
	void Draw()const;

	bool HitDamege(class BoxCollider* bc, int attack_power)override;
	
};

