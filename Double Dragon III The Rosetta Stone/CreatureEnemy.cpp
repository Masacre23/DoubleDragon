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

CreatureEnemy::CreatureEnemy(bool start_enabled) : EntityCreature(ENEMY1, start_enabled)
{

}

CreatureEnemy::~CreatureEnemy()
{}

bool CreatureEnemy::Start()
{
	LOG("Loading enemy");

	graphics = App->textures->Load("Genesis 32X SCD - Double Dragon III The Rosetta Stone - Enemies.png");
	//graphics = App->textures->Load("Genesis 32X SCD - Double Dragon III The Rosetta Stone - Billy & Jimmy2.png");
	
	//playerState = IDLE;

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
	LOG("Updating enemy");
	position.x = 100;
	position.y = 216;
	SDL_Rect enemy = right_down.frames[0];
	bool flip = false;
	
	if (creatureCollider->collisionMatrix[1][0])
	{
		for (list<ModuleEntity*>::iterator it = App->entityManager->entities.begin(); it != App->entityManager->entities.end(); ++it)
		{
			CreaturePlayer* p = (CreaturePlayer*)(*it);
			if (p->playerState == ATTACKING)
			{
				enemy = right_down.frames[1];
			}
		}
		
	}
	creatureCollider->SetPos(position.x, position.y - 64);
	App->renderer->Blit(graphics, position.x + speed, position.y - enemy.h, &(enemy), 1.0f, flip);
	return UPDATE_CONTINUE;
}