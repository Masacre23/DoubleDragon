#include "Globals.h"
#include "Application.h"
#include "ModuleSceneMission1.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "CreaturePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"
#include "ModuleCollision.h"
#include "EntityManager.h"

#include "ModuleFonts.h"
#include "ModuleWindow.h"
#include "EntityExit.h"
#include "CreatureEnemy.h"

ModuleSceneMission1::ModuleSceneMission1(bool start_enabled) : Module(start_enabled)
{
	// Background / sky
	background.x = 8;
	background.y = 8;
	background.w = 959;
	background.h = 224;
}

ModuleSceneMission1::~ModuleSceneMission1()
{}

//Load assets
bool ModuleSceneMission1::Start()
{
	player = (CreaturePlayer*)App->entityManager->CreateEntity(Types::player, creature_type::PLAYER1);
	exit = (EntityExit*)App->entityManager->CreateEntity(Types::exits, creature_type::UNKNOWN,800, 60, 50, 30);

	bool res = true;
	LOG("Loading menu scene");

	graphics = App->textures->Load("Genesis 32X SCD - Double Dragon III The Rosetta Stone - Mission 1 America.png");

	//res = App->player->Start();
	//App->player->Enable();
	for (list<ModuleEntity*>::iterator it = App->entityManager->entities.begin(); it != App->entityManager->entities.end(); ++it)
	{
		res = (*it)->Start();
		(*it)->Enable();
	}

	//Colliders
	SDL_Rect wallup = { 0, 0, 4000, 83 };
	App->collision->AddCollider(wallup, collider_type::WALL_UP);

	SDL_Rect walldown = { 0, SCREEN_HEIGHT, 4000, 83 };
	App->collision->AddCollider(walldown, collider_type::WALL_DOWN);

	SDL_Rect wallright = { 900, 0, 5, SCREEN_HEIGHT };
	App->collision->AddCollider(wallright, collider_type::WALL_RIGHT);

	//Car
	SDL_Rect walldownCar = { 375, 180, 113, 5 };
	App->collision->AddCollider(walldownCar, collider_type::WALL_DOWN);

	SDL_Rect wallrightCar = { 375, 180, 5, 40 };
	App->collision->AddCollider(wallrightCar, collider_type::WALL_RIGHT);

	SDL_Rect wallleftCar = { 375 + 113, 180, 5, 40 };
	App->collision->AddCollider(wallleftCar, collider_type::WALL_LEFT);

	//Enemies
	float posX[] = {-50, 400, 0, 300.0f, 300.0f};
	float posY[] = { 100.0f, 200.0f, 150.0f, 200.0f, 230.0f };
	App->entityManager->Wave(1, 1, posX, posY);

	return res;
}

//UnLoad assets
bool ModuleSceneMission1::CleanUp()
{
	LOG("Unloading menu scene");

	App->textures->Unload(graphics);
	App->collision->Disable();
	//App->player->Disable();
	for (list<ModuleEntity*>::iterator it = App->entityManager->entities.begin(); it != App->entityManager->entities.end(); ++it)
		(*it)->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneMission1::Update()
{
	static int time = 200 * 60;
	--time;

	if (player->creatureCollider->collisionArray[collider_type::EXIT])
	{
		bool b = true;
		for (list<ModuleEntity*>::iterator it = App->entityManager->entities.begin(); it != App->entityManager->entities.end(); ++it)
		{
			if ((*it)->type == enemy)
			{
				CreatureEnemy* e = (CreatureEnemy*)(*it);
				if (e->creature_state != DEAD)
					b = false;
			}
		}
		if(b)
			exit->NextRoom();
	}

	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, 0, 0, &background, 1.0f); 

	//Update entities
	for (list<ModuleEntity*>::iterator it = App->entityManager->entities.begin(); it != App->entityManager->entities.end(); ++it)
		(*it)->Update();

	// Draw fonts

	//First player
	//Without life
	/*iPoint pos = { App->window->center_window_x - SCREEN_WIDTH / 4, 10 };
	App->fonts->DrawLine("to", 0, pos);
	pos.x -= 15;
	pos.y += 10;
	App->fonts->DrawLine("buy in", 0, pos);*/

	//With life
	iPoint pos = { App->window->center_window_x - SCREEN_WIDTH / 4, 10 };
	pos.y = -90;
	App->fonts->DrawLine(to_string(player->life), 4, pos);

	//Time
	pos = { App->window->center_window_x, 10 };
	pos.x -= 20;
	App->fonts->DrawLine("time: "+to_string(time/60), 0, pos);

	//Second player
	pos = { App->window->center_window_x + SCREEN_WIDTH / 4, 10};
	App->fonts->DrawLine("to", 0, pos);
	pos.x -= 15;
	pos.y += 10;
	App->fonts->DrawLine("buy in", 0, pos);

	return UPDATE_CONTINUE;
}