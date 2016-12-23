#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Animation.h"
#include "Globals.h"
#include "Point.h"
#include "EntityCreature.h"

struct SDL_Texture;

enum state
{
	IDLE = 1,
	WALKING,
	RUNNING,
	JUMPING,
	ATTACKING
};

class ModulePlayer   : public EntityCreature
{
public:
	ModulePlayer(bool start_enabled = true);
	//ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	int getSpeed();
	bool isAttacking();
	SDL_Rect& getAttack();
	bool isJumping();
	void Jump(int& x, int& y);

public:

	SDL_Texture* graphics = nullptr;
	iPoint position;
	Animation right_down;
	Animation up;
	Animation punch;
	Animation kick;
	SDL_Rect kick_jump;
	SDL_Rect jump;
	Animation rotate_kick_jump;

	state playerState;
	int speed;
	int currentAttack = 0;
	//bool isJumping = false;
};

#endif // __MODULEPLAYER_H__