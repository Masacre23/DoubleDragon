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
#include "ModuleSceneMenu.h"

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
	player = (CreaturePlayer*)App->entityManager->CreateEntity(Types::player, creature_type::PLAYER1, 120.0f, 200.0f);
	exit = (EntityExit*)App->entityManager->CreateEntity(Types::exits, creature_type::UNKNOWN,800, 60, 50, 30);

	bool res = true;
	LOG("Loading menu scene");

	graphics = App->textures->Load("Genesis 32X SCD - Double Dragon III The Rosetta Stone - Mission 1 America.png");
	gameoverTexture = App->textures->Load("Game over.png");

	for (list<ModuleEntity*>::iterator it = App->entityManager->entities.begin(); it != App->entityManager->entities.end(); ++it)
	{
		res = (*it)->Start();
		(*it)->Enable();
	}

	//Colliders-------------------
	SDL_Rect wallup = { 0, 0, 4000, 83 };
	App->collision->AddCollider(wallup, collider_type::WALL_UP);

	SDL_Rect walldown = { 0, SCREEN_HEIGHT, 4000, 83 };
	App->collision->AddCollider(walldown, collider_type::WALL_DOWN);

	SDL_Rect wallright = { 900, 0, 5, SCREEN_HEIGHT };
	App->collision->AddCollider(wallright, collider_type::WALL_RIGHT);

	SDL_Rect wallleft = { 40, 0, 5, SCREEN_HEIGHT };
	App->collision->AddCollider(wallleft, collider_type::WALL_LEFT);

	//Car
	SDL_Rect walldownCar = { 375, 180, 113, 5 };
	App->collision->AddCollider(walldownCar, collider_type::WALL_DOWN);

	SDL_Rect wallrightCar = { 375, 180, 5, 40 };
	App->collision->AddCollider(wallrightCar, collider_type::WALL_RIGHT);

	SDL_Rect wallleftCar = { 375 + 113, 180, 5, 40 };
	App->collision->AddCollider(wallleftCar, collider_type::WALL_LEFT);

	//Spawns
	SDL_Rect spawn1 = {550, 0, 5, SCREEN_HEIGHT};
	App->collision->AddCollider(spawn1, collider_type::SPAWN);

	SDL_Rect wallspawn = { 551, 0, 5, SCREEN_HEIGHT };
	App->collision->AddCollider(wallspawn, collider_type::WALL_LEFT);

	//Enemies
	float posX[] = {-player->position.x - 300, player->position.x + 300, player->position.x + 400 };
	float posY[] = { 150.0f, 200.0f, 250.0f};
	App->entityManager->Wave(3, posX, posY);
	++num_waves;

	//Music
	App->audio->PlayMusic("02-in-america.ogg");

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
	static bool b = false;
	
	--App->time;

	if (App->time % (2 * 60) == 0) //2 seconds
		b = !b;
	// Exit
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
		if (b)
			exit->NextRoom();
	}

	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, 0, 0, &background, 1.0f);

	//Update entities
	int num_enemies = 0;
	for (list<ModuleEntity*>::iterator it = App->entityManager->entities.begin(); it != App->entityManager->entities.end(); ++it)
	{
		if ((*it)->IsEnabled())
		{
			if ((*it)->type == Types::enemy)
				++num_enemies;
			(*it)->Update();
		}
	}

	//Manage waves
	if (player->creatureCollider->collisionArray[collider_type::SPAWN])
	{
		new_wave = true;
	}

	if (num_enemies == 1 && num_waves % 2 != 0 || num_enemies == 0 && new_wave)
	{
		float posX[] = { player->position.x - 300, player->position.x + 300, player->position.x + 400 };
		float posY[] = { 150.0f, 200.0f, 250.0f };
		App->entityManager->Wave(3, posX, posY);
		++num_waves;
		new_wave = false;
	}

	// Draw fonts --------------------------------------------

	//First player
	iPoint pos = { App->window->center_window_x - SCREEN_WIDTH / 4, 10 };
	if (player->creature_state == DEAD)
	{
		//Without life
		pos = { App->window->center_window_x - SCREEN_WIDTH / 4 - 10, 22 };
		if (b)
		{
			App->fonts->DrawLine("press", 0, pos);
			//pos.x += 15;
			pos.y += 10;
			App->fonts->DrawLine("start", 0, pos);
		}
		else
		{
			App->fonts->DrawLine("cont _", 0, pos);
			//pos.x += 15;
			pos.y += 10;
			App->fonts->DrawLine("inue ?", 0, pos);
		}

	}
	else
	{
		//With life
		pos.y = -80;
		pos.x -= 20 + 20;
		if (player->life < 100)
		{
			if(player->life < 10)
				App->fonts->DrawLine("000", 4, pos);
			else
				App->fonts->DrawLine("0" + to_string(player->life), 4, pos);
		}
		else
			App->fonts->DrawLine(to_string(player->life), 4, pos);
		pos.x += 5;
		pos.y = 45;
		App->fonts->DrawLine("jimmy", 0, pos);
		pos.y = 17;
		pos.x += 45;
		App->fonts->DrawFace(pos);
	}

	//Time
	pos = { App->window->center_window_x - 20, 22 };
	if(App->time <= 0)
		App->fonts->DrawLine("time 0", 0, pos);
	else
		App->fonts->DrawLine("time " + to_string(App->time / 60), 0, pos);
	pos.y += 10;
	App->fonts->DrawLine("coins " + to_string(App->coins), 0, pos);


	//Second player ----------------------------------------
	
	pos = { App->window->center_window_x + SCREEN_WIDTH / 4 + 10, 22 };
	if (player->creature_state == DEAD)
	{
		// Without life
		if (b)
		{
			pos.x -= 10;
			App->fonts->DrawLine("cont _", 0, pos);
			pos.y += 10;
			App->fonts->DrawLine("inue ?", 0, pos);
		}
		else
		{
			pos.x -= 10;
			App->fonts->DrawLine("press", 0, pos);
			pos.y += 10;
			App->fonts->DrawLine("start", 0, pos);
		}
	}
	else
	{
		if (!player2created)
		{
			if (b)
			{
				pos.x -= 10;
				App->fonts->DrawLine("press", 0, pos);
				pos.y += 10;
				App->fonts->DrawLine("start", 0, pos);
			}
			else
			{
				App->fonts->DrawLine("to", 0, pos);
				pos.x -= 15;
				pos.y += 10;
				App->fonts->DrawLine("buy in", 0, pos);
			}
		}
		else // With life
		{
			pos.y += SCREEN_WIDTH / 2;
			pos.y = -80 -24;
			pos.x -= 20 + 20;
			if (player2->life < 100)
			{
				if (player2->life < 10)
					App->fonts->DrawLine("000", 5, pos);
				else
					App->fonts->DrawLine("0" + to_string(player2->life), 5, pos);
			}
			else
				App->fonts->DrawLine(to_string(player2->life), 5, pos);
			pos.x += 5;
			pos.y = 45;
			App->fonts->DrawLine("billy", 0, pos);
			pos.y = 17;
			pos.x += 45;
			App->fonts->DrawFace(pos, 1);
		}
	}

	//Game over
	if (App->time <= 0)
	{
		SDL_Rect gameover = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		if (player2created)
		{
			if (player2->creature_state == DEAD)
			{
				App->renderer->Blit(gameoverTexture, App->window->center_window_x - SCREEN_WIDTH / 2, 0, &(gameover), 1.0f);
			}
		}
		else
		{
			App->renderer->Blit(gameoverTexture, App->window->center_window_x - SCREEN_WIDTH / 2, 0, &(gameover), 1.0f);
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && App->time <= 10 * 60)
	{
		if (App->coins > 0 && App->time > 0)
			Respawn();
		else
		{
			Reset();
		}
	}
	else if(App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && player2created == false)
	{
		InsertPlayer2();
	}

	return UPDATE_CONTINUE;
}

/*****************************************************/
void ModuleSceneMission1::Respawn()
{
	--App->coins;
	App->time = 150 * 60; //150 seconds
	player->creature_state = IDLE;
	player->life = 250;
	player->invulnerability = true;
}

/******************************************************/
void ModuleSceneMission1::Reset()
{
	App->CleanUp();
	App = new Application();
	App->Init();
}

/**************************************************/
void ModuleSceneMission1::InsertPlayer2()
{
	player2 = (CreaturePlayer*)App->entityManager->CreateEntity(Types::player, PLAYER2, player->position.x + 50, player->position.y);
	player2->Start();
	player2created = true;

	App->numplayers++;
}