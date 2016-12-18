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
	SDL_Rect& getAttack(const int& attack);
	void Jump(int& x, int& y, bool& isJumping);

public:

	SDL_Texture* graphics = nullptr;
	iPoint position;
	Animation right_down;
	Animation up;
	Animation punch;
	Animation kick;
	SDL_Rect kick_jump;
	SDL_Rect jump;

	int speed;
	bool isJumping = false;
};

#endif // __MODULEPLAYER_H__