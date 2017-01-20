#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include <list>
#include "EntityCreature.h"

class ModuleEntity;
enum Types;

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	ModuleEntity* CreateEntity(const Types& type, const creature_type& creaturetype, float x = 0.0f, float y = 0.0f, int w = 0, int h = 0);
	void RadixSortList(std::list<ModuleEntity*>& l, const int& length, const int& numMax = 255);
	int Digit(const int& index, int num);
	void Wave(const int& numEnemies, float posX[], float posY[]);

public:
	std::list<ModuleEntity*> entities;
};

#endif