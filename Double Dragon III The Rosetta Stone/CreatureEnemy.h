#ifndef __CREATUREENEMY_H__
#define __CREATUREENEMY_H__

#include "Globals.h"
#include "Point.h"
#include "EntityCreature.h"
#include "ModuleCollision.h"

struct SDL_Texture;

class CreatureEnemy : public EntityCreature
{
public:
	CreatureEnemy(const creature_type* enemytype, const float* x, const float* y, bool start_enabled = true);
	~CreatureEnemy();

	bool Start();
	update_status Update();
	bool CleanUp();

	void Move();
	SDL_Rect Attack();
	SDL_Rect Jump(float& jump_speed, bool falling = false);

public:
	SDL_Texture* graphics = nullptr;
	CreaturePlayer* target, *target1, *target2;
	SDL_Rect* enemy = new SDL_Rect();
	creature_type enemytype;
	bool flip = false;

private:
	int y_ini = -1;
	float jump_speed = 4;
	float falling_speed = 2;
	int counter = 0;
	int current_attack = rand() % 3;
	int damage_reaction = rand() % 3;
	int counterJump = 0;
	int hitSound;
};

#endif