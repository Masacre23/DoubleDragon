#include "EntityManager.h"
#include "ModuleEntity.h"
#include "ModulePlayer.h"

EntityManager::EntityManager()
{}

EntityManager::~EntityManager()
{}

void EntityManager::CreateEntity(Types type)
{
	//static_assert(ModuleEntity::Types::un)
	ModuleEntity* ret = nullptr;
	switch (type)
	{
	case player: ret = new ModulePlayer(); break;
	}

	if (ret != nullptr)
		entities.push_back(ret);

	//return ret;
}