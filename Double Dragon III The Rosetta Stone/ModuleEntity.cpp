#include "ModuleEntity.h"
#include "EntityCreature.h"
#include <string>

#include "Application.h"
#include "EntityManager.h"


ModuleEntity::ModuleEntity(bool start_enabled) : Module(start_enabled)
{}

ModuleEntity::~ModuleEntity()
{}

void ModuleEntity::UpdateProfundity()
{
	if (type == player || type == enemy)
	{
		EntityCreature* c = (EntityCreature*)this;
		if (c->creature_state == JUMPING)
		{
			return;
		}
	}

	profundity = position.y;
}