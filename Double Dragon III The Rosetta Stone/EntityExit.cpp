#include "EntityExit.h"
#include "ModuleCollision.h"
#include "Application.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneMenu.h"
#include "ModuleSceneMission1.h"
#include "ModuleRender.h"

#include "ModuleCollision.h"
#include "EntityManager.h"

EntityExit::EntityExit(SDL_Rect rect, bool start_enabled) : ModuleEntity(start_enabled)
{
	collider = App->collision->AddCollider(rect, EXIT);
}

EntityExit::~EntityExit()
{}

void EntityExit::NextRoom()
{
	App = new Application();
	App->Init();
}