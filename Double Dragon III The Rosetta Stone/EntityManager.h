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
	void RadixSortList(std::list<ModuleEntity*>& l, int length, int numMax = 64);
	int Digit(int index, int num);

public:
	std::list<ModuleEntity*> entities;
};

#endif