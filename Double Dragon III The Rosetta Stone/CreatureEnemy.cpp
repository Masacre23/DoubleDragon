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

#include <cstdlib>
#include "ModuleAudio.h"

CreatureEnemy::CreatureEnemy(creature_type creaturetype, float x, float y, bool start_enabled) : EntityCreature(creaturetype, start_enabled)
{
	position.x = x;
	position.y = y;
	enemytype = creaturetype;
}

CreatureEnemy::~CreatureEnemy()
{}

bool CreatureEnemy::Start()
{
	LOG("Loading enemy");

	hitSound = App->audio->LoadFx("enemy_hit.wav");

	graphics = App->textures->Load("Genesis 32X SCD - Double Dragon III The Rosetta Stone - Enemies.png");
	
	creature_state = WALKING;

	bool findsecond = false;
	if (App->numplayers == 2)
	{
		findsecond = rand() % 2;
	}

	int counter = 0;
	for (list<ModuleEntity*>::iterator it = App->entityManager->entities.begin(); it != App->entityManager->entities.end(); ++it)
	{
		target = (CreaturePlayer*)(*it);
		if (target->type == player)
		{
			++counter;
			if(findsecond == false || counter == 2)
				break;
		}
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
	
	if (creature_state == WALKING)
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
			switch (damage_reaction)
			{
			case 0:
				*enemy = damaged;
				break;
			case 1:
				*enemy = damaged2;
				break;
			case 2:
				counter = 0;
				*enemy = Jump(falling_speed, true);
				break;
			}
		}
		else
		{
			creature_state = IDLE;
			counter = 0;
			damage_reaction = rand() % 3;
			Move();
		}
		break;
	case DEAD:
		++counter;
		if (fall.AnimationHalf())
		{
			if(counter % 8 != 0)
				App->renderer->Blit(graphics, position.x + speed, position.y - (*enemy).h, &(*enemy), 1.0f, flip);
			if (counter > 60 * 3)
			{
				CleanUp();
				Disable();
			}
			return UPDATE_CONTINUE;
			break;
		}
		*enemy = fall.GetCurrentFrame();
		break;
	case IDLE:
		*enemy = right_down.frames[right_down.current_frame];
	default:
		Move();
		break;
	}

	creatureCollider->SetPos(position.x + 25, position.y - 64);
	App->renderer->Blit(graphics, position.x + speed, position.y - (*enemy).h, &(*enemy), 1.0f, flip);
	return UPDATE_CONTINUE;
}

/****************************************************/
void CreatureEnemy::Move()
{
	float distx, disty, distance;

	distx = target->position.x - position.x;
	disty = target->position.y - position.y;

	distance = sqrtf((distx * distx) + (disty * disty));
	if (distance > 20 && creature_state != ATTACKING && creature_state != JUMPING)
	{
		//Normalize
		distx /= distance;
		disty /= distance;

		distx *= speed;
		disty *= speed;

		position.x += distx;
		position.y += disty;

		if (target->position.y > position.y)
			*enemy = right_down.GetCurrentFrame();
		else
			*enemy = up.GetCurrentFrame();
	}
	else
	{
		if ((target->creature_state != DEAD && target->creature_state != DEAD) || creature_state == JUMPING)
		{
			*enemy = Attack();
		}
		else
			*enemy = right_down.frames[right_down.current_frame];
	}
}

/****************************************************/
SDL_Rect CreatureEnemy::Attack()
{
	creature_state = ATTACKING;
	if (punch.AnimationFinished() || kick.AnimationFinished())
	{
		creature_state = WALKING;
		current_attack = rand() % 3;

		if(enemytype == creature_type::ENEMY1)
			return right_down.frames[3];
		else if(enemytype == creature_type::ENEMY2)
			return right_down.frames[1];
	}
	if ((punch.AnimationHalf() || kick.AnimationHalf() || creature_state == JUMPING) && position.DistanceTo(target->position) < 20 
		&& target->creature_state != DAMAGED && target->invulnerability == false && target->falling == false)
	{
		if (target->creature_state != JUMPING)
			target->creature_state = DAMAGED;
		else
		{
			target->falling = true;
		}
		target->life -= damageAttack;
		App->audio->PlayFx(hitSound);
	}
	
	switch (current_attack)
	{
	case 0:
		return punch.GetCurrentFrame();
		break;
	case 1:
		return kick.GetCurrentFrame();
		break;
	case 2:
		creature_state = JUMPING;
		if (creatureCollider->collisionArray[collider_type::PLAYER] && target->creature_state != DAMAGED && target->invulnerability == false
			&& target->falling == false)
		{
			if (target->creature_state != JUMPING)
				target->creature_state = DAMAGED;
			else
				target->falling = true;
			target->life -= damageAttack;
			App->audio->PlayFx(hitSound);
		}
		return Jump(jump_speed);
		break;
	}
}

/************************************/
SDL_Rect CreatureEnemy::Jump(float& jump_speed, bool falling)
{
	float aceleration = 0.3f;

	if (y_ini == -1)
	{
		y_ini = position.y;
		position.y -= 1;
	}
	else if (y_ini <= position.y)
	{
		position.y = y_ini;
		if (fall.AnimationFinished() || falling == false)
		{
			creature_state = WALKING;
			y_ini = -1;
			counterJump = 0;
			current_attack = rand() % 3;
			damage_reaction = rand() % 3;
			jump_speed = 4;

			if (enemytype == creature_type::ENEMY1)
				return right_down.frames[3];
			else if (enemytype == creature_type::ENEMY2)
				return right_down.frames[1];
		}
	}
	else
	{
		jump_speed -= aceleration;
		position.y -= jump_speed;

		if (falling)
		{
			if (target->flip)
				position.x -= 4;
			else if (target->flip == false)
				position.x += 4;
		}
		else
		{
			if (flip == false)
				position.x += 2;
			else if (flip)
				position.x -= 2;
		}
	}
	if (falling)
		return fall.GetCurrentFrame();

	if (enemytype == creature_type::ENEMY1)
	{
		++counterJump;
		if (counterJump < 12)
			return jump;
		else
			return kick_jump;
	}
	else if (enemytype == creature_type::ENEMY2)
		return jump;
}
