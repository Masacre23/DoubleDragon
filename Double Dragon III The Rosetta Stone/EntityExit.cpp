#include "EntityExit.h"
#include "ModuleCollision.h"
#include "Application.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneMenu.h"
#include "ModuleSceneMission1.h"
#include "ModuleRender.h"

EntityExit::EntityExit(SDL_Rect rect, bool start_enabled) : ModuleEntity(start_enabled)
{
	collider = App->collision->AddCollider(rect, EXIT);
}

EntityExit::~EntityExit()
{}

void EntityExit::NextRoom()
{
	App->scene_mission1->Disable();
	App->fade->FadeToBlack(App->scene_menu, nullptr, 3.0f);
	App->renderer->camera.x = 0;
}