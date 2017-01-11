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
	background.w = 960;
	background.h = 224;

	// Title
	title.x = 10;
	title.y = 224;
	title.w = 320;
	title.h = 224;
}

ModuleSceneMenu::~ModuleSceneMenu()
{}

//Load assets
bool ModuleSceneMenu::Start()
{
	bool res = true;
	LOG("Loading menu scene");

	graphics = App->textures->Load("title_dd3.png");

	App->audio->PlayMusic("01-rosetta-stone.ogg");

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
	static int x, x2 = -400;
	static bool b = false;
	if (x > -960 + 320)
		x -= 10;
	else
		b = true;
	App->renderer->Blit(graphics, x, 0, &background, 1.0f);
	if (b)
	{
		if(x2 <= 0)
			x2 += 20;
		App->renderer->Blit(graphics, x2, 0, &title, 1.0f);
	}
	return UPDATE_CONTINUE;
}