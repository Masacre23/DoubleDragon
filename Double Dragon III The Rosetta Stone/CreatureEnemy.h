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
	CreatureEnemy(float x, float y, bool start_enabled = true);
	~CreatureEnemy();

	bool Start();
	update_status Update();
	bool CleanUp();

	void Move(SDL_Rect& enemy);
	SDL_Rect Attack();
	void ReceiveDamage(int damage);

public:
	SDL_Texture* graphics = nullptr;
	CreaturePlayer* target;
	SDL_Rect enemy;
};

#endif