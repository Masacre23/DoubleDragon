#ifndef __CREATUREPLAYER_H__
#define __CREATUREPLAYER_H__

#include "Animation.h"
#include "Globals.h"
#include "Point.h"
#include "EntityCreature.h"
#include "ModuleCollision.h"

struct SDL_Texture;

class CreaturePlayer   : public EntityCreature
{
public:
	CreaturePlayer(bool start_enabled = true);
	~CreaturePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	int getSpeed();
	bool isAttacking();
	SDL_Rect& getAttack();
	bool isJumping();
	void Jump(int& x, int& y);
	int getCollision();

public:
	
	Animation rotate_kick_jump;

	state playerState;
	int currentAttack = 0;
	Collider* playerCollider;
	bool wallCollision = false;
	bool enemyCollision = false;
};

#endif // __MODULEPLAYER_H__