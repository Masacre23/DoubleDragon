#ifndef __CREATURE_H__
#define __CREATURE_H__

#include "Animation.h"
#include "Globals.h"
#include "Point.h"
#include"ModuleEntity.h"
#include "ModuleCollision.h"

struct SDL_Texture;

enum creature_type
{
	PLAYER1,
	PLAYER2,
	ENEMY1,
	ENEMY2,
	BOSS
};

class EntityCreature : public ModuleEntity
{
public:
	EntityCreature(creature_type types, bool start_enabled = true);
	~EntityCreature();

public:
	SDL_Texture* graphics = nullptr;
	iPoint position;

	Collider* creatureCollider;
	Animation right_down;

	int speed;
};

#endif