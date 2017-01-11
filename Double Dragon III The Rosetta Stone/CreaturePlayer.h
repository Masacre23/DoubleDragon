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
	CreaturePlayer(creature_type playertype, float x, float y, bool start_enabled = true);
	~CreaturePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	int getSpeed();
	bool isAttacking();
	SDL_Rect& getAttack();
	bool isJumping();
	void Jump();
	void HeadButt();
	void doDamage();
	void UpdateCamera();

public:
	
	Animation rotate_kick_jump;
	SDL_Rect head_butt;

	int currentAttack = 0;
	bool running = false;
	bool isButting = false;
	bool flip = false;
	bool invulnerability = false;
	int damage_reaction = rand() % 3;
	bool falling = false;

	//Sounds
	int punchSound;
	int kickSound;

private:
	SDL_Rect billy = right_down.frames[0];
	int counter = 0;

	int newSpeed;
	int controlsplayer[7];
	int controlsplayer1[7] = { SDL_SCANCODE_W, SDL_SCANCODE_A, SDL_SCANCODE_S, SDL_SCANCODE_D, SDL_SCANCODE_N, SDL_SCANCODE_M, SDL_SCANCODE_SPACE };
	int controlsplayer2[7] = { SDL_SCANCODE_UP, SDL_SCANCODE_LEFT, SDL_SCANCODE_DOWN, SDL_SCANCODE_RIGHT, SDL_SCANCODE_KP_2, SDL_SCANCODE_KP_3, SDL_SCANCODE_KP_0 };

	bool jumpDirection[2] = { false, false }; //right, left
	float jump_speed = 5;
	int y_ini = -1;

	//Get speed
	int maxTime = 24;
	int time = 0;
	bool walking = false;
};

#endif // __MODULEPLAYER_H__