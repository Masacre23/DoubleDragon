#include "Globals.h"
#include "Application.h"
#include "CreatureEnemy.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "src\pugixml.hpp"
#include "EntityManager.h"
#include "CreaturePlayer.h"
#include <cmath>

CreatureEnemy::CreatureEnemy(float x, float y, bool start_enabled) : EntityCreature(ENEMY1, start_enabled)
{
	position.x = x;
	position.y = y;
	life = 100;
	damageAttack = 5;
}

CreatureEnemy::~CreatureEnemy()
{}

bool CreatureEnemy::Start()
{
	LOG("Loading enemy");

	graphics = App->textures->Load("Genesis 32X SCD - Double Dragon III The Rosetta Stone - Enemies.png");
	
	creature_state = IDLE;

	for (list<ModuleEntity*>::iterator it = App->entityManager->entities.begin(); it != App->entityManager->entities.end(); ++it)
	{
		target = (CreaturePlayer*)(*it);
		if (target->type == player)
			break;
	}

	return true;
}

// Unload assets
bool CreatureEnemy::CleanUp()
{
	LOG("Unloading enemy");

	App->textures->Unload(graphics);

	return true;
}

// Update
update_status CreatureEnemy::Update()
{
	UpdateProfundity();
	static bool flip = false;
	static int counter = 0;
	
	if (creature_state != ATTACKING && creature_state != DAMAGED && creature_state != DEAD)
	{
		if (target->position.x < position.x)
			flip = true;
		else
			flip = false;
	}

	if (life <= 0)
		Die();

	switch (creature_state)
	{
	case DAMAGED:
		++counter;
		if (counter < 24)
		{
			enemy = damaged;
		}
		else
		{
			creature_state = IDLE;
			counter = 0;
			Move(enemy);
		}
		break;
	case DEAD:
		++counter;
		if (fall.AnimationHalf())
		{
			if(counter % 8 != 0)
				App->renderer->Blit(graphics, position.x + speed, position.y - enemy.h, &(enemy), 1.0f, flip);
			if (counter > 60 * 3)
				CleanUp();
			return UPDATE_CONTINUE;
			break;
		}
		enemy = fall.GetCurrentFrame();
		break;
	case IDLE:
		//if(up.current_frame == 0)
		enemy = right_down.frames[right_down.current_frame];
	default:
		Move(enemy);
		break;
	}

	creatureCollider->SetPos(position.x + 25, position.y - 64);
	App->renderer->Blit(graphics, position.x + speed, position.y - enemy.h, &(enemy), 1.0f, flip);
	return UPDATE_CONTINUE;
}

/****************************************************/
void CreatureEnemy::Move(SDL_Rect& enemy)
{
	float distx, disty, distance, moveX, moveY;
	speed = 1.0f;

	distx = target->position.x - position.x;
	disty = target->position.y - position.y;

	distance = sqrtf((distx * distx) + (disty * disty));
	if (distance > 20 && creature_state != ATTACKING)
	{
		//if(creatureCollider->collisionMatrix[1][1])//Enemy-enemy
		
		
		//Normalize
		distx /= distance;
		disty /= distance;

		distx *= speed;
		disty *= speed;

		position.x += distx;
		position.y += disty;

		enemy = right_down.GetCurrentFrame();
	}
	else
		enemy = Attack();
}

/****************************************************/
SDL_Rect CreatureEnemy::Attack()
{
	creature_state = ATTACKING;
	if (punch.AnimationFinished())
	{
		creature_state = WALKING;
		return right_down.frames[3];
	}
	if (punch.AnimationHalf() && position.DistanceTo(target->position) < 20 && target->creature_state != DAMAGED)
	{
		target->creature_state = DAMAGED;
		target->life -= damageAttack;
	}
	return punch.GetCurrentFrame();
}
