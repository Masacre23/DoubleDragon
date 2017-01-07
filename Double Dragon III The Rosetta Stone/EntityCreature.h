#ifndef __CREATURE_H__
#define __CREATURE_H__

#include "Animation.h"
#include "Globals.h"
#include"ModuleEntity.h"
#include "ModuleCollision.h"

struct SDL_Texture;

enum creature_type
{
	PLAYER1,
	PLAYER2,
	ENEMY1,
	ENEMY2,
	BOSS,
	UNKNOWN
};

enum state
{
	IDLE = 1,
	WALKING,
	RUNNING,
	JUMPING,
	ATTACKING,
	DAMAGED,
	DEAD
};

class EntityCreature : public ModuleEntity
{
public:
	EntityCreature(creature_type types, bool start_enabled = true);
	~EntityCreature();

	void Die();

public:
	SDL_Texture* graphics = nullptr;

	Collider* creatureCollider;
	Animation right_down;
	Animation up;
	Animation punch;
	Animation kick;
	SDL_Rect kick_jump;
	SDL_Rect jump;
	SDL_Rect damaged, damaged2;
	Animation fall;

	state creature_state;
	float speed;
	int life;
	int damageAttack;
};

#endif