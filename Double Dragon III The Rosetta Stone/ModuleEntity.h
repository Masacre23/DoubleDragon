#ifndef __MODULEENTITY_H__
#define __MODULEENTITY_H__

#include <list>
#include "Globals.h"
#include "Module.h"

/*enum Types
{
	npc,
	player,
	room,
	exit,
	item,
	unknown
};*/
enum Types
{
	npc,
	player,
	unknown
};

class ModuleEntity : public Module
{
public:
	ModuleEntity(bool start_enabled = true);
	~ModuleEntity();

public:
	//Types type;
};

#endif