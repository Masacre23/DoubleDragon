#include "EntityManager.h"
#include "ModuleEntity.h"
#include "CreaturePlayer.h"
#include "CreatureEnemy.h"

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
	case player: ret = (ModuleEntity*)new CreaturePlayer(); break;
	case enemy: ret = (ModuleEntity*)new CreatureEnemy(); break;
	}

	if (ret != nullptr)
		entities.push_back(ret);

	//return ret;
}