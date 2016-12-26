#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
//#include "ModuleParticles.h"

using namespace std;

ModuleCollision::ModuleCollision()
{
}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end();)
	{
		if ((*it)->to_delete == true)
		{
			RELEASE(*it);
			it = colliders.erase(it);
		}
		else
			++it;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleCollision::Update()
{

	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
	{
		(*it)->colliding = false;
		for (list<Collider*>::iterator it2 = colliders.begin(); it2 != colliders.end(); ++it2)
		{
			if ((*it)->CheckCollision((*it2)->rect))
			{
				//LOG("YOLOOOOOOOOOOOOOOOOOOOOOO");
				(*it)->colliding = true;
				(*it2)->colliding = true;
				break;
			}
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if (debug == true)
		DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
	{
		switch ((*it)->type)
		{
		case PLAYER:
			App->renderer->DrawQuad((*it)->rect, 0, 255, 0, 80);
			break;
		case ENEMY:
			App->renderer->DrawQuad((*it)->rect, 0, 0, 255, 80);
			break;
		case WALL:
			App->renderer->DrawQuad((*it)->rect, 255, 0, 0, 80);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		RELEASE(*it);

	colliders.clear();

	return true;
}

Collider* ModuleCollision::AddCollider(const SDL_Rect& rect, const collider_type& type)
{
	Collider* ret = new Collider(rect);
	ret->type = type;
	colliders.push_back(ret);

	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	if (rect.x < r.x && rect.x + rect.w > r.x)
		if (rect.y < r.y && rect.y + rect.h > r.y)
			return true;

	return false;
}
