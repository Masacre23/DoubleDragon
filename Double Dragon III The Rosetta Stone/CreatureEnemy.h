#ifndef __CREATUREENEMY_H__
#define __CREATUREENEMY_H__

#include "Animation.h"
#include "Globals.h"
#include "Point.h"
#include "EntityCreature.h"
#include "ModuleCollision.h"

struct SDL_Texture;

class CreatureEnemy : public EntityCreature
{
public:
	CreatureEnemy(bool start_enabled = true);
	~CreatureEnemy();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* graphics = nullptr;
	iPoint position;
};

#endif