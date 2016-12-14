#include "Globals.h"
#include "Application.h"
#include "ModuleSceneMission1.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

ModuleSceneMission1::ModuleSceneMission1(bool start_enabled) : Module(start_enabled)
{
	// ground
	/*ground.x = 0;
	ground.y = 0;
	ground.w = 896;
	ground.h = 72;*/

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
	bool res = true;
	LOG("Loading menu scene");

	graphics = App->textures->Load("Genesis 32X SCD - Double Dragon III The Rosetta Stone - Mission 1 America.png");
	//graphics = App->textures->Load("ddragon3.png");
	//App->audio->PlayMusic();
	//App->audio->PlayMusic("C:\\SDL Game 2 - Master - Handout\\Game\\ken.ogg");
	return res;
}

//UnLoad assets
bool ModuleSceneMission1::CleanUp()
{
	LOG("Unloading menu scene");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleSceneMission1::Update()
{
	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, 0, 0, &background, 1.8f); 
	//App->renderer->Blit(graphics, 0, 170, &ground, 1.2f);
	return UPDATE_CONTINUE;
}