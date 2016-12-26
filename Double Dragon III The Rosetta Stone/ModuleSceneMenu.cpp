#include "Globals.h"
#include "Application.h"
#include "ModuleSceneMenu.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "CreaturePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

ModuleSceneMenu::ModuleSceneMenu(bool start_enabled) : Module(start_enabled)
{
	// Background
	background.x = 0;
	background.y = 0;
	background.w = 320;
	background.h = 224;
}

ModuleSceneMenu::~ModuleSceneMenu()
{}

//Load assets
bool ModuleSceneMenu::Start()
{
	bool res = true;
	LOG("Loading menu scene");

	graphics = App->textures->Load("DD3_Title.gif");
	//App->audio->PlayMusic("01-rosetta-stone.ogg");

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