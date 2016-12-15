#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;

class ModulePlayer   : public Module
{
public:
	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	bool isAttacking(int& currentAttack);
	SDL_Rect GetAttack(int attack);

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect idle_left;
	SDL_Rect idle_right;
	iPoint position;
	Animation right_down;
	Animation left_down;
	Animation up_right;
	Animation up_left;
	Animation punch;
	Animation kick;
	bool direction; //rigth->true left->false

	int speed;
};

#endif // __MODULEPLAYER_H__