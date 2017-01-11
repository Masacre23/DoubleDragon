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
	void Jump();
	void HeadButt();
	void doDamage();
	void UpdateCamera();
	//int getCollision();

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
};

#endif // __MODULEPLAYER_H__