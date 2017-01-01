#include "ModuleEntity.h"
#include "EntityCreature.h"
#include <string>

ModuleEntity::ModuleEntity(bool start_enabled) : Module(start_enabled)
{}

ModuleEntity::~ModuleEntity()
{}

void ModuleEntity::UpdateProfundity()
{
	

	if (type == player || type == enemy)
	{
		/*std::string tmp = "PLAYER: " + std::to_string(position.y);
		char tab2[1024];
		strcpy(tab2, tmp.c_str());
		LOG(tab2);*/
		EntityCreature* c = (EntityCreature*)this;
		if (c->creature_state == JUMPING)
		{
			return;
		}
	}

	profundity = position.y;
	
}