#include "EntityExit.h"
#include "ModuleCollision.h"
#include "Application.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneMenu.h"
#include "ModuleSceneMission1.h"
#include "ModuleRender.h"

#include "ModuleCollision.h"
#include "EntityManager.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleFonts.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "CreaturePlayer.h"

#include "ModuleSceneIni.h"
#include "Globals.h"

EntityExit::EntityExit(const SDL_Rect* rect, bool start_enabled) : ModuleEntity(start_enabled)
{
	collider = App->collision->AddCollider(*rect, EXIT);
}

EntityExit::~EntityExit()
{}

update_status EntityExit::Update()
{
	/*if (reset)
	{
		*App->scene_ini = ModuleSceneIni(false);
		App->scene_ini->Init();
		App->scene_ini->Start();
		*App->scene_menu = ModuleSceneMenu(false);
		App->scene_menu->Init();
		App->scene_menu->Start();
		//App->fade->FadeToBlack(App->scene_ini, nullptr, 0.0f);
		*App->scene_mission1 = ModuleSceneMission1(false);
		App->scene_mission1->Init();
		App->scene_mission1->Start();
		//*App->entityManager = EntityManager();
		App->fade->FadeToBlack(App->scene_ini, nullptr, 0.0f);
		App->entityManager->entities.clear();
		reset = false;
	}*/
	return UPDATE_CONTINUE;
}

bool EntityExit::CleanUp()
{

	return true;
}

void EntityExit::NextRoom() const
{
	/*for (list<ModuleEntity*>::iterator it = App->entityManager->entities.begin(); it != App->entityManager->entities.end(); ++it)
	{
		(*it)->Disable();
	}*/
	/*App->entityManager = new EntityManager();
	for (list<Collider*>::iterator it = App->collision->colliders.begin(); it != App->collision->colliders.end(); ++it)
	{
		
		delete(*it);
		//RELEASE(*it);
	}
	
	App->collision = new ModuleCollision();
	for (list<Collider*>::iterator it = App->collision->colliders.begin(); it != App->collision->colliders.end(); ++it)
	{
		RELEASE(*it);
	}

	App->collision->Init();
	App->collision->Start();

	App->scene_mission1->Disable();
	App->renderer->camera.x = 0;
	App->window->center_window_x = SCREEN_WIDTH / 2;
	App->fade->FadeToBlack(App->scene_menu, App->scene_mission1, 3.0f);*/
	/*App->scene_mission1->player2->Disable();
	App->collision->Disable();
	App->fade->FadeToBlack(App->scene_menu, App->scene_mission1, 3.0f);*/


	/*App->CleanUp();
	App = new Application();
	App->Init();*/
	*App->scene_ini = ModuleSceneIni(false);
	App->scene_ini->Init();
	//App->scene_ini->Start();
	App->fade->FadeToBlack(App->scene_ini, nullptr, 0.0f);
	*App->scene_menu = ModuleSceneMenu(false);
	App->scene_menu->Init();
	//App->scene_menu->Start();
	//App->fade->FadeToBlack(App->scene_ini, nullptr, 0.0f);
	*App->scene_mission1 = ModuleSceneMission1(false);
	App->scene_mission1->Init();
	//App->scene_mission1->Start();
	*App->entityManager = EntityManager();
	//App->entityManager->entities.clear();
	App->renderer->camera.x = App->renderer->camera.y = 0;
	App->renderer->camera.w = SCREEN_WIDTH * SCREEN_SIZE;
	App->renderer->camera.h = SCREEN_HEIGHT* SCREEN_SIZE;
	App->window->center_window_x = SCREEN_WIDTH / 2;
}