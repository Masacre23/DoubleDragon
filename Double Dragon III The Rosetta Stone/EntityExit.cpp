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

EntityExit::EntityExit(SDL_Rect rect, bool start_enabled) : ModuleEntity(start_enabled)
{
	collider = App->collision->AddCollider(rect, EXIT);
}

EntityExit::~EntityExit()
{}

void EntityExit::NextRoom()
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
	App->scene_mission1->player2->Disable();

	App->CleanUp();
	App = new Application();
	App->Init();
}