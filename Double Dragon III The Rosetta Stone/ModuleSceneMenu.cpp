#include "Globals.h"
#include "Application.h"
#include "ModuleSceneMenu.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

ModuleSceneMenu::ModuleSceneMenu(bool start_enabled) : Module(start_enabled)
{
	// ground
	/*ground.x = 0;
	ground.y = 0;
	ground.w = 896;
	ground.h = 72;*/

	// Background / sky
	background.x = 0;
	background.y = 0;
	background.w = 320;
	background.h = 240;
}

ModuleSceneMenu::~ModuleSceneMenu()
{}

//Load assets
bool ModuleSceneMenu::Start()
{
	bool res = true;
	LOG("Loading menu scene");

	graphics = App->textures->Load("Double_Dragon3_arcade_title.png");
	//graphics = App->textures->Load("ddragon3.png");
	//App->audio->PlayMusic();
	//App->audio->PlayMusic("C:\\SDL Game 2 - Master - Handout\\Game\\ken.ogg");
	return res;
}

//UnLoad assets
bool ModuleSceneMenu::CleanUp()
{
	LOG("Unloading menu scene");

	App->textures->Unload(graphics);
	
	return true;
}

// Update: draw background
update_status ModuleSceneMenu::Update()
{
	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, 0, 0, &background, 1.8f); // sea and sky
	//App->renderer->Blit(graphics, 0, 170, &ground, 1.2f);
	return UPDATE_CONTINUE;
}