#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include <list>
class ModuleEntity;
enum Types;

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	void CreateEntity(Types type);

public:
	std::list<ModuleEntity*> entities;
};

#endif