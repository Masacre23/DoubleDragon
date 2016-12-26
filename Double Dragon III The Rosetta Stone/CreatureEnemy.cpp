#include "Globals.h"
#include "Application.h"
#include "CreatureEnemy.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "src\pugixml.hpp"

CreatureEnemy::CreatureEnemy(bool start_enabled) : EntityCreature(ENEMY1, start_enabled)
{

}

CreatureEnemy::~CreatureEnemy()
{}

bool CreatureEnemy::Start()
{
	LOG("Loading enemy");

	//graphics = App->textures->Load("Genesis 32X SCD - Double Dragon III The Rosetta Stone - Enemies.png");
	graphics = App->textures->Load("Genesis 32X SCD - Double Dragon III The Rosetta Stone - Billy & Jimmy2.png");
	
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
	SDL_Rect enemy = right_down.frames[0];
	bool flip = false;

	App->renderer->Blit(graphics, position.x + speed, position.y - enemy.h, &(enemy), 1.0f, flip);
	return UPDATE_CONTINUE;
}