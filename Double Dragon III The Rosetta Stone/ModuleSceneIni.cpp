#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIni.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEntity.h"
#include "ModuleSceneMenu.h"

ModuleSceneIni::ModuleSceneIni(bool start_enabled) : Module(start_enabled)
{}

ModuleSceneIni::~ModuleSceneIni()
{
	CleanUp();
}

bool ModuleSceneIni::Start()
{
	bool res = true;
	LOG("Loading Ini scene");

	sega = App->textures->Load("resources/title_sega.png");
	flying = App->textures->Load("resources/flyingedge.png");


	flyingRect = { 0,0,320,224 };
	segaAnimation.frames.push_back({ 0, 0, 96, 32 });
	segaAnimation.frames.push_back({ 0, 32, 96, 32 });
	segaAnimation.frames.push_back({ 0, 64, 96, 32 });
	segaAnimation.frames.push_back({ 0, 96, 96, 32 });
	segaAnimation.frames.push_back({ 0, 128, 96, 32 });
	segaAnimation.frames.push_back({ 0, 160, 96, 32 });
	segaAnimation.frames.push_back({ 0, 192, 96, 32 });
	segaAnimation.frames.push_back({ 0, 224, 96, 32 });
	segaAnimation.frames.push_back({ 0, 256, 96, 32 });
	segaAnimation.frames.push_back({ 0, 288, 96, 32 });
	segaAnimation.frames.push_back({ 0, 320, 96, 32 });
	segaAnimation.frames.push_back({ 0, 352, 96, 32 });
	segaAnimation.frames.push_back({ 0, 384, 96, 32 });
	segaAnimation.frames.push_back({ 0, 416, 96, 32 });

	App->audio->PlayMusic("resources/01-rosetta-stone.ogg");

	return res;
}

update_status ModuleSceneIni::Update()
{
	static int counter = 0;
	++counter;

	switch (currentState)
	{
	case SEGA:
		App->renderer->Blit(sega, App->window->center_window_x - segaAnimation.frames[0].w/2, SCREEN_HEIGHT/2 - segaAnimation.frames[0].h/2, &(segaAnimation.GetCurrentFrame()), 1.0f);
		if (counter >= 5 * 60)
			currentState = FLYING;
		break;
	case FLYING:
		App->renderer->Blit(flying, 0, 0, &(flyingRect), 1.0f);
		if (counter >= 10 * 60)
		{
			Disable();
			App->fade->FadeToBlack(App->scene_menu, App->scene_ini, 2.0f);
		}
		break;
	}
	return UPDATE_CONTINUE;
}

bool ModuleSceneIni::CleanUp()
{
	LOG("Unloading ini scene");
	App->textures->Unload(sega);
	App->textures->Unload(flying);

	return true;
}