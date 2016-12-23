#ifndef __CREATURE_H__
#define __CREATURE_H__

#include"ModuleEntity.h"

class EntityCreature : public ModuleEntity
{
public:
	EntityCreature(bool start_enabled = true);
	~EntityCreature();


};

#endif